#ifndef BOARD_H
#define BOARD_H

#include <QFrame>
#include "Stone.h"
#include "Step.h"
#include <QVector>

class Board : public QFrame
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();

    Stone _s[32];
    int _r;//棋子的半径
    bool _bSide;
    QVector<Step*> _steps;//保存步骤
    int _selectid;//被选中的棋子id
    bool _bRedTurn;//是否轮到红棋
    void init(bool bRedSide);//初始化

    void paintEvent(QPaintEvent *);
    void drawPlate(QPainter& p);//绘制棋盘
    void drawPlace(QPainter& p);//绘制宫殿
    void drawStone(QPainter& p, int id);//绘制棋子

    QPoint center(int row, int col);//得到坐标
    QPoint center(int id);
    bool red(int id);
    bool sameColor(int id1, int id2);//判断是否是相同颜色
    int getChessId(int row, int col);//得到棋子id
    void killStone(int id);//吃掉棋子
    void reliveStone(int id);//恢复
    void moveStone(int moveid, int row, int col);//移动棋子
    bool isDead(int id);//判断是否被吃

    void mouseReleaseEvent(QMouseEvent *);
    void click(QPoint pt);
    virtual void click(int id, int row, int col);
    void trySelectStone(int id);//尝试选择棋子
    void tryMoveStone(int killid, int row, int col);//尝试移动棋子
    void moveStone(int moveid, int killid, int row, int col);
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);
    void backOne();
    void back(Step* step);//悔棋
    virtual void back();

    bool Move(int moveid, int killid, int row, int col);//判断能否移动
    bool MoveChe(int moveid, int killid, int row, int col);
    bool MoveMa(int moveid, int killid, int row, int col);
    bool MovePao(int moveid, int killid, int row, int col);
    bool MoveBing(int moveid, int killid, int row, int col);
    bool MoveJiang(int moveid, int killid, int row, int col);
    bool MoveShi(int moveid, int killid, int row, int col);
    bool MoveXiang(int moveid, int killid, int row, int col);

    bool Select(int id);

    int getStoneCount(int row1, int col1, int row2, int col2);
    int relation(int row1, int col1, int row, int col);
    bool isBottomSide(int id);
    QPoint topLeft(int row, int col);
    QPoint topLeft(int id);
    QRect cell(int row, int col);
    QRect cell(int id);
    bool getClickRowCol(QPoint pt, int& row, int& col);

signals:

public slots:
    void slotBack();

};

#endif // BOARD_H
