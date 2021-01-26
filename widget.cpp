#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->myclient = new QTcpSocket();
    decoder = QTextCodec::codecForName("utf-8")->makeDecoder();
    //connect(this->myclient, &QTcpSocket::connected, this, &Widget::onConnected);
    connect(this->ui->loginBtn, &QPushButton::clicked, this, &Widget::login);
}

void Widget::login()
{
    myclient->connectToHost(this->ip, this->port);
    if(!myclient->waitForConnected())
    {
        qDebug()<<"error can not connect to host";
        return;
    }
    QString username = ui->usernameEdit->text();
    QString passworld = ui->passworldEdit->text();
    if(username == "" || passworld == ""){
        return;
    }
    QString data = username+";"+passworld;
    int sendRe = myclient->write(data.toUtf8());
    if(!myclient->waitForBytesWritten()){
        qDebug()<<"error in send data";
        return;
    }
    if(sendRe == -1)
    {
        qDebug()<<"error in send data";
        return;
    }
    if(!myclient->waitForReadyRead()){
        return;
    }
    char recvMsg[64];
    int recvRe = myclient->read(recvMsg, 64);
    if(recvRe == -1){
        qDebug()<<"error in recv data";
    }
    QString aa(recvMsg);
    qDebug()<<aa;
    if(aa == "success")
    {
        chatwid = new ChatWid(this->myclient, username);
        //connect(chatwid, SIGNAL(chatClose()), this,)
        this->hide();
        chatwid->show();
        ui->passworldEdit->setText("");
        return;
    }
    else
    {
        qDebug()<<"passworld error";
        ui->passworldEdit->setText("");
    }
}

Widget::~Widget()
{
    myclient->disconnectFromHost();
    myclient->waitForDisconnected();
    delete ui;
    delete chatwid;
    delete myclient;
    qDebug()<<"widget has released";
}

