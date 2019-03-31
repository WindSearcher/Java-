#ifndef ChooseDlg_H
#define ChooseDlg_H

#include <QDialog>
#include <QPushButton>

class ChooseDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseDlg(QWidget *parent = 0);
    ~ChooseDlg();

    QPushButton* buttons[2];
    int selected;

signals:

public slots:
    void slotClicked();
};

#endif // ChooseDlg_H
