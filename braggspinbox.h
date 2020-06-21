#ifndef BRAGGSPINBOX_H
#define BRAGGSPINBOX_H

#include <QDoubleSpinBox>

class braggSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    braggSpinBox(QWidget *parent = nullptr);
    ~braggSpinBox() = default;

    void setDecimals(int decimals);

private slots:
    void customContextMenu(QPoint /*pos*/); //pos is widget pos, not used. Use QCursor instead
    void copy();
    void cut();
    void paste();
    void singleStepDown();
    void singleStepUp();

 };

#endif // BRAGGSPINBOX_H
