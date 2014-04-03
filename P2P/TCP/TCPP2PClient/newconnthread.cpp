#include "newconnthread.h"

newConnThread::newConnThread(QMutex *lk, QString *d, int *sF, int ID, QLinkedList<Data> *s, QObject *parent) :
    QThread(parent)
{
    //this is a thread that was started to handle a new client
    //connecting directing to this peer.
    lock = lk;
    data = d;
    sysFrame = sF;
    threadFrame = *sysFrame;
    socketDescriptor = ID;
    sendData = s;
}

newConnThread::~newConnThread()
{

}

void newConnThread::run()
{
    //this is where the thread actually starts.
    socket = new QTcpSocket;
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        exit(1);
    }
    //cool. we've got a connection.
    //setup timer
    timer = new QTimer;
    timer->start(500);

    //time to connect some signals and slots.
    connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(handleDisconnected()));
    connect(timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    connect(this,SIGNAL(timeSig()),this,SLOT(handleWrite()));
    //make the thread run even when this run function goes out of scope.
    exec();
}

void newConnThread::handleReadyRead()
{
    //this slot will handle what happens when the socket has something to read.
    //socket has prepacked data. which is pretty cool. just add.
    QString temp;
    temp = socket->readAll();
    lock->lock();
    data->append(temp).append('\n');
    lock->unlock();
}

void newConnThread::handleTimeout()
{
    //this handles changing the permissions of the socket so that
    //the timer can control the writing indirectly.
    emit timeSig();
}

void newConnThread::handleDisconnected()
{
    //this is what happens when the socket is disconnected.
    //since this is a thread that was created by someone connecting TO
    //the server, nothing really needs to happen.
    socket->deleteLater();
    newConnThread::exit();
}

void newConnThread::handleWrite()
{
    //this slot handles sending all data that hasn't been sent to the socket
    //that corresponds with this thread to the client.
    QLinkedList<Data>::Iterator it;
    for(it=sendData->begin();it!=sendData->end();it++)
    {
        if(it->frame == threadFrame)
        {
            socket->write(it->text.toUtf8());
            socket->flush();
            threadFrame++;
        }
    }
}
