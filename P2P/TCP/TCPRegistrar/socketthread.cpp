#include "socketthread.h"

socketThread::socketThread(QMutex *lk, QLinkedList<User> *us, User *u, int ID, QObject *parent)
	: QThread(parent)
{
	socketDescriptor = ID;
	users = us;
	newestUser = u;
	lock = lk;
}

socketThread::~socketThread()
{
}

void socketThread::run()
{
	//This is where the thread goes on entry. Handles some stuff.
	QLinkedList<User>::Iterator it;
	User tempUser;
	int i;
	qDebug() << socketDescriptor << "Starting thread";
	socket = new QTcpSocket;
	if(!socket->setSocketDescriptor(socketDescriptor))
	{
		emit error(socket->error());
		return;
	}
	//thread is definetly connected. First thing I do is send send all data to client.
	for(i=0;i<15000;i++); //need to waste time to see if it fixes an error of sending ips to the client.
	lock->lock();
	for(it=users->begin();it!=users->end();it++)
	{
		//iterate across the array of users and send client all of them.
		socket->write(it->ip.toUtf8());
		socket->waitForBytesWritten();
		//socket->flush();
		for(i=0;i<5000;i++); //waste some time between sending.
	}
	numberPeers = users->size();
	//client now has all of the data. awesome.
	//time to add client to the list of users.
	tempUser.ip = socket->peerAddress().toString();
	users->append(tempUser);
	*newestUser = tempUser; //need an assignment operator for User... probably a copy constructor too.
	lock->unlock();
	//next we have to start the timer, do all the connections.
	connect(socket,SIGNAL(disconnected()),this,SLOT(handleDisconnected()),Qt::DirectConnection);
	connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()),Qt::DirectConnection);
	//make the thread stay existent even when this function has finished.
	exec();
}

void socketThread::handleReadyRead()
{
	//this is where the thread will handle reading from the client.... honestly, there should be nothing here.
	//that was an easy function.. I don't know why I bothered with this.
}

void socketThread::handleDisconnected()
{
	//this is what happens when a client disconnects.
	qDebug() << "Client disconnected";
	QLinkedList<User>::Iterator it;
	lock->lock();
	for(it=users->begin();it!=users->end();it++)
	{
		//go through the list, find the one that matches you, remove it. This should also happen to all the clients thast are connected to the client. This is just an aside.
		if(socket->peerAddress().toString() == it->ip)
		{
			users->erase(it);
			goto end; //because if you don't break, then you'll have a memory access violation.
		}
	}
end: lock->unlock(); //use this as a go to point for breaking out of the loop.
	socket->deleteLater();
	socketThread::exit();
}

/*This is another function that I do not need.
void socketThread::handleTimeout() //this slot exists only to handle the fact that sockets cannot be signaled by anything other than themselves or the class they belong to. So I just use a signal to emit a signal so that it looks like the parent calls the socket to write.
{
	emit timeSig();
}*/

/* Decided I didn't need this. The client is able to recieve connections.
void socketThread::handleWrite()
{
	 This is where the thread checks to see if the size of the user list
	is equal to the number of peers that the thread has sent to the client.
	If it doesn't, it sends the most recent.
	This is EXTREMELY dependent on the fact that I really doubt people will
	connect to this server faster than one every quarter of a second.
	
	For future reference, I think there has to be a better way to do this.
	I mean, there has to be a way I can signal all threads to send a
	new user. But I don't have time to research the issue.
	QLinkedList<User>::Iterator it;
	lock->lock();
	if(users->size() != numberPeers)
	{
		it = users->end(); //because we know we add users in the back of the list
		socket->write(it->ip.toString().toUtf8());	
	}
	lock->unlock();
}*/

