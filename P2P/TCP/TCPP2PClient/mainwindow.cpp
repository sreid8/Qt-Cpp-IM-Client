#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	sysFrame=0;
    startDialog dia(&regPort,&name,&regAddr);
    dia.setModal(true);
    dia.exec();
    //after this, all the correct parameters have been set.
    lock = new QMutex;
    timer = new QTimer;
    serv = new Server(lock,&msgs,&sendData,&sysFrame,regAddr,regPort);
    serv->StartServer();
	 timer->start(500); //every half second, the awesome window will update
	 connect(timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    //server has been started, all client are connecting or are connected.
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete serv;
    delete ui;
}

void MainWindow::handleTimeout()
{
    ui->textBrowser->clear();
    ui->textBrowser->setText(msgs);
    ui->textBrowser->repaint();
}

void MainWindow::on_pushButton_clicked()
{
    //this is when the user has clicked the button.
    QString temp;
    Data tempData;
    temp=ui->lineEdit->text();
    ui->lineEdit->clear();
    lock->lock();
    tempData.frame=sysFrame;
    tempData.text=temp;
    sendData.append(tempData);
    sysFrame++;
    lock->unlock();
}
