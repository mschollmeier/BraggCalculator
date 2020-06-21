#ifndef BRAGGCALC_H
#define BRAGGCALC_H

#include <QMenu>
#include <QOperatingSystemVersion>
#include <QPrinter>
#include <QUndoStack>
#include <QUndoView>
#include <QWidget>

#include "braggparams.h"

QT_BEGIN_NAMESPACE
namespace Ui { class braggCalc; }
QT_END_NAMESPACE

class braggCalc : public QWidget
{
    Q_OBJECT

public:
    braggCalc(QWidget *parent = nullptr);
    ~braggCalc();

    void reset();

private:
    Ui::braggCalc *ui;

    braggParams _p;

    QOperatingSystemVersion::OSType _currentOS = QOperatingSystemVersion::currentType();

    QPrinter _printer;

    QUndoStack *_undoStack = nullptr;
#ifdef QT_DEBUG
    QUndoView *_undoView = nullptr;
    void createUndoView();
#endif

    QAction *_undoAction = nullptr;
    QAction *_redoAction = nullptr;

    // private functions
    void reCalcBragg();   //re-calculates Bragg angle when energy or crystal params change
    void reCalcCrystal(); //re-calculates crystal params when Bragg angle changes
    void reCalcEnergy();  //re-calculates energy/wavelemgth when Bragg angle changes

    // menus and actions
    void createMenu();
    void setupConnections();
    void resetInputWidgets();


private slots:
    void energyChanged(double energy);
    void energyUnitChanged(int index);
    void lambdaChanged(double lambda);
    void lambdaUnitChanged(int index);

    void twoDChanged(double twoD);
    void twoDUnitChanged(int index);

    void reflOrderChanged(int reflOrder);
    void braggChanged(double bragg);
    void braggUnitChanged(int index);
    void normalChanged(double normal);
    void normalUnitChanged(int index);
    void crystalCheckBoxChanged(int state);
    void xrayCheckBoxChanged(int state);

    // menu and action slots
    void about();
    void allNew();
    void closeApp();
    void exportFile();
    void open();
    void save();
    void setDecimals(int decimals);
    void pageSetup();
    void print();


};
#endif // BRAGGCALC_H
