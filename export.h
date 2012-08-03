#ifndef EXPORT_H
#define EXPORT_H

#include <QDialog>

namespace Ui {
class DBCViewer;
class Export;
}

class Export : public QDialog
{
    Q_OBJECT

public:
    explicit Export(QWidget *parent = 0);
    ~Export();

    QString getTableName() const;
    bool getExportData() const;
    bool getCreateTable() const;

    bool getExportSingleInsert() const;
    unsigned int getRowsPerInsert() const;

private slots:
    void on_ExportData_clicked();

    void on_MultipleRows_clicked();

    void on_SingleRow_clicked();

protected:
    Ui::Export *ui;
};

#endif // EXPORT_H
