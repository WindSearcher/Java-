#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include "Board.h"
#include "CtrlPanel.h"
#include "SingleGame.h"
#include "MultiGame.h"
#include"ChooseDlg.h"
class MainWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MainWnd(int gameType, QWidget *parent = 0);
    ~MainWnd();

    int gameType;
    SingleGame* game1;
    MultiGame* game2;
    ChooseDlg* dlg;
signals:

public slots:
    void slotChose();
};

#endif // MAINWND_H
