#include "chatwid.h"
#include "ui_chatwid.h"

ChatWid::ChatWid(QTcpSocket *client, QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWid)
{
    ui->setupUi(this);
    this->client = client;
    this->username = username;
    this->decoder = QTextCodec::codecForName("UTF-8")->makeDecoder();
    //this->grabKeyboard();
    //this->current_time = QTime::currentTime();
    connect(client, &QTcpSocket::readyRead, this, &ChatWid::recvMsg);
    connect(ui->sendBtn, &QPushButton::clicked, this, &ChatWid::sendMsg);
}

void ChatWid::recvMsg()
{
    /*char recvMsg[128];
    int recvRe = client->read(recvMsg, 128);
    if(recvRe == -1){
        ui->textBro->append("[error in this text]");
    }
    ui->textBro->append(getCurrentTime()+decoder->toUnicode(recvMsg, qstrlen(recvMsg)));*/
    QByteArray data_ = client->read(128);
    ui->textBro->append(getCurrentTime()+decoder->toUnicode(data_));
}

void ChatWid::sendMsg()
{
    QString data = ui->textEdit->toPlainText();
    //QString time = "["+QString(current_time.hour())+":"+QString(current_time.minute())+":"+QString(current_time.second())+"]";
    data = username+":"+data;
    const char* str = data.toUtf8().toStdString().c_str();
    int recvRe = client->write(str,qstrlen(str));
    client->waitForBytesWritten();
    ui->textEdit->setText("");
    if(recvRe == -1){
        return;
    }
    ui->textBro->append(getCurrentTime()+data);
}

QString ChatWid::getCurrentTime()
{
    QDateTime date(QDateTime::currentDateTime());
    QString time = "["+date.toString("hh:mm:ss")+"] ";
    return time;
}

void ChatWid::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return){
        sendMsg();
        return;
    }
    QWidget::keyPressEvent(event);
}

ChatWid::~ChatWid()
{
    delete ui;
    qDebug()<<"chatwid has realsed";
    emit chatClose();
}
