#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(QString *n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    name = n;
    ui->setupUi(this);
}

startDialog::~startDialog()
{
    delete ui;
}

void startDialog::on_pushButton_clicked()
{
    *name = ui->lineEdit->text();
    startDialog::close();
}
