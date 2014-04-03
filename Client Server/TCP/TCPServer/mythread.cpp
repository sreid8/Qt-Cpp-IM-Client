#include "mythread.h"
QMutex lock;

mythread::mythread(QMutex *lk, int *frm, int ID,QLinkedList<frameData> *dat,QLinkedList<threadFrame> *list, QObject *parent) :
QThread(parent)
{
	this->socketDescriptor = ID;
	this->sendData = dat;
	this->sysFrameList = list;
	this->frame = *frm;
	this->sysFrame = frm;
	this->lock = lk;
}

void mythread::run()
{
	//thread starts here
	//unneeded
	//QLinkedList<Data>::iterator Dit;
	//QLinkedList<User>::iterator Uit;
	threadFrame myFrame;
	QTimer *timer = new QTimer(0);
	
	
	timer->start(10); 
	qDebug() << socketDescriptor << "Starting thread";
	socket = new QTcpSocket();
	if (!socket->setSocketDescriptor(this->socketDescriptor))
	{
		emit error(socket->error());
		return;
	}
	myFrame.frame = *sysFrame;
	myFrame.socketDescriptor=this->socketDescriptor;
	sysFrameList->append(myFrame);
	connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
	connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
	connect(timer,SIGNAL(timeout()),this,SLOT(timeUp()),Qt::DirectConnection); //still need this.
	connect(this,SIGNAL(timeSig()),this,SLOT(readyWrite()),Qt::DirectConnection);

	qDebug() << socketDescriptor << "Client connected.";
	QMutex lock;



	exec(); //thread will stay alive until we tell it to close
}


