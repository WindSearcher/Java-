#include "ChooseDlg.h"
#include <QVBoxLayout>
#include<QPixmap>
#include<QPainter>

ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{

    setStyleSheet("background-image:url(:/image/image/src4.jpg);border:1px solid black;");

    QPixmap background(":/image/image/src4.jpg");
    setFixedSize(background.size());
    buttons[0] = new QPushButton("人机对战",this);
    buttons[1] = new QPushButton("人人对战",this);
    buttons[0]->setFixedSize(80,25);
    buttons[0]->move(70,165);
    buttons[0]->setStyleSheet("color:pink;font-size:18;font-weight:bold");
    buttons[1]->setFixedSize(125,30);
    buttons[1]->move(180,background.height()-30);
    buttons[1]->setStyleSheet("color:pink;font-size:18;font-weight:bold");
    for(int i=0; i<2; ++i)
    {
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseDlg::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<4; ++i)
    {
        if(buttons[i] == s)
        {
            this->selected = i;
            break;
        }
    }
    accept();
}



ChooseDlg::~ChooseDlg()
{

}

