#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>

namespace Ui {
class startupDialog;
}

class startupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit startupDialog(QString *server, quint16 *port, QWidget *parent = 0);
    ~startupDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::startupDialog *ui;
    QString *serverAddr;
    quint16 *serverPort;
};

#endif // STARTUPDIALOG_H
