#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(int *p, QString *n, QString *a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    regPort = p;
    regAddr = a;
    name = n;
    ui->setupUi(this);
}

startDialog::~startDialog()
{
    delete ui;
}

void startDialog::on_pushButton_clicked()
{
    //this is where the client has clicked the connect button.
    *regAddr = ui->lineEdit->text();
    *regPort = ui->lineEdit_2->text().toInt();
    *name = ui->lineEdit_3->text();
    startDialog::close();
}