void mythread::readyRead()
{ //this will change
	int flag=0;
	QString::iterator it;
	frameData tempData;
	QByteArray stuff = socket->readAll();
	qDebug() << stuff;
	QString stuffText,testName, msgTemp;
	stuffText.clear();
	qDebug() << socketDescriptor << "Data in: " << stuff;



	//for individual messaging registration.... old code.
	/*if (stuff == "REG\n") //client would like to register. next message should be username
	{//need to add check to see if user exists
		socket->write("ACK");//this is a hard ack that tells the client that it may write to the socket and be heard by the server.
		socket->flush();
		stuff.clear(); //verify that buffer is cleared.
		socket->waitForReadyRead();
		stuff=socket->readAll();//should have username followed by \n
		stuffText = stuff; //move it to a string so that I can manually remove the \n and then add it to the users list.
		stuffText.remove('\n'); //hopefully removes the \n
		//Need to check to see if users already exists.
		for(Uit=users->begin();Uit!=users->end();Uit++)
		{
			testName = Uit->getName();
			if(testName == stuffText) //if this is true, then the user exists and we need to act on it
			{
				socket->write("user already exists");
				socket->flush();
				socket->close();
				flag=1;
				break;
			}
		}
		//now to add to the user list, completing the register process.
		if(!flag) //this way the user doesn't get double added if the user name matched.
		{
			temp.setName(stuffText);
			temp.setDescriptor(this->socketDescriptor);//temp user configured. time to add
			lock.lock();
			users->append(temp);
			lock.unlock();
			//clean up
			stuff.clear();
			stuffText.clear();
			temp.clear();
			stuff="ACK";
			socket->write("ACK");
			socket->flush();
		}
		flag=0;
		stuff.clear();
	}
	*/
	if(stuff=="REG\n") // set client username internal to the thread. No need to do much else.
	{
		socket->write("ACK");
		socket->flush();
		//socket->flush();
		socket->waitForReadyRead();
		stuff=socket->readAll();
		name=stuff;
		if(-1==socket->write("ACK"))//to finalize name registration.
		{
                qDebug() << "error2";
		}
		socket->flush();
	} //done...... much easier than before... wow.


	if(stuff=="REGJ\n") // set client username internal to the thread. No need to do much else.
	{
		socket->write("ACK\n");
		socket->flush();
		//socket->flush();
		socket->waitForReadyRead();
		stuff=socket->readAll();
		name=stuff;
		if(-1==socket->write("ACK\n"))//to finalize name registration.
		{
				qDebug() << "error2";
		}
		socket->flush();
	}

	if(stuff=="MSG\n") //client would like to send a message.
	{
		
		//socket->write("ACK\n");
		//socket->flush();
		qDebug() << socket->isOpen();
		socket->waitForReadyRead();
		stuff=socket->readAll();
		//socket->waitForReadyRead();
		qDebug() << stuff;
		msgTemp.clear();
		msgTemp = '<';
		msgTemp.append(name);
		msgTemp.append(">: ");
		msgTemp.append(stuff);
		msgTemp.append('\n');
		lock->lock(); //I'm messing with the shared memory here... make sure to lock
		tempData.setData(msgTemp.toUtf8());
		tempData.setFrame(*sysFrame);
		sendData->append(tempData);
		(*sysFrame)++;
		lock->unlock();
		//socket->write("ACK");
		//socket->flush();
	} //much easier.

}


	/*if (stuff == "MSG\n")
	{
		socket->write("ACK");
		socket->flush();
		stuff.clear();
		socket->waitForReadyRead(); //change to a more intelligent wait routine to wait for new data to be available
		stuff=socket->readAll();
		stuffText = stuff;
		stuffText.remove('\n');
		//check if sender exists
		lock.lock();
		for(Uit=users->begin();Uit!=users->end();Uit++)
		{
			if(Uit->getName() == stuffText) //found that the userName exists
			{
				flag=1;
				break;
			}
		}
		lock.unlock();
		if(flag==1)
		{
			flag=0;
			socket->write("ACK");
			socket->flush();
			//ready for reciever name
			socket->waitForReadyRead(); 
			stuff=socket->readAll();
			stuffText.clear();
			stuffText = stuff;
			stuffText.remove('\n');
			//check if receiver exists
			for(Uit=users->begin();Uit!=users->end();Uit++)
			{
				if(Uit->getName() == stuffText)
				{
					flag=1; //receiever exists
					temp=*Uit;
				}
			}
			if(flag==1)
			{
				//move data to data queue
				flag=0;
				//time to get the message. 
				stuff.clear();
				stuffText.clear();
				socket->write("ACK");
				socket->flush();
				socket->waitForReadyRead();
				stuff=socket->readAll();
				stuffText=stuff;
				//I've got the message, time push to the right socket.
				dData.setData(stuff);
				dData.setDescriptor(temp.getDescriptor());
				dData.setName(temp.getName());
				dData.setSendDescriptor(this->socketDescriptor);
				data->append(dData); //data was added to the queue.
				socket->write("ACK");
				socket->flush();
				//				emit readyWriteSig();
			}
			else
			{
				socket->write("Didn't exist");
				socket->flush();
			}
		}
	}
	*/
	//completely unneeded old code.... could be potentially used for a more full-featured messenger app later on, which is why I'm keeping it
	/*if(stuff == "UNREG\n") /// this is showing as always true.... why?
	{
		socket->write("ACK");
		socket->waitForReadyRead(); //change to a more intelligent wait routine
		stuff=socket->readAll();
		stuffText=stuff;
		stuffText.remove('\n');
		for(Uit=users->begin();Uit!=users->end();Uit++)
		{
			if(Uit->getName()==stuffText)
			{
				users->erase(Uit); //found it, erasing it to unregister
				break; //stop looping.
			}
		}
		socket->write("ACK"); //on this ack, client will know to close the socket, which will close this thread.

	}

	//list command. tells the client who the list of current online users are.
	if(stuff == "LIST\n")
	{
		socket->write("ACK");
		socket->flush();
		socket->waitForReadyRead();
		stuff=socket->readAll();
		if(stuff=="ACK")
		{
			qDebug() << "Beginning to search online user list.";
			//now to search user list
			for(Uit=users->begin();Uit!=users->end();Uit++)
			{//test to see if user that is in the list == the user who asked. don't want to list the user who asked to the user. that'd be idiotic.
				if(!(Uit->getDescriptor() == socketDescriptor)) // this will fire as long as the person who asked doesn't equal the person in the list that we're on
				{
					socket->write(Uit->getName().toUtf8());
					socket->flush();
					qDebug() << "Wrote name: " << Uit->getName();
					stuff.clear();
					socket->waitForBytesWritten();
					stuff = socket->readAll();
					qDebug() << "Got response: " << stuff;
					if(stuff!="ACK") //something went wrong with the transmission of the list items
					{
						break;
					}
				}
			}
		}
		//socket->write("ACK"); //tells the client that we're done.
		stuff.clear(); //so that the thread doesn't loop.
		qDebug() << "Finished.";
	}
}*/


		







