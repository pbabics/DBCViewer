#ifndef DBCVIEWER_H
#define DBCVIEWER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <cmath>

namespace Ui {
    class DBCViewer;
}

class DBCViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBCViewer(QWidget *parent = 0);
    ~DBCViewer();

private slots:
    void on_actionQuit_triggered();

    void LoadIntoTable(QString file, QString format);
    void ReloadIntoTable();

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_actionGet_triggered();

    void on_actionSet_triggered();

    void on_actionReload_triggered();

    void on_searchButton_clicked();

    void on_actionAutomatic_Field_Detection_triggered();

    void on_actionManual_Field_Setup_triggered();

private:
    Ui::DBCViewer *ui;
    QString lastFile;
    QString fieldTypes;
    QFile loader;
    QFileInfo fileInfo;
};

#endif // DBCVIEWER_H
