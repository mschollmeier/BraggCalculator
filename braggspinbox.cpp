#include "braggspinbox.h"

#include <QClipboard>
#include <QGuiApplication>
#include <QLineEdit>
#include <QMenu>
#include <QMimeData>

#include <cmath>

braggSpinBox::braggSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->customContextMenuRequested(QCursor::pos());
    connect(this, &QDoubleSpinBox::customContextMenuRequested, this, &braggSpinBox::customContextMenu);
}


// -----------------------------------------------------------------------------------
// public functions
// -----------------------------------------------------------------------------------
void braggSpinBox::setDecimals(int decimals)
{
    QDoubleSpinBox::setDecimals(decimals);
    if (this->singleStep() < pow(10, -decimals))
        this->setSingleStep(pow(10, -decimals));

}

// -----------------------------------------------------------------------------------
// private
// -----------------------------------------------------------------------------------
void braggSpinBox::customContextMenu(QPoint /*pos*/)
{
    auto mousePos = QCursor::pos();
    QMenu *menu = new QMenu(this);

    menu->setAttribute(Qt::WA_QuitOnClose, true);
    menu->addAction(tr("Cut"), this, [this]{cut();});
    menu->addAction(tr("Copy"), this, [this]{copy();});
    menu->addAction(tr("Paste"), this, [this]{paste();});
    menu->addSeparator();
    menu->addAction(tr("Select all"), this, [this]{selectAll();});
    menu->addSeparator();

    auto stepSizeMenu = new QMenu(this);
    auto stepSizeGroup = new QActionGroup(this);

    stepSizeMenu->setTitle("Set step size");
    // add actions for digits, 1 thru 15
    for (int i = 0; i <= decimals(); i++) {
        double step = pow(10, -i);
        auto decAction = new QAction(this);
        decAction->setText(QString::number(step));
        decAction->setCheckable(true);
        connect(decAction, &QAction::triggered, [this, step]{setSingleStep(step);});

        if (abs(step - singleStep()) <= 1e-15)
            decAction->setChecked(true);

        stepSizeGroup->addAction(decAction);
        stepSizeMenu->addAction(decAction);
    }

    // add "set step size" to menu
    menu->addMenu(stepSizeMenu);

    menu->addSeparator();
    menu->addAction(tr("Step up"), this, [this]{singleStepUp();});
    menu->addAction(tr("Step down"), this, [this]{singleStepDown();});
    menu->move(mousePos);
    menu->show();
}


void braggSpinBox::copy()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    auto txt = QString::number(this->value()).toUtf8();
    clipboard->setText(txt);
}


void braggSpinBox::cut()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    auto txt = QString::number(this->value()).toUtf8();
    clipboard->setText(txt);
    this->setValue(0.0);
}


void braggSpinBox::paste()
{
    const QClipboard *clipboard = QGuiApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();

    if (mimeData->hasText())
        this->setValue(mimeData->text().toDouble());

}


void braggSpinBox::singleStepDown()
{
    auto val = this->value() - this->singleStep();
    this->setValue(val);
}


void braggSpinBox::singleStepUp()
{
    auto val = this->value() + this->singleStep();
    this->setValue(val);
}

