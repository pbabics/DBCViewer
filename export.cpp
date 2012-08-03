#include "export.h"
#include "ui_export.h"

Export::Export(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Export)
{
    ui->setupUi(this);
}

Export::~Export()
{
    delete ui;
}

bool Export::getExportData() const
{
    return ui->ExportData->checkState() == Qt::Checked;
}

bool Export::getCreateTable() const
{
    return ui->CreateTable->checkState() == Qt::Checked;
}

bool Export::getExportSingleInsert() const
{
    return ui->SingleRow->isChecked();
}

QString Export::getTableName() const
{
    return ui->tableName->text();
}

unsigned int Export::getRowsPerInsert() const
{
    return ui->rowsPerInsert->text().toUInt();
}


void Export::on_ExportData_clicked()
{
    ui->groupBox->setEnabled(ui->ExportData->checkState() == Qt::Checked);
}

void Export::on_MultipleRows_clicked()
{
    ui->label->setEnabled(true);
    ui->rowsPerInsert->setEnabled(true);
}

void Export::on_SingleRow_clicked()
{
    ui->label->setEnabled(false);
    ui->rowsPerInsert->setEnabled(false);
}
