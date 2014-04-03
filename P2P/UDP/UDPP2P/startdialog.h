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
    explicit startDialog(QString *n, QWidget *parent = 0);
    ~startDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::startDialog *ui;
    QString *name;
};

#endif // STARTDIALOG_H
