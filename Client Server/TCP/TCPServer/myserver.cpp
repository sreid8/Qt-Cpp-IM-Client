#include "myserver.h"
using namespace::std;
QLinkedList<frameData> *data;
QLinkedList<threadFrame> *frameList;

int *sysFrame;

myserver::myserver(QObject *parent) :
    QTcpServer(parent)
{
}

myserver::~myserver() //just because I hate memory leaks.
{
	delete data;
	delete frameList;
}

void myserver::StartServer()
{
	timer = new QTimer;
	timer->start(300000); //this is a timer that will fire ever 5 minutes to clean unneeded messages.
	connect(timer,SIGNAL(timeout()),this,SLOT(cleanUp())); //connects the timer's timeout signal with the cleanup method.
	lock = new QMutex;
	data = new QLinkedList<frameData>;
	frameList = new QLinkedList<threadFrame>;
	sysFrame = new int;
	*sysFrame = 0;
    if(!this->listen(QHostAddress::Any,8060))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening on port 8060";
    }
}

void myserver::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << "Connecting ...";
    mythread *thread = new mythread(lock, sysFrame,socketDescriptor,data, frameList, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void myserver::cleanUp()
{
	//this is the cleanup slot. basically iterates through the list and everything that has a frame number before the most recent frame number is removed. This helps remove server load.
	QLinkedList<threadFrame>::iterator fit;
	QLinkedList<frameData>::iterator dit;
	int frame=*sysFrame;
	bool flag=true;
	lock->lock(); //don't want any other threads to access, or to interrupt any other threads currently using this data.
	//first to find the lowest frame number.
	for(fit=frameList->begin();fit!=frameList->end();fit++)
	{
		if(fit->frame < frame)
		{
			frame = fit->frame;
		}
	}//now I've got the lowest current frame.

begin: while(flag)
	   {
		   for(dit=data->begin();dit!=data->end();dit++)
		   {
			   flag = false;
			   if(dit->getFame() < frame)
			   {
				   data->erase(dit); //this invalidates the interator and needs to make the loop start all over.
				   flag = true;
				   goto begin;
			   }
		   }
	   }
	   lock->unlock();
}
