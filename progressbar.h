#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QDialog>

namespace Ui {
class ProgressBar;
}

class ProgressBar : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProgressBar(QWidget *parent = 0);
    ~ProgressBar();

    void Show(unsigned int maximum, QString progressName, bool manualyClose = false, unsigned int currentProgress = 0);
    void Close();
    void UpdateProgress(unsigned int currentProgress);
    void UpdateTitle(QString progressName);
    void IncrementProgress();
    unsigned int GetProgress() const;
    
private slots:
    void on_progressBar_valueChanged(int value);

private:
    Ui::ProgressBar *ui;
    bool closeManualy;
};

#endif // PROGRESSBAR_H
