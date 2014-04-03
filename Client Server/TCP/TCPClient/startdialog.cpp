#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(QString *serv, int *port, QString *name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    serverAddr = serv;
    serverPort = port;
    user = name;
    ui->setupUi(this);
}

startDialog::~startDialog()
{
    delete ui;
}

void startDialog::on_pushButton_clicked()
{
    *serverAddr = ui->serverAddr->text();
    *serverPort = ui->portNumber->text().toInt();
    *user = ui->username->text();
    startDialog::close();
}
