#include "manualthread.h"

manualThread::manualThread(QString ip, QMutex *lk, QString *d, int *sF, QLinkedList<Data> *s, QObject *parent) :
    QThread(parent)
{
    //this type of thread is one that is called when the
    //client is connecting TO another client, not another
    //client connecting to this.
    lock = lk;
    data = d;
    sysFrame = sF;
    threadFrame = *sysFrame;
    sendData = s;
    hostAddr = ip;
}

void manualThread::run()
{
    //this is where the thread starts.
    socket = new QTcpSocket;
	QHostAddress temp(hostAddr);
    socket->connectToHost(temp,8061);
    if(!socket->waitForConnected())
    {
        //socket failed to connect.
        exit(1);
    }
    else {;}
    //now the socket is connected. next is to set up the timer
    timer = new QTimer;
    timer->start(500); //every half second, check for new send data.
    //connect signals and slots
    connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(handleDisconnected()));
    connect(timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    connect(this,SIGNAL(timeSig()),this,SLOT(handleWrite()));
    //now to make this thread continue even after run goes out of scope.
    exec();
}

void manualThread::handleReadyRead()
{
    //this function does the same thing as the newConnThread one
    //does, therefore, copy and paste.
    QString temp;
    temp = socket->readAll();
    lock->lock();
    data->append(temp).append('\n');
    lock->unlock();
}

void manualThread::handleDisconnected()
{
    //when a thread disconnects from this one, it means that
    //the other client disconnected, and as such, there's not much
    //that I have to handle other than closing the thread and
    //deleting the socket.
    socket->deleteLater();
    manualThread::exit();
}

void manualThread::handleTimeout()
{
    //see description in newConnThread
    emit timeSig();
}

void manualThread::handleWrite()
{
    //this is going to be the same as the other thread.
    //copy and paste.
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
