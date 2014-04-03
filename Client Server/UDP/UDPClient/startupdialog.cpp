#include "startupdialog.h"
#include "ui_startupdialog.h"

startupDialog::startupDialog(QString *server, quint16 *port,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startupDialog)
{
    serverAddr = server;
    serverPort = port;
    ui->setupUi(this);
}

startupDialog::~startupDialog()
{
    delete ui;
}

void startupDialog::on_pushButton_clicked()
{
    *serverAddr = ui->lineEdit->text();
    *serverPort = (quint16)ui->lineEdit_2->text().toUShort();
    startupDialog::close();

}
