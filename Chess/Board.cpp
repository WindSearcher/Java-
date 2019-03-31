#include "Board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#define GetRowCol(__row, __col, __id) \
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col
QPoint START;

Board::Board(QWidget *parent) : QFrame(parent)
{
    this->_r = 20;
    setMinimumSize(_r*18+1, _r*20+1);
    init(true);
}

Board::~Board()
{

}

void Board::init(bool bRedSide)
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);
    }
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _s[i].rotate();
        }
    }

    _selectid = -1;
    _bRedTurn = true;
    _bSide = bRedSide;
    update();
}

void Board::paintEvent(QPaintEvent *)
{
    _r = 20;//半径
    START = QPoint(_r+1, _r+1);//棋盘开始绘制的起始位置

    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    drawPlate(p);
    drawPlace(p);
    //画棋子
    for(int i=0; i<32; i++)
    {
        drawStone(p, i);
    }
}


//画棋子
void Board::drawStone(QPainter &p, int id)
{
    if(isDead(id)) return;

    QColor color;
    if(red(id)) color = Qt::red;
    else color = Qt::black;

    p.setPen(QPen(QBrush(color), 2));

    if(id == _selectid) p.setBrush(Qt::gray);
    else p.setBrush(Qt::yellow);

    p.drawEllipse(cell(id));
    //填充文字
    p.setFont(QFont("system", _r*1.2, 700));
    p.drawText(cell(id), _s[id].name(), QTextOption(Qt::AlignCenter));
}


//判断棋子是否已经被吃
bool Board::isDead(int id)
{
    if(id == -1)return true;
    return _s[id]._dead;
}


//判断棋子的阵营
bool Board::red(int id)
{
    return _s[id]._red;
}


//画宫殿
void Board::drawPlace(QPainter &p)
{
    p.drawLine(center(0, 3), center(2, 5));
    p.drawLine(center(2, 3), center(0, 5));

    p.drawLine(center(9, 3), center(7, 5));
    p.drawLine(center(7, 3), center(9, 5));
}


//画棋盘
void Board::drawPlate(QPainter &p)
{
    for(int i=0; i<10; ++i) //画竖线
    {
        if(i==0 || i==9)
        {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        }
        p.drawLine(center(i, 0), center(i, 8));
    }

    for(int i=0; i<9; ++i) //画横线
    {
        if(i==0 || i==8)
        {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
            p.drawLine(center(0, i), center(9, i));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
            p.drawLine(center(0, i), center(4, i));
            p.drawLine(center(5, i), center(9, i));
        }
    }
}


//返回绘制坐标
QPoint Board::center(int row, int col)
{
    QPoint pt(_r*col*2, _r*row*2);
    return pt + START;
}



QPoint Board::center(int id)
{
    return center(_s[id]._row, _s[id]._col);
}



QPoint Board::topLeft(int row, int col)
{
    return center(row, col) - QPoint(_r, _r);
}

QPoint Board::topLeft(int id)
{
    return center(id) - QPoint(_r, _r);
}


QRect Board::cell(int row, int col)
{
    return QRect(topLeft(row, col), QSize(_r*2-1, _r*2-1));
}

QRect Board::cell(int id)
{
    return QRect(topLeft(id), QSize(_r*2-1, _r*2-1));
}


//获取点击点的行列
bool Board::getClickRowCol(QPoint pt, int &row, int &col)
{
    for(row=0; row<=9; ++row)
    {
        for(col=0; col<=8; ++col)
        {
            QPoint distance = center(row, col) - pt;
            if(distance.x() * distance.x() + distance.y() * distance.y() < _r* _r)
                return true;
        }
    }
    return false;
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
    {
        return;
    }

    click(ev->pos());
}


void Board::click(int id, int row, int col)
{
    if(this->_selectid == -1)
    {
        trySelectStone(id);
    }
    else
    {
        tryMoveStone(id, row, col);
    }
}

//得到所点击处的信息
void Board::click(QPoint pt)
{
    int row, col;
    getClickRowCol(pt, row, col);

    int id = getChessId(row, col);
    click(id, row, col);
}

int Board::getChessId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(_s[i]._row == row && _s[i]._col == col && !isDead(i))
            return i;
    }
    return -1;
}

//判断点击顺序与轮到顺序是否相同
bool Board::Select(int id)
{
    return _bRedTurn == _s[id]._red;
}

void Board::trySelectStone(int id)
{
    if(id == -1)
        return;


     //是否符合当前方棋子
    if(_bRedTurn != _s[id]._red) return;

    _selectid = id;
    update();
}

//判断两个棋子是否相同颜色
bool Board::sameColor(int id1, int id2)
{
    if(id1 == -1 || id2 == -1) return false;

    return red(id1) == red(id2);
}

