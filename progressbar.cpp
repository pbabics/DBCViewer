#include "progressbar.h"
#include "ui_progressbar.h"

ProgressBar::ProgressBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressBar),
    closeManualy(false)
{
    ui->setupUi(this);
}

ProgressBar::~ProgressBar()
{
    delete ui;
}


void ProgressBar::Show(unsigned int maximum, QString progressName, bool manualyClose, unsigned int currentProgress)
{
    ui->progressBar->setMaximum(maximum);
    ui->label->setText(progressName);
    ui->progressBar->setValue(currentProgress);
    closeManualy = manualyClose;
    this->open();
}

void ProgressBar::Close()
{
    closeManualy = false;
    this->close();
}

void ProgressBar::UpdateProgress(unsigned int currentProgress)
{
    ui->progressBar->setValue(currentProgress);
}

unsigned int ProgressBar::GetProgress() const
{
    return ui->progressBar->value();
}

void ProgressBar::IncrementProgress()
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
}

void ProgressBar::UpdateTitle(QString title)
{
    ui->label->setText(title);
}

void ProgressBar::on_progressBar_valueChanged(int value)
{
    if (!closeManualy && value == ui->progressBar->maximum())
        this->close();
}
