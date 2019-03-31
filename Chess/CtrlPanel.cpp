#include "CtrlPanel.h"
#include <QGridLayout>
#include <QVBoxLayout>
CtrlPanel::CtrlPanel(QWidget *parent) : QWidget(parent)
{
    QGridLayout* grid = new QGridLayout(this);
    QVBoxLayout* vLay = new QVBoxLayout;
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(2, 1);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(2, 1);
    grid->addLayout(vLay, 1, 1);

    vLay->addWidget(this->_back = new QPushButton("悔棋"));
    this->_back->setStyleSheet("color:green;font-size:20;"
                               "background-color:black;font-weight:bold");
    vLay->addWidget(this->_chose= new QPushButton("重新选择"));
    this->_chose->setStyleSheet("color:green;font-size:20;"
                                "background-color:black;font-weight:bold");
    connect(this->_back, SIGNAL(clicked()), this, SIGNAL(sigBack()));
    connect(this->_chose, SIGNAL(clicked()), this, SIGNAL(sigChose()));
}

CtrlPanel::~CtrlPanel()
{

}

