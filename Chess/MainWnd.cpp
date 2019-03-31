#include "MainWnd.h"
#include <QHBoxLayout>
#include<QDebug>
MainWnd *wnd;
MainWnd::MainWnd(int gameType, QWidget *parent) : QWidget(parent)
{
    if(gameType == 0)
    {
        game1 = new SingleGame(this);
        game1->show();
        qDebug()<<"hello";
        setWindowTitle("人机对战");
        CtrlPanel* panel = new CtrlPanel;
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game1, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game1, SLOT(slotBack()));
        connect(panel, SIGNAL(sigChose()), this, SLOT(slotChose()));
    }
    else if(gameType == 1)
    {
        game2 = new MultiGame(this);
        game2->show();
        qDebug()<<"hello";
        setWindowTitle("人人对战");
        CtrlPanel* panel = new CtrlPanel;
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game2, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game2, SLOT(slotBack()));
        connect(panel, SIGNAL(sigChose()), this, SLOT(slotChose()));
    }

}


void MainWnd::slotChose()
{
    dlg = new ChooseDlg();
    dlg->show();
    hide();
    if(dlg->exec() != QDialog::Accepted)
         return ;
    wnd = new MainWnd(dlg->selected);
    wnd->show();

}

MainWnd::~MainWnd()
{

}

