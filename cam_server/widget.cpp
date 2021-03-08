#include "widget.h"
#include <QHBoxLayout>
#include <QHostAddress>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    camera = new QCamera("/dev/video0"); //"/dev/video0" 摄像头设备文件，视情况而定
    viewfinder = new QCameraViewfinder(this);
    viewfinder->setFixedSize(640,480);
    viewfinder->show();

      lb_pic = new QLabel(this);
      myserver = new QTcpServer(this);
      client = NULL;

    camera->setViewfinder(viewfinder);
      QHBoxLayout *hbox = new QHBoxLayout;
        hbox->addWidget(viewfinder);
      hbox->addWidget(lb_pic);

      this->setLayout(hbox);

      imageCapture = new QCameraImageCapture(camera);

      camera->setCaptureMode(QCamera::CaptureStillImage);

      connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(show_pic(int,QImage)));
      connect(myserver, SIGNAL(newConnection()), this, SLOT(accept_client()));

      this->startTimer(3);
      myserver->listen(QHostAddress::AnyIPv4, 8888);
      camera->start();
}

Widget::~Widget()
{

}
