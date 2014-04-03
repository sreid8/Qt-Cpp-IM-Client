#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startupdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    serverAddr = new QString;
    serverPort = new quint16;
    startupDialog start(serverAddr,serverPort,this);
    start.setModal(true);
    start.exec();
    socket = new QUdpSocket(0);
    socket->bind(QHostAddress::Any,1234);
    ui->setupUi(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
}

MainWindow::~MainWindow()
{
    socket->close();
    delete socket;
    delete ui;
    delete serverAddr;
    delete serverPort;
}

void MainWindow::handleReadyRead()
{
    char str[100];
	QString tempString;
    qint64 size;
    QByteArray temp;
    quint16 tempPort;
    QHostAddress tempAddr;
    ui->lineEdit_2->clear();
    size = socket->pendingDatagramSize();
	socket->readDatagram(str,size,&tempAddr,&tempPort);
	tempString.clear();
	for(int i=0;i<size;i++)
	{
		tempString.append(str[i]);
	}
    //tempString.append(str);
	ui->lineEdit_2->clear();
    ui->lineEdit_2->setText(tempString);
}

void MainWindow::on_pushButton_clicked()
{
    QString temp;
    QHostAddress tempAddr(*serverAddr);
    temp = ui->lineEdit->text();
	QByteArray data(temp.toUtf8());
    ui->lineEdit->clear();
    socket->writeDatagram(data,tempAddr,*serverPort);
    socket->flush();
}
