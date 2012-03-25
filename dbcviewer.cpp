#include "dbcviewer.h"
#include "ui_dbcviewer.h"

DBCViewer::DBCViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DBCViewer)
{
    ui->setupUi(this);
}

DBCViewer::~DBCViewer()
{
    delete ui;
}

void DBCViewer::on_actionQuit_triggered()
{
    QApplication::quit();
}

void DBCViewer::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Please select DBC file", "./", "*.dbc");
    ui->statusBar->showMessage("Loading... " + file);
    LoadIntoTable(file);
}

void DBCViewer::LoadIntoTable(QString file)
{
    QFile loader(file);
    if (!loader.open(QIODevice::ReadOnly))
    {
        QMessageBox message;
        message.setText("Cannot open file " + file);
        message.exec();
        ui->statusBar->showMessage("Cannot open file " + file);
        return;
    }

    char title[5];
    int records;
    int fields;
    int recordSize;
    int stringsSize;
    int stringsOffset;

    QDataStream stream(&loader);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.readRawData(title, 4);
    if (qstrncmp(title, "WDBC", 4) != 0)
    {
        QMessageBox message;
        message.setText("This it not DBC File !!");
        message.exec();
        ui->statusBar->showMessage("File is not DBC " + file);
        return;
    }
    stream >> records;
    stream >> fields;
    stream >> recordSize;
    stream >> stringsSize;

    for (int i = ui->tableWidget->columnCount(); i < fields; ++i)
        ui->tableWidget->insertColumn(ui->tableWidget->columnCount());

    for (int i = ui->tableWidget->rowCount(); i < records; ++i)
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    stringsOffset = records * recordSize + 20;

    int* table = new int[records * recordSize];

    for (int i = 0; i < records; ++i)
    {
        stream.readRawData((char*)(table + i * recordSize), recordSize);
    }

    char* strings = new char[stringsSize];
    stream.readRawData(strings, stringsSize);

    ui->tableWidget->setUpdatesEnabled(false);
    unsigned char fieldTypes[fields];
    memset(fieldTypes, 1, fields);
    fieldTypes[0] = 0;

    for (register int i = 0; i < records; ++i)
    {
        for (register int b = 1; b < fields; ++b)
        {
            if (table[i * recordSize + b] > 0 &&
                table[i * recordSize + b] < stringsSize  &&
                *(strings + table[i * recordSize + b] - 1) == 0 &&
                *(strings + table[i * recordSize + b]) >= 'A' &&
                *(strings + table[i * recordSize + b]) <= 'z' &&
                fieldTypes[b] == 1)
                fieldTypes[b] = 1;
            else
            {
                if (*(float*)(table + i * recordSize + b) - int(*(float*)(table + i * recordSize + b)) != 0 && log10(table[i * recordSize + b]) > 6)
                    fieldTypes[b] = 2;
                else
                    fieldTypes[b] = 0;
            }
        }
    }

    for (register int i = 0; i < records; ++i)
    {
        for (register int b = 0; b < fields; ++b)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            switch (fieldTypes[b])
            {
                case 1: // strings;
                    item->setText(QString(strings + table[i * recordSize + b]));
                    break;
                case 0: // ints
                    item->setText(QString::number(table[i * recordSize + b]));
                    break;
                case 2: // float
                    item->setText(QString::number(*(float*)(table + i * recordSize + b)));
                    break;
            }
            ui->tableWidget->setItem(i, b, item);
        }
    }
    ui->tableWidget->setUpdatesEnabled(true);
    ui->statusBar->showMessage("File Loaded");
    loader.close();
    delete [] table;
    delete [] strings;
}

void DBCViewer::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i)
        if (QTableWidgetItem* item = ui->tableWidget->item(previousRow, i))
            item->setBackground(QBrush(Qt::transparent));
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i)
        if (QTableWidgetItem* item = ui->tableWidget->item(currentRow, i))
            item->setBackground(QBrush(QColor(0xFF, 0x6E, 0x00)));
}
