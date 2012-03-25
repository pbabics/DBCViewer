#ifndef DBCVIEWER_H
#define DBCVIEWER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
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

    void on_actionOpen_triggered();

    void LoadIntoTable(QString file);

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::DBCViewer *ui;
};

#endif // DBCVIEWER_H
