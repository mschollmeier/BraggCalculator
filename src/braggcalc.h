/***** GPL *******************************************************************
**                                                                          **
** This file is part of BraggCalculator, a GUI-based program to quickly     **
** evaluate the Bragg equation for x-ray reflection.                        **
**                                                                          **
** Copyright (c) 2020  Marius S. Schollmeier                                **
**                                                                          **
** This program is free software: you can redistribute it and/or modify     **
** it under the terms of the GNU General Public License as published by     **
** the Free Software Foundation, either version 3 of the License, or        **
** (at your option) any later version.                                      **
**                                                                          **
** This program is distributed in the hope that it will be useful,          **
** but WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            **
** GNU General Public License for more details.                             **
**                                                                          **
** You should have received a copy of the GNU General Public License        **
** along with this program.  If not, see <https://www.gnu.org/licenses/     **
**                                                                          **
******************************************************************************
** Author:  Marius Schollmeier,                                             **
** Contact: mschollmeier01@gmail.com                                        **
** Date:    Dec. 02, 2020                                                   **
** Version: 1.0                                                             **
*****************************************************************************/

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
