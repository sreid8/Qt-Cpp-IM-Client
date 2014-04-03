#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    socket = new QUdpSocket;
    if(!socket->bind(QHostAddress::Any,8065))
    {
        exit(1);
    }
    //socket is open for business.
    connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()),Qt::DirectConnection);
    //socket should be ready.
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    socket->deleteLater();
}

void MainWindow::handleReadyRead()
{
    char stuff[1000];
    qint64 bytesRecv;
    quint16 peerPort;
    QHostAddress peerAddr;
    bytesRecv = socket->pendingDatagramSize();
    socket->readDatagram(stuff,bytesRecv,&peerAddr,&peerPort);
    ui->textBrowser->append(stuff);
    ui->textBrowser->append("\n");
}

void MainWindow::on_pushButton_clicked()
{
    //send button clicked
    QString temp;
    QHostAddress addr("192.168.1.255");
    temp.clear();
    temp.append("<").append(name).append(">: ");
    temp.append(ui->lineEdit->text());
    //okay, now to send.
    socket->writeDatagram(temp.toUtf8(),addr,8065);
}
