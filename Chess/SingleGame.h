#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "Board.h"

class SingleGame : public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    ~SingleGame();

    int _level;

    void back();
    void click(int id, int row, int col);

    Step* getBestMove();//判断最优解
    void getAllPossibleMove(QVector<Step*>& steps);//得到所有可能的移动
    int getMinScore(int level, int curMin);
    int getMaxScore(int level, int curMax);//评估局面分
    int score();

    void fakeMove(Step* step);//假装移动一步
    void unfakeMove(Step* step);

signals:

public slots:
    void computerMove();//电脑移动
};

#endif // SINGLEGAME_H
