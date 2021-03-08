#include "widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    lbvideo = new QLabel;
    lbvideo->setFixedSize(640,480);
    lbvideo->setScaledContents(true);
    lbip = new QLabel("IP");
    lbport = new QLabel("PORT");

    leip = new QLineEdit("192.168.1.5");
    leport = new QLineEdit("8888");

    btstart = new QPushButton("START");

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(lbip);
    hbox->addWidget(leip);
    hbox->addWidget(lbport);
    hbox->addWidget(leport);
    hbox->addWidget(btstart);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox);
    vbox->addWidget(lbvideo);

    setLayout(vbox);

    connect(btstart, SIGNAL(clicked()), this, SLOT(startv()));
}

Widget::~Widget()
{

}
