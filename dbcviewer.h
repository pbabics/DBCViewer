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
#include <QTextStream>
#include <cmath>
#include "export.h"
#include "progressbar.h"

namespace Ui {
    class DBCViewer;
    class Export;
    class ProgressBar;
}

class DBCViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBCViewer(QWidget *parent = 0);
    ~DBCViewer();

private slots:
    void on_actionQuit_triggered();

    void LoadDBCIntoTable(QString file, QString format);
    void LoadDB2IntoTable(QString file, QString format);

    void ReloadDBCIntoTable();
    void ReloadDB2IntoTable();

    QString DetectFormat(int rows, int cols, int *table, int recordSize, char *strings, int stringsSize, int usedRows = 10);

    void FillTable(int rows, int cols, int *table, int recordSize, char *strings, int stringsSize);

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_actionGet_triggered();

    void on_actionSet_triggered();

    void on_actionReload_triggered();

    void on_searchButton_clicked();

    void on_actionAutomatic_Field_Detection_triggered();

    void on_actionManual_Field_Setup_triggered();

    void on_actionExport_To_SQL_triggered();

    void on_actionAutomatic_field_detection_triggered();

    void on_actionManual_field_Setup_triggered();

    void on_actionFile_Statistics_triggered();

private:
    Ui::DBCViewer *ui;
    Export *exportWindow;
    ProgressBar *progress;
    QString lastFile;
    QString fieldTypes;
    QFile loader;
    QFileInfo fileInfo;

    QFileDialog dbcDialog;
    QFileDialog db2Dialog;
    QFileDialog saveDialog;

    struct
    {
        int records;
        int fields;
        int sizeOfRecord;
        int StringSize;
        int tableHash;
        int build;
        int locales;
    } dbFileInfo;
};

#endif // DBCVIEWER_H
