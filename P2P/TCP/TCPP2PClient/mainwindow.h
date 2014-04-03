#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLinkedList>
#include <QMutex>
#include <QTimer>
#include "data.h"
#include "startdialog.h"
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void handleTimeout();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QMutex *lock;
    QString regAddr;
    int regPort;
    QString name;
    QLinkedList<Data> sendData;
    int sysFrame;
    QString msgs;
	Server *serv;
};

#endif // MAINWINDOW_H
