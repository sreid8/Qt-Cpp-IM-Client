#ifndef REGHANDLE_H
#define REGHANDLE_H

#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QLinkedList>
#include "manualthread.h"
#include "data.h"

class RegHandle : public QThread
{
	Q_OBJECT

public:
	RegHandle(QString regIP, QMutex *lk, QString *m, int *sF, QLinkedList<Data> *d, QObject *parent=0);
	~RegHandle();
	void run();

public slots:
	void handleReadyRead();

private:
	QTcpSocket *socket;
	QString ip;
	QMutex *lock;
	QString *msgs;
	int *sysFrame;
	QLinkedList<Data> *data;
};

#endif // REGHANDLE_H
