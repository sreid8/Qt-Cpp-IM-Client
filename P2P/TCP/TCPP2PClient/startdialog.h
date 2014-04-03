#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit startDialog(int *p, QString *n, QString *a, QWidget *parent = 0);
    ~startDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::startDialog *ui;
    int* regPort;
    QString *regAddr;
    QString *name;
};

#endif // STARTDIALOG_H