void mythread::disconnected()
{
	//THIS IS WHERE YOU ARE
	QLinkedList<threadFrame>::iterator fit;
	qDebug() << "Client " << socketDescriptor << "has disconnected from the server.";
	//remover the thread from the list of frames... because if the thread isn't removed, then the system cleanup will never be able to work right.
	lock->lock(); //I only want one person playing around with the shared variables.
	for(fit=sysFrameList->begin();fit!=sysFrameList->end();fit++)
	{
		//search for yourself in the list, remove yourself.
		if(fit->socketDescriptor == this->socketDescriptor)
		{
			//found myself, need to remove.
			sysFrameList->erase(fit);
			break; //memory accesss issues if you erase something then do not break.
		}
	}
	lock->unlock();
	socket->deleteLater();
	mythread::exit();
}
	
//this is old disconnected code. not important unless I wanted to implement an actual, individual messaging IM client/server
/*qDebug() << socketDescriptor << "client disconnected ";
	//should go through a special unreg process to remove disconnected user from list.
	//you know, I think I'll do that now.
	//first to delete the reference in the user list
	QLinkedList<User>::iterator uit;
	QLinkedList<Data>::iterator dit;
	int flag =1;
	for(uit=users->begin();uit!=users->end();uit++)
	{
		if(uit->getDescriptor()==socketDescriptor) //if this is true, then the user that had this socket was found in the user list... won't be found if the user was able to issue the proper unreg command first
		{
			users->erase(uit);
			break; //have to break because when something is removed from a linked list, all iterators and pointers are invalidated.
		}
	}
	//also remove any data that might be left over wasting my RAM and so forth...
	if(flag)
	{
		for(dit=data->begin();dit!=data->end();dit++)
		{
			if(dit->getDescriptor()==socketDescriptor)//if true, found some data for that was for the socket. removing that.
			{
				data->erase(dit);
				flag=1; //until no data is found, I want to keep looking.
				break;
			}
			else flag=0; //if no data is found, no need to continue to loop
		}
	}
	socket->deleteLater();
	exit(0);*/


void mythread::readyWrite() 
{
	//this method will compare the thread's current frame with what's in the sendData memory. if the frame that's in there is equal to or greater than the frame, the method will send that data. the messages should be in order, anyway.
	QLinkedList<frameData>::iterator it;
	QLinkedList<threadFrame>::iterator fit;
	QString response;
	bool flag=false;
	lock->lock();
	for(it=sendData->begin();it!=sendData->end();it++)
	{
		if(it->getFame()==this->frame) // using == because the increment each time through will cause the == to change and I don't want to repeat messages
		{
			response = it->getData();
			socket->write(response.toUtf8());
			socket->flush();
			//doing an ACK to synchronize when the client expects more data.
			this->frame++;
			flag=true; //this flag tells if data was ever sent... because if none was ever sent, then there's no reason for me to be randomly bothering the client with the finish that is below.
		}
	}
	//if(flag)
	//{
	//	flag=false;
	//	socket->write("FIN");
	//	socket->flush();
//	}
	//have to update system level frame number. otherwise issues.
	for(fit=sysFrameList->begin();fit!=sysFrameList->end();fit++)
	{
		if(fit->socketDescriptor==this->socketDescriptor)
		{
			//found this thread
			fit->frame = this->frame;
		}
	}
	lock->unlock();
}
	


//old readyWrite code. useful for actual IM client maybe one day
/*QMutex lock;
	QLinkedList<Data>::iterator it;
	QLinkedList<User>::iterator uit;
	QString stuff;
	//critical section
	lock.lock();
	//////////////////////////SOME OF THIS CODE UNTESTED. PLEASE TEST WHEN CLIENT IS MORE OPERATIONAL /////////////////////////////
	for(it=data->begin();it!=data->end();it++)
	{
		if(it->getDescriptor() ==  socketDescriptor) // data belongs to this socket
		{
			for(uit=users->begin();uit!=users->end();uit++)
			{
				if(uit->getDescriptor() == it->getSendDescriptor())	//found the sender
				{
					socket->write(uit->getName().toUtf8());
					socket->flush();
				}
			}
			//socket->write(it->getName().toUtf8());//to send the sender name
			socket->flush();
			socket->waitForReadyRead();
			stuff=socket->readAll();
			if(stuff=="ACK");
			{
				socket->write(it->getData()); //changed without testing. can't see it giving any QSocketNotifier errors, but we'll see later.
				data->erase(it);
				break;
			}
		}
	}
	lock.unlock(); //unlocked so that other threads can access to write data into this lst.*/


void mythread::timeUp() //probably does not need to be remade.
{
	emit timeSig();
}
