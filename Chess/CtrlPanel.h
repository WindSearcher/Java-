#ifndef CTRLPANEL_H
#define CTRLPANEL_H

#include <QWidget>
#include <QPushButton>

class CtrlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlPanel(QWidget *parent = 0);
    ~CtrlPanel();

    QPushButton* _back;
    QPushButton* _chose;
signals:
    void sigBack();
    void sigChose();
public slots:
};

#endif // CTRLPANEL_H