//尝试移动棋子
void Board::tryMoveStone(int killid, int row, int col)
{
    //选择了同一方棋子,换选中的棋子
    if(killid != -1 && sameColor(killid, _selectid))
    {
        trySelectStone(killid);
        return;
    }

    //判断能否移动
    bool ret = Move(_selectid, killid, row, col);
    if(ret)
    {
        moveStone(_selectid, killid, row, col);
        _selectid = -1;
        update();
    }
}


int Board::getStoneCount(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2)
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;

    if(row1 == row2)
    {
        int min = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getChessId(row1, col) != -1) ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getChessId(row, col1) != -1) ++ret;
        }
    }

    return ret;
}


bool Board::MoveChe(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    //如果移动的位置上有棋子则不能移动
    int ret = getStoneCount(row1, col1, row, col);
    if(ret == 0)
        return true;
    return false;
}

//判断马是否可以走动
int Board::relation(int row1, int col1, int row, int col)
{
    return qAbs(row1-row)*10+qAbs(col1-col);
}

bool Board::MoveMa(int moveid, int, int row, int col)
{
    //获取移动起始位置的坐标
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 12 && r != 21)
        return false;

    if(r == 12)
    {
        //判断横着走能否走
        if(getChessId(row1, (col+col1)/2) != -1)
            return false;
    }
    else
    {
        if(getChessId((row+row1)/2, col1) != -1)
            return false;
    }

    return true;
}

bool Board::MovePao(int moveid, int killid, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCount(row, col, row1, col1);
    if(killid != -1)
    {
        if(ret == 1) return true;
    }
    else
    {
        if(ret == 0) return true;
    }
    return false;
}


bool Board::isBottomSide(int id)
{
    return _bSide == _s[id]._red;
}

bool Board::MoveBing(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(isBottomSide(moveid))
    {
        if(row > row1) return false;
        if(row1 >= 5 && row == row1) return false;
    }
    else
    {
        if(row < row1) return false;
        if(row1 <= 4 && row == row1) return false;
    }

    return true;
}

bool Board::MoveJiang(int moveid, int killid, int row, int col)
{
    if(killid != -1 && _s[killid]._type == Stone::JIANG)
        return MoveChe(moveid, killid, row, col);

    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(col < 3 || col > 5) return false;
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    return true;
}

bool Board::MoveShi(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 11) return false;

    if(col < 3 || col > 5) return false;
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    return true;
}

bool Board::MoveXiang(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 22) return false;

    int rEye = (row+row1)/2;
    int cEye = (col+col1)/2;
    if(getChessId(rEye, cEye) != -1)
        return false;

    if(isBottomSide(moveid))
    {
        if(row < 4) return false;
    }
    else
    {
        if(row > 5) return false;
    }
    return true;
}

bool Board::Move(int moveid, int killid, int row, int col)
{
    if(sameColor(moveid, killid)) return false;

    switch (_s[moveid]._type)
    {
    case Stone::CHE:
        return MoveChe(moveid, killid, row, col);

    case Stone::MA:
        return MoveMa(moveid, killid, row, col);

    case Stone::PAO:
        return MovePao(moveid, killid, row, col);

    case Stone::BING:
        return MoveBing(moveid, killid, row, col);

    case Stone::JIANG:
        return MoveJiang(moveid, killid, row, col);

    case Stone::SHI:
        return MoveShi(moveid, killid, row, col);

    case Stone::XIANG:
        return MoveXiang(moveid, killid, row, col);

    }
    return false;
}

//恢复棋子
void Board::reliveStone(int id)
{
    if(id==-1) return;
    _s[id]._dead = false;
}


//杀死棋子
void Board::killStone(int id)
{
    if(id==-1) return;
    _s[id]._dead = true;
}


//移动 棋子
void Board::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;

    _bRedTurn = !_bRedTurn;
}

//在移动的过程中杀死棋子
void Board::moveStone(int moveid, int killid, int row, int col)
{
    saveStep(moveid, killid, row, col, _steps);

    killStone(killid);
    moveStone(moveid, row, col);
}


//保存途径,以便悔棋
void Board::saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps)
{
    GetRowCol(row1, col1, moveid);
    Step* step = new Step;
    step->_colFrom = col1;
    step->_colTo = col;
    step->_rowFrom = row1;
    step->_rowTo = row;
    step->_moveid = moveid;
    step->_killid = killid;

    steps.append(step);
}

void Board::back(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void Board::backOne()
{
    if(this->_steps.size() == 0) return;

    Step* step = this->_steps.last();
    _steps.removeLast();
    back(step);

    update();
    delete step;
}

void Board::back()
{
    backOne();
}

void Board::slotBack()
{
    backOne();
}
