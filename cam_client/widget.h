#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTcpSocket>
#include <QPushButton>
#include <QHostAddress>
#include <QDebug>
#include <QPixmap>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void startv()
    {
        readsize = true;

        sockv = new QTcpSocket(this);
        connect(sockv, SIGNAL(readyRead()), this, SLOT(recv_show()));
        sockv->connectToHost(QHostAddress(leip->text()), atoi(leport->text().toStdString().c_str()));
        btstart->setText("STOP");
        leip->setDisabled(true);
        leport->setDisabled(true);

        disconnect(btstart, SIGNAL(clicked()), this, SLOT(startv()));
        connect(btstart, SIGNAL(clicked()), this, SLOT(stop()));
    }

    void stop()
    {
        sockv->close();
        sockv->deleteLater();

        disconnect(btstart, SIGNAL(clicked()), this, SLOT(stop()));
        connect(btstart, SIGNAL(clicked()), this, SLOT(startv()));

        leip->setDisabled(false);
        leport->setDisabled(false);
        btstart->setText("START");
    }

    void recv_show()
    {
        if(readsize){ //接收图片大小
            char buf[10] = {0};
            sockv->read(buf, 10);
            picsize = atoi(buf); //转成整形大小值
     //       qDebug()<<picsize;

            readsize = false;
        }
        else
        {
            if(sockv->bytesAvailable() < picsize) //等待图片内容接收完整
                return;

            char buf[640*480*3];
            sockv->read(buf, picsize);
            QPixmap pix;
            pix.loadFromData((uchar*)buf, picsize, "jpeg");
            lbvideo->setPixmap(pix);//切换照片

            readsize = true;
        }

    }

private:
    QLabel *lbvideo, *lbip, *lbport;
    QLineEdit *leip, *leport;
    QPushButton *btstart;

    QTcpSocket *sockv;

    bool readsize;
    int picsize;

};

#endif // WIDGET_H
