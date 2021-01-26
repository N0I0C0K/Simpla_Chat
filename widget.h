#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QTextCodec>
#include <QTextDecoder>
#include <QByteArray>

#include "chatwid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void login();
private:
    QTextDecoder *decoder;
    ChatWid *chatwid;
    Ui::Widget *ui;
    QTcpSocket *myclient;
    QString ip = "127.0.0.1"; //39.105.179.235
    int port = 8110;
};
#endif // WIDGET_H
