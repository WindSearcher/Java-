#ifndef STEP_H
#define STEP_H

#include <QObject>

class Step : public QObject
{
    Q_OBJECT
public:
    explicit Step(QObject *parent = 0);
    ~Step();

    int _moveid;//移动棋子的id
    int _killid;//即将被杀死棋子的id
    int _rowFrom;//起始位置
    int _colFrom;
    int _rowTo;//要到达的位置
    int _colTo;

signals:

public slots:
};

#endif // STEP_H
