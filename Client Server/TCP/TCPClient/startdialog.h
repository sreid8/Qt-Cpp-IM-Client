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
    explicit startDialog(QString *serv, int *port, QString *name, QWidget *parent = 0);
    ~startDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::startDialog *ui;
    QString *serverAddr;
    int *serverPort;
    QString *user;
};

#endif // STARTDIALOG_H
