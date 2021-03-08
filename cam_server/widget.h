#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QTimerEvent>
#include <QDebug>
#include <QPixmap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTemporaryFile>
#include <QFile>
#include <QBuffer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void show_pic(int i, QImage img)
    {

        QPixmap pix(1920, 1080);
#if 1
        pix.fill(Qt::red);
        pix = pix.fromImage(img);
        lb_pic->setPixmap(pix);
#else
        lb_pic->setPixmap(QPixmap::fromImage(img));

#endif
//        qDebug()<<i;


        if(client&&client->isWritable())
        {
//            qDebug()<<"sending "<<pix.size();
#if 0
            pix.save("tem.jpg","jpeg");
//             qDebug()<<"saveed";
            QFile tem("tem.jpg");
            tem.open(QIODevice::ReadOnly);

#else
            QBuffer tem;
            pix.save(&tem, "jpeg");
#endif
            char buf[10] = {0};
 //           qDebug()<<"size: "<<buf;
            sprintf(buf, "%d", tem.size());
  //          qDebug()<<"size: "<<buf;
            client->write(buf, 10);//发大小（大小值先转换成字符串装在固定的10个字节的buff中发送）
  //          qDebug()<<"size ok";
#if 0
            QByteArray data = tem.readAll();           
#else
            QByteArray data(tem.buffer());
#endif
            client->write(data);//发图片内容
   //          qDebug()<<"finish";
             tem.close();
        }
    }

    void accept_client()
    {
        if(NULL != client)
        {
            client->close();
            client->deleteLater();
        }
        client = myserver->nextPendingConnection();
        connect(client, SIGNAL(disconnected()), this, SLOT(client_close()));
    }

    void client_close()
    {
        client->close();
        client->deleteLater();
        client = NULL;
    }
protected:
    virtual void
    timerEvent(QTimerEvent *event)
    {
        imageCapture->capture();
//        qDebug()<<"tttt";
    }

 private:
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    QLabel *lb_pic;

    QTcpServer *myserver;
    QTcpSocket *client;
};

#endif // WIDGET_H
