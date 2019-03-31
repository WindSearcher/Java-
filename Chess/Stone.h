#ifndef STONE_H
#define STONE_H

#include <QRect>
#include <QPainter>

class Stone
{
public:
    Stone();
    ~Stone();

    enum TYPE{CHE, MA, PAO, BING, JIANG, SHI, XIANG};

    void init(int id);//用以初始化红方棋子
    void rotate();//初始化黑方棋子
    int _row;//行
    int _col;//列
    TYPE _type;//类型
    bool _dead;//生存状态
    bool _red;//是否是红方
    int _id;

    QString name();


};

#endif // STONE_H
