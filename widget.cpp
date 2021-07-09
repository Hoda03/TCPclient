#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpsocket = NULL;
    tcpsocket = new QTcpSocket(this);
    connect(tcpsocket, &QTcpSocket::connected, [=](){
        ui->textEdittread->setText("client");
    });
    connect(tcpsocket, &QTcpSocket::connected, [=](){
        QByteArray array = tcpsocket-> readAll();
        ui -> textEdittread -> append(array);
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_send_clicked()
{
    if(tcpsocket == NULL)
        return;
    QString str = ui -> textEdit -> toPlainText();

    tcpsocket -> write(str.toUtf8().data());

}


void Widget::on_close_clicked()
{
    if(tcpsocket == NULL)
        return;
    tcpsocket -> disconnectFromHost();
    tcpsocket -> close();
    tcpsocket = NULL ;

}


void Widget::on_pushButton_clicked()
{
    QString ip = ui -> lineEditip ->  text();
    qint16 port = ui -> lineEditport -> text().toInt();
    tcpsocket -> connectToHost (ui -> lineEditip ->  text(),port);

}

