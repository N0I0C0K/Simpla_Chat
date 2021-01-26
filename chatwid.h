#ifndef CHATWID_H
#define CHATWID_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>
#include <QTextDecoder>
#include <QTextCodec>
#include <QByteArray>
#include <QEvent>
#include <QKeyEvent>

namespace Ui {
class ChatWid;
}

class ChatWid : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWid(QTcpSocket *client, QString username, QWidget *parent = nullptr);
    QString getCurrentTime();
    ~ChatWid();


signals:
    void chatClose();

public slots:
    void recvMsg();
    void sendMsg();
private:
    QTextDecoder *decoder;
    QString username;
    QTime current_time;
    Ui::ChatWid *ui;
    QTcpSocket *client;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    //virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // CHATWID_H
