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

#include "braggcalc.h"
#include "ui_braggcalc.h"

#include <QDebug>
#include <QDoubleSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QMetaType>
#include <QPageSize>
#include <QPrintDialog>
#include <QtPrintSupport>
#include <QSpinBox>
#include <QStandardPaths>
#include <QTextDocument>
#include <QTextDocumentWriter>

#include <cmath>

#include "aboutwindow.h"
#include "braggserialize.h"
#include "createbraggtextdoc.h"
#include "undocommands.h"

const double pi_2 = static_cast<double>(Constants::pi_2);
using Constants::rad2deg;
using Constants::deg2rad;

braggCalc::braggCalc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::braggCalc)
{
    ui->setupUi(this);

    _undoStack = new QUndoStack(this);

    _printer.setPageSize(QPageSize(QPageSize::Letter));
    _printer.setPageOrientation(QPageLayout::Portrait);
    _printer.setResolution(QPrinter::HighResolution);
    _printer.setPageMargins(QMarginsF(1, 1, 1, 1), QPageLayout::Inch);

    this->createMenu();

    this->resetInputWidgets();
    this->setupConnections();

    QCoreApplication::setApplicationName( QString("Bragg Angle Calculator") );

    qRegisterMetaType<braggParams>("braggParams");

    this->setWindowTitle( QCoreApplication::applicationName() );
    this->show();

    auto size = this->size();
    this->setFixedSize(size);

}

braggCalc::~braggCalc()
{
    delete ui;
}


void braggCalc::reset()
{
    _p.clear();
    this->_undoStack->clear();
    this->resetInputWidgets();
    this->setDecimals(_p.decimals);
}

// -----------------------------------------------------------------------------------
// private slots
// -----------------------------------------------------------------------------------
void braggCalc::energyChanged(double energy)
{
    auto cmd = new spinBoxUndoCommand<double, QDoubleSpinBox>(energy, _p.energy, ui->energyDoubleSpinBox);
    _undoStack->push(cmd);  //executes cmd by calling its redo() function.
    _p.energy = energy;

    // calculate new wavelength and Bragg angle
    ui->lambdaDoubleSpinBox->blockSignals(true);
    ui->braggDoubleSpinBox->blockSignals(true);
    ui->normalDoubleSpinBox->blockSignals(true);

    if (_p.energy > Constants::epsilonZero) {
        _p.lambda = Constants::keV2Angstrom / (_p.energyMultiplier[_p.energyCurIndex] * _p.energy) / _p.lambdaMultiplier[_p.lambdaCurIndex];
        ui->lambdaDoubleSpinBox->setValue(_p.lambda);

        this->reCalcBragg();
    }
    else
        ui->lambdaDoubleSpinBox->setValue(0.0);

    ui->lambdaDoubleSpinBox->blockSignals(false);
    ui->braggDoubleSpinBox->blockSignals(false);
    ui->normalDoubleSpinBox->blockSignals(false);
}


void braggCalc::energyUnitChanged(int index)
{
    double oldMultiplier = _p.energyMultiplier[_p.energyCurIndex];
    _p.energyCurIndex = index;
    double newMultiplier = _p.energyMultiplier[index];
    double ratio = oldMultiplier / newMultiplier;
    _p.energy *= ratio;

    ui->energyDoubleSpinBox->blockSignals(true);
    ui->energyDoubleSpinBox->setDecimals(_p.decimals);
    ui->energyDoubleSpinBox->setValue(_p.energy);
    ui->energyDoubleSpinBox->blockSignals(false);
}

void braggCalc::lambdaChanged(double lambda)
{

    auto cmd = new spinBoxUndoCommand<double, QDoubleSpinBox>(lambda, _p.lambda, ui->lambdaDoubleSpinBox);
    _undoStack->push(cmd);  //executes cmd by calling its redo() function.
    _p.lambda = lambda;

    // calculate new energy and Bragg angle
    ui->energyDoubleSpinBox->blockSignals(true);
    ui->braggDoubleSpinBox->blockSignals(true);
    ui->normalDoubleSpinBox->blockSignals(true);

    if (_p.lambda > Constants::epsilonZero) {
        _p.energy = Constants::keV2Angstrom / (_p.lambdaMultiplier[_p.lambdaCurIndex] * lambda) / _p.energyMultiplier[_p.energyCurIndex];
        ui->energyDoubleSpinBox->setValue(_p.energy);
        this->reCalcBragg();
    }
    else
        ui->energyDoubleSpinBox->setValue(0.0);

    ui->energyDoubleSpinBox->blockSignals(false);
    ui->braggDoubleSpinBox->blockSignals(false);
    ui->normalDoubleSpinBox->blockSignals(false);

}

void braggCalc::lambdaUnitChanged(int index)
{
    double oldMultiplier = _p.lambdaMultiplier[_p.lambdaCurIndex];
    _p.lambdaCurIndex = index;
    double newMultiplier = _p.lambdaMultiplier[index];
    double ratio = oldMultiplier / newMultiplier;
    _p.lambda *= ratio;

    ui->lambdaDoubleSpinBox->blockSignals(true);
    ui->lambdaDoubleSpinBox->setDecimals(_p.decimals);
    ui->lambdaDoubleSpinBox->setValue(_p.lambda);
    ui->lambdaDoubleSpinBox->blockSignals(false);
}

void braggCalc::twoDChanged(double twoD)
{
    auto cmd = new spinBoxUndoCommand<double, QDoubleSpinBox>(twoD, _p.twoD, ui->twoDDoubleSpinBox);
    _undoStack->push(cmd);  //executes cmd by calling its redo() function.
    _p.twoD = twoD;

    ui->energyDoubleSpinBox->blockSignals(true);
    ui->lambdaDoubleSpinBox->blockSignals(true);
    ui->braggDoubleSpinBox->blockSignals(true);
    ui->normalDoubleSpinBox->blockSignals(true);

    this->reCalcBragg();

    ui->energyDoubleSpinBox->blockSignals(false);
    ui->lambdaDoubleSpinBox->blockSignals(false);
    ui->braggDoubleSpinBox->blockSignals(false);
    ui->normalDoubleSpinBox->blockSignals(false);
}


void braggCalc::twoDUnitChanged(int index)
{
    double oldMultiplier = _p.twoDMultiplier[_p.twoDCurIndex];
    _p.twoDCurIndex = index;
    double newMultiplier = _p.twoDMultiplier[index];
    double ratio = oldMultiplier / newMultiplier;
    _p.twoD *= ratio;

    ui->twoDDoubleSpinBox->blockSignals(true);
    ui->twoDDoubleSpinBox->setDecimals(_p.decimals);
    ui->twoDDoubleSpinBox->setValue(_p.twoD);
    ui->twoDDoubleSpinBox->blockSignals(false);
}


void braggCalc::reflOrderChanged(int reflOrder)
{

    auto cmd = new spinBoxUndoCommand<int, QSpinBox>(reflOrder, _p.reflOrder, ui->reflOrderSpinBox);
    _undoStack->push(cmd);  //executes cmd by calling its redo() function.
    _p.reflOrder = reflOrder;

    ui->energyDoubleSpinBox->blockSignals(true);
    ui->lambdaDoubleSpinBox->blockSignals(true);
    ui->braggDoubleSpinBox->blockSignals(true);
    ui->normalDoubleSpinBox->blockSignals(true);

    this->reCalcBragg();

    ui->energyDoubleSpinBox->blockSignals(false);
    ui->lambdaDoubleSpinBox->blockSignals(false);
    ui->braggDoubleSpinBox->blockSignals(false);
    ui->normalDoubleSpinBox->blockSignals(false);
}


void braggCalc::braggChanged(double bragg)
{
    auto cmd = new spinBoxUndoCommand<double, QDoubleSpinBox>(bragg, _p.bragg, ui->braggDoubleSpinBox);
    _undoStack->push(cmd);  //executes cmd by calling its redo() function.
    _p.bragg = bragg;

    ui->energyDoubleSpinBox->blockSignals(true);
    ui->lambdaDoubleSpinBox->blockSignals(true);
    ui->twoDDoubleSpinBox->blockSignals(true);
    ui->normalDoubleSpinBox->blockSignals(true);

    if (_p.braggInDegree)
        _p.normal = _p.normalInDegree ? 90.0 - _p.bragg : pi_2 - deg2rad * _p.bragg;
    else
        _p.normal = _p.normalInDegree ? 90.0 - rad2deg * _p.bragg : pi_2 - _p.bragg;

    ui->normalDoubleSpinBox->setValue(_p.normal);

    ui->energyDoubleSpinBox->blockSignals(false);
    ui->lambdaDoubleSpinBox->blockSignals(false);
    ui->twoDDoubleSpinBox->blockSignals(false);
    ui->normalDoubleSpinBox->blockSignals(false);

    if (ui->xrayCheckBox->isChecked())
        reCalcCrystal();
    else if (ui->crystalCheckBox->isChecked())
        reCalcEnergy();
}


void braggCalc::normalChanged(double normal)
{
    ui->energyDoubleSpinBox->blockSignals(true);
    ui->lambdaDoubleSpinBox->blockSignals(true);
    ui->twoDDoubleSpinBox->blockSignals(true);
    ui->braggDoubleSpinBox->blockSignals(true);

    auto cmd = new spinBoxUndoCommand<double, QDoubleSpinBox>(normal, _p.normal, ui->normalDoubleSpinBox);
    _undoStack->push(cmd);  //executes cmd by calling its redo() function.
    _p.normal = normal;

    if (_p.normalInDegree)
        _p.bragg = _p.braggInDegree ? 90.0 - _p.normal : pi_2 - deg2rad * _p.normal;
    else
        _p.bragg = _p.braggInDegree ? 90.0 - rad2deg * _p.normal : pi_2 - _p.normal;

    ui->braggDoubleSpinBox->setValue(_p.bragg);

    if (ui->xrayCheckBox->isChecked())
        reCalcCrystal();
    else if (ui->crystalCheckBox->isChecked())
        reCalcEnergy();

    ui->energyDoubleSpinBox->blockSignals(false);
    ui->lambdaDoubleSpinBox->blockSignals(false);
    ui->twoDDoubleSpinBox->blockSignals(false);
    ui->braggDoubleSpinBox->blockSignals(false);

}

void braggCalc::braggUnitChanged(int index)
{
    _p.braggCurIndex = index;
    auto newUnit = _p.braggUnitList[index];

    ui->braggDoubleSpinBox->blockSignals(true);

    if (newUnit.compare("deg") == 0) {
        _p.bragg *= rad2deg;
        ui->braggDoubleSpinBox->setSuffix(UnicodeCharacters::degree);
        ui->braggDoubleSpinBox->setRange(0.0, 90.0);
        ui->braggDoubleSpinBox->setValue(_p.bragg);
        _p.braggInDegree = true;
    }
    else {
        _p.bragg *= deg2rad;
        ui->braggDoubleSpinBox->setSuffix("");
        ui->braggDoubleSpinBox->setRange(0.0, pi_2);
        ui->braggDoubleSpinBox->setValue(_p.bragg);
        _p.braggInDegree = false;
    }

    ui->braggDoubleSpinBox->blockSignals(false);
}


void braggCalc::normalUnitChanged(int index)
{
    _p.normalCurIndex = index;
    auto newUnit = _p.normalUnitList[index];

    ui->normalDoubleSpinBox->blockSignals(true);

    if (newUnit.compare("deg") == 0) {
        _p.normal *= rad2deg;
        ui->normalDoubleSpinBox->setRange(0.0, 90.0);
        ui->normalDoubleSpinBox->setValue(_p.normal);
        ui->normalDoubleSpinBox->setSuffix(UnicodeCharacters::degree);
        _p.normalInDegree = true;
    }
    else {
        _p.normal *= deg2rad;
        ui->normalDoubleSpinBox->setRange(0.0, pi_2);
        ui->normalDoubleSpinBox->setValue(_p.normal);
        ui->normalDoubleSpinBox->setSuffix("");
        _p.normalInDegree = false;
    }

    ui->normalDoubleSpinBox->blockSignals(false);
}


void braggCalc::crystalCheckBoxChanged(int state)
{
    if (state == Qt::Checked) {
        ui->xrayCheckBox->setCheckState(Qt::Unchecked);
        _p.crystalBoxChecked = true;
        _p.xrayBoxChecked = false;
    }
    else {
        ui->xrayCheckBox->setCheckState(Qt::Checked);
        _p.crystalBoxChecked = false;
        _p.xrayBoxChecked = true;
    }
}


void braggCalc::xrayCheckBoxChanged(int state)
{
    if (state == Qt::Checked) {
        ui->crystalCheckBox->setCheckState(Qt::Unchecked);
        _p.xrayBoxChecked = true;
        _p.crystalBoxChecked = false;
    }
    else {
        ui->crystalCheckBox->setCheckState(Qt::Checked);
        _p.xrayBoxChecked = false;
        _p.crystalBoxChecked = true;
    }
}



// -----------------------------------------------------------------------------------
// private functions
// -----------------------------------------------------------------------------------
void braggCalc::reCalcBragg()
{
    ui->braggDoubleSpinBox->blockSignals(true);
    ui->normalDoubleSpinBox->blockSignals(true);

    double theta {-1.0};

    if (_p.twoD > Constants::epsilonZero)
        theta = rad2deg * asin(_p.reflOrder * (_p.lambda * _p.lambdaMultiplier[_p.lambdaCurIndex]) / (_p.twoD * _p.twoDMultiplier[_p.twoDCurIndex])); //in degrees

    if (0.0 <= theta && theta <= 90.0 && _p.lambda > 0.0)  {
        _p.bragg = _p.braggInDegree ? theta : deg2rad * theta;
        _p.normal = (_p.normalInDegree ? 1.0 : deg2rad) * (90.0 - theta);
        ui->braggDoubleSpinBox->setValue(_p.bragg);
        ui->normalDoubleSpinBox->setValue(_p.normal);
    } else {
        ui->braggDoubleSpinBox->setValue(0.0);
        ui->normalDoubleSpinBox->setValue(0.0);
    }

    ui->braggDoubleSpinBox->blockSignals(false);
    ui->normalDoubleSpinBox->blockSignals(false);

}

void braggCalc::reCalcCrystal()
{

    auto sinCalc = _p.braggInDegree ? sin(deg2rad * _p.bragg) : sin(_p.bragg);
    _p.twoD = _p.reflOrder * (_p.lambda * _p.lambdaMultiplier[_p.lambdaCurIndex]) / sinCalc / _p.twoDMultiplier[_p.twoDCurIndex];

    ui->twoDDoubleSpinBox->blockSignals(true);
    ui->twoDDoubleSpinBox->setValue(_p.twoD);
    ui->twoDDoubleSpinBox->blockSignals(false);
}


void braggCalc::reCalcEnergy()
{
    auto sinCalc = _p.braggInDegree ? sin(deg2rad * _p.bragg) : sin(_p.bragg);
    _p.lambda = _p.twoDMultiplier[_p.twoDCurIndex] * _p.twoD * sinCalc / _p.reflOrder / _p.lambdaMultiplier[_p.lambdaCurIndex];

    _p.energy = Constants::keV2Angstrom / _p.lambda / _p.lambdaMultiplier[_p.lambdaCurIndex] /_p.energyMultiplier[_p.energyCurIndex];

    ui->lambdaDoubleSpinBox->blockSignals(true);
    ui->energyDoubleSpinBox->blockSignals(true);

    ui->energyDoubleSpinBox->setValue(_p.energy);
    ui->lambdaDoubleSpinBox->setValue(_p.lambda);

    ui->lambdaDoubleSpinBox->blockSignals(false);
    ui->energyDoubleSpinBox->blockSignals(false);
}

// -----------------------------------------------------------------------------------
// Menus and Actions
// -----------------------------------------------------------------------------------
void braggCalc::createMenu()
{
    // create menu bar and add top level menus
    auto menuBar = new QMenuBar(this);
    this->layout()->setMenuBar(menuBar);
    auto fileMenu = menuBar->addMenu(tr("&File"));
    auto editMenu = menuBar->addMenu(tr("&Edit"));
    auto viewMenu = menuBar->addMenu(tr("&View"));
    auto helpMenu = menuBar->addMenu(tr("&Help"));

    auto newAction = new QAction(tr("&New..."), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("New calculation"));
    connect(newAction, &QAction::triggered, this, &braggCalc::allNew);

    auto openAction = new QAction(tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open parameters from file"));
    connect(openAction, &QAction::triggered, this, &braggCalc::open);

    auto closeAction = new QAction(tr("&Close"), this);
    if (_currentOS == QOperatingSystemVersion::MacOS) {
        closeAction->setShortcut(QKeySequence::Close);
        closeAction->setStatusTip(tr("Close the window"));
        connect(closeAction, &QAction::triggered, this, &braggCalc::close);
    }

    auto saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save parameters to file"));
    connect(saveAction, &QAction::triggered, this, &braggCalc::save);

    auto exportAction = new QAction(tr("Export..."), this);
    exportAction->setStatusTip(tr("Export data to another file format"));
    connect(exportAction, &QAction::triggered, this, &braggCalc::exportFile);

    auto setupPageAction = new QAction(tr("Page Setup..."), this);
    connect(setupPageAction, &QAction::triggered, this, &braggCalc::pageSetup);

    auto printAction = new QAction(tr("&Print..."), this);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(tr("Print the document"));
    connect(printAction, &QAction::triggered, this, &braggCalc::print);

    auto exitAction = new QAction(tr("E&xit"), this);
    if (_currentOS == QOperatingSystemVersion::MacOS) {
        exitAction->setShortcuts(QKeySequence::Quit);
    }
    else {
        exitAction->setShortcut(QKeySequence("Alt+F4"));
    }
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, &braggCalc::closeApp);

    // add to FILE menu
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    if (_currentOS == QOperatingSystemVersion::MacOS) {
        fileMenu->addAction(closeAction);
    }
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(setupPageAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // EDIT menu
    _undoAction = _undoStack->createUndoAction(this, tr("&Undo"));
    _undoAction->setShortcuts(QKeySequence::Undo);

    _redoAction = _undoStack->createRedoAction(this, tr("&Redo"));
    _redoAction->setShortcuts(QKeySequence::Redo);

    editMenu->addAction(_undoAction);
    editMenu->addAction(_redoAction);


    // VIEW
    // add Decimal Places (similar to Calculator on MacOS)
    auto decPlacesMenu = new QMenu(this);
    auto decimalsGroup = new QActionGroup(this);

    decPlacesMenu->setTitle("Decimal Places");
    // add actions for digits, 1 thru 15
    for (int i = 0; i < 16; i++) {
        auto decAction = new QAction(this);
        decAction->setText(QString("%1").arg(i));
        decAction->setCheckable(true);
        connect(decAction, &QAction::triggered, [this, i]{setDecimals(i);});
        if (i == _p.decimals)
            decAction->setChecked(true);

        decimalsGroup->addAction(decAction);
        decPlacesMenu->addAction(decAction);
    }

    // add "Decimal Places" to View menu
    viewMenu->addSeparator();
    viewMenu->addMenu(decPlacesMenu);
    viewMenu->addSeparator();

#ifdef QT_DEBUG
    auto debugMenu = menuBar->addMenu("Debug");
    auto undoViewAction = new QAction("Open Undostack Viewer", this);
    connect(undoViewAction, &QAction::triggered, this, &braggCalc::createUndoView);
    debugMenu->addAction(undoViewAction);
#endif


    auto aboutAction = new QAction(tr("About..."), this);
    connect(aboutAction, &QAction::triggered, this, &braggCalc::about);

    helpMenu->addAction(aboutAction);


}


void braggCalc::setupConnections()

{    // connections for X-Ray Group Box
    connect(ui->energyDoubleSpinBox,  QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [=](double d){energyChanged(d);});
    connect(ui->energyUnitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){energyUnitChanged(index);});

    connect(ui->lambdaDoubleSpinBox,  QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [=](double d){lambdaChanged(d);});
    connect(ui->lambdaUnitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){lambdaUnitChanged(index);});

    // connections for Crystal Group Box
    connect(ui->twoDDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [=](double d){twoDChanged(d);});
    connect(ui->twoDUnitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){twoDUnitChanged(index);});

    connect(ui->reflOrderSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [=](int i){reflOrderChanged(i);});


    // connections for Angle Group Box
    connect(ui->braggDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [=](double d){braggChanged(d);});
    connect(ui->braggUnitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){braggUnitChanged(index);});

    connect(ui->normalDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [=](double d){normalChanged(d);});
    connect(ui->normalUnitComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){normalUnitChanged(index);});

    connect(ui->crystalCheckBox, &QCheckBox::stateChanged, this, &braggCalc::crystalCheckBoxChanged);
    connect(ui->xrayCheckBox, &QCheckBox::stateChanged, this, &braggCalc::xrayCheckBoxChanged);

    //    connect(ui->closePushButton, &QPushButton::clicked, this, qApp->exit);

}


void braggCalc::resetInputWidgets()
{
    // set SpinBox parameters
    ui->energyDoubleSpinBox->setRange(0.0, std::numeric_limits<double>::max());
    ui->energyDoubleSpinBox->setValue(0.0);

    ui->lambdaDoubleSpinBox->setRange(0.0, std::numeric_limits<double>::max());
    ui->lambdaDoubleSpinBox->setValue(0.0);

    ui->twoDDoubleSpinBox->setRange(0.0, std::numeric_limits<double>::max());
    ui->twoDDoubleSpinBox->setValue(0.0);

    ui->reflOrderSpinBox->setValue(1);

    ui->braggDoubleSpinBox->setRange(0.0, 90.0);
    ui->braggDoubleSpinBox->setValue(0.0);
    ui->braggDoubleSpinBox->setSpecialValueText("invalid");
    ui->braggDoubleSpinBox->setSuffix(UnicodeCharacters::degree);

    ui->normalDoubleSpinBox->setRange(0.0, 90.0);
    ui->normalDoubleSpinBox->setValue(0.0);
    ui->normalDoubleSpinBox->setSpecialValueText("invalid");
    ui->normalDoubleSpinBox->setSuffix(UnicodeCharacters::degree);

    ui->crystalCheckBox->setCheckState(Qt::Checked);

    // populate energy unit comboBox
    ui->energyUnitComboBox->addItems(_p.energyUnitList);
    for (auto pref : _p.energyUnitList) {
        if (pref.compare("keV") == 0)
            break;
        _p.energyCurIndex++;
    }
    ui->energyUnitComboBox->setCurrentIndex(_p.energyCurIndex);

    // populate wavelength unit comboBox
    ui->lambdaUnitComboBox->addItems(_p.lambdaUnitList);
    for (auto pref : _p.lambdaUnitList) {
        if (pref.compare(UnicodeCharacters::angstrom) == 0)
            break;
        _p.lambdaCurIndex++;
    }
    ui->lambdaUnitComboBox->setCurrentIndex(_p.lambdaCurIndex);

    // populate twoD unit comboBox
    ui->twoDUnitComboBox->addItems(_p.twoDUnitList);
    for (auto pref : _p.twoDUnitList) {
        if (pref.compare(UnicodeCharacters::angstrom) == 0)
            break;
        _p.twoDCurIndex++;
    }
    ui->twoDUnitComboBox->setCurrentIndex(_p.twoDCurIndex);

    // populate angle unit comboBoxes.
    // Take advantage from fact that both lists are identical
    ui->braggUnitComboBox->addItems(_p.braggUnitList);
    ui->normalUnitComboBox->addItems(_p.normalUnitList);
    for (auto pref : _p.braggUnitList) {
        if (pref.compare("deg") == 0)
            break;
        _p.braggCurIndex++;
        _p.normalCurIndex++;
    }
    ui->braggUnitComboBox->setCurrentIndex(_p.braggCurIndex);
    ui->normalUnitComboBox->setCurrentIndex(_p.normalCurIndex);
}

// only in Debug mode
#ifdef QT_DEBUG
void braggCalc::createUndoView()
{
    _undoView = new QUndoView(_undoStack);
    _undoView->setWindowTitle(tr("Debug: Undo Stack Viewer"));
    //move next to mainwindow, then show window
    _undoView->move(this->frameGeometry().topRight());
    _undoView->updateGeometry();
    _undoView->show();
    _undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

#endif



// -----------------------------------------------------------------------------------
// Menus and Action slots
// -----------------------------------------------------------------------------------
void braggCalc::about()
{
    auto about = new aboutWindow();
    about->setAttribute(Qt::WA_DeleteOnClose, true);
    about->show();
    //move to center of mainwindow
    about->move(
                this->frameGeometry().topLeft() +
                this->rect().center() - about->rect().center());
    about->updateGeometry();

}


void braggCalc::allNew()
{
    if (!this->isVisible())
        this->show();
    this->reset();
}


void braggCalc::closeApp()
{
    qApp->exit();
}


void braggCalc::exportFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export As"),
                                                    _p.curFolder.absolutePath(),
                                                    tr("PDF file (*.pdf);; Text file (*.txt)"));

    auto fileType = fileName.split(".", Qt::KeepEmptyParts, Qt::CaseInsensitive).last();

    if (fileType.contains("pdf", Qt::CaseInsensitive))
    {

        _printer.setOutputFileName(fileName);
        _printer.setOutputFormat(QPrinter::PdfFormat);

        QTextDocument doc;
        doc.documentLayout()->setPaintDevice(&_printer);
        doc.setDefaultFont(this->font());
        doc.setPageSize(_printer.pageLayout().fullRectPixels(_printer.resolution()).size());

        bragg::createBraggTextDoc(doc, _p);
//        qDebug() << doc.toPlainText();
        doc.print(&_printer);
    }

    else if (fileType.contains("txt", Qt::CaseInsensitive))
    {
        QTextDocument doc;
        bragg::createBraggTextDoc(doc, _p);

        QTextDocumentWriter writer;
        writer.setFormat("plaintext");
        writer.setFileName(fileName);
        writer.write(&doc);
    }


}


void braggCalc::open()
{
    if (!this->isVisible())
        this->show();

    QString fileName = QFileDialog::getOpenFileName(this, "", _p.curFolder.absolutePath(), "Bragg files (*.bragg), All files (*)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return;
    }

    try {
        auto fileIO = braggSerialize();
        _p = fileIO.loadFromFile(file);

    }
    catch (std::exception& e) {
        QMessageBox::warning(this, tr("Unable to open file"), QString::fromStdString(e.what()));
    }

    // disable all signals
    for (auto &box : ui->xrayGroupBox->findChildren<QDoubleSpinBox*>())
        box->blockSignals(true);
    for (auto &combo : ui->xrayGroupBox->findChildren<QComboBox*>())
        combo->blockSignals(true);

    for (auto &box : ui->crystalGroupBox->findChildren<QDoubleSpinBox*>())
        box->blockSignals(true);
    for (auto &combo : ui->crystalGroupBox->findChildren<QComboBox*>())
        combo->blockSignals(true);

    ui->reflOrderSpinBox->blockSignals(true);

    for (auto &box : ui->braggGroupBox->findChildren<QDoubleSpinBox*>())
        box->blockSignals(true);
    for (auto &combo : ui->braggGroupBox->findChildren<QComboBox*>())
        combo->blockSignals(true);
    for (auto &check : ui->xrayGroupBox->findChildren<QCheckBox*>())
        check->blockSignals(true);

    // set decimals
    this->setDecimals(_p.decimals);

    // set all boxes to new parameters
    ui->energyDoubleSpinBox->setValue(_p.energy);
    ui->energyUnitComboBox->setCurrentIndex(_p.energyCurIndex);

    ui->lambdaDoubleSpinBox->setValue(_p.lambda);
    ui->lambdaUnitComboBox->setCurrentIndex(_p.lambdaCurIndex);

    ui->twoDDoubleSpinBox->setValue(_p.twoD);
    ui->twoDUnitComboBox->setCurrentIndex(_p.twoDCurIndex);

    ui->reflOrderSpinBox->setValue(_p.reflOrder);

    double maxRange = _p.braggInDegree ? 90.0 : pi_2;
    QString suffix = _p.braggInDegree ? UnicodeCharacters::degree : "";
    ui->braggDoubleSpinBox->setRange(0.0, maxRange);
    ui->braggDoubleSpinBox->setValue(_p.bragg);
    ui->braggDoubleSpinBox->setSuffix(suffix);

    ui->braggUnitComboBox->setCurrentIndex(_p.braggCurIndex);

    maxRange = _p.normalInDegree ? 90.0 : pi_2;
    suffix = _p.normalInDegree ? UnicodeCharacters::degree : "";
    ui->normalDoubleSpinBox->setRange(0.0, maxRange);
    ui->normalDoubleSpinBox->setValue(_p.normal);
    ui->normalDoubleSpinBox->setSuffix(suffix);

    ui->normalUnitComboBox->setCurrentIndex(_p.normalCurIndex);

    // either crystalBox is checked or xrayBox
    if (_p.crystalBoxChecked)
        ui->crystalCheckBox->setCheckState(Qt::Checked);
    if (_p.xrayBoxChecked)
        ui->xrayCheckBox->setCheckState(Qt::Checked);

    // unblock signals
    for(auto &box : ui->xrayGroupBox->findChildren<QDoubleSpinBox*>())
        box->blockSignals(false);
    for (auto &combo : ui->xrayGroupBox->findChildren<QComboBox*>())
        combo->blockSignals(false);

    for (auto &box : ui->crystalGroupBox->findChildren<QDoubleSpinBox*>())
        box->blockSignals(false);
    for (auto &combo : ui->crystalGroupBox->findChildren<QComboBox*>())
        combo->blockSignals(false);

    ui->reflOrderSpinBox->blockSignals(false);

    for (auto &box : ui->braggGroupBox->findChildren<QDoubleSpinBox*>())
        box->blockSignals(false);
    for (auto &combo : ui->braggGroupBox->findChildren<QComboBox*>())
        combo->blockSignals(false);
    for (auto &check : ui->xrayGroupBox->findChildren<QCheckBox*>())
        check->blockSignals(false);

}

void braggCalc::save()
{
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("Bragg files (*.bragg)");
    dialog.setDirectory(_p.curFolder);
    dialog.selectFile("Untitled.bragg");

    if (dialog.exec() != QDialog::Accepted)
        return;

    _p.curFolder = dialog.directory(); //update current folder


    QFile file(dialog.selectedFiles().first());
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to save file"),
                                 file.errorString());
        return;
    }

    try {
        auto bS = braggSerialize();
        bS.saveToFile(file, _p);

    }
    catch (std::exception& e) {
        QMessageBox::warning(this, tr("Unable to save file"), QString::fromStdString(e.what()));
    }
}


void braggCalc::pageSetup()
{
    QPageSetupDialog dlg(&_printer, this);
    dlg.exec();

}


void braggCalc::print()
{

    //    qDebug() << "print";

    //    qDebug()<<"List of printers";
    //    QList<QPrinterInfo> printerList=QPrinterInfo::availablePrinters();
    //    foreach (QPrinterInfo printerInfo, printerList) {
    //        qDebug()<<printerInfo.printerName();
    //    }

    _printer.setOutputFormat(QPrinter::NativeFormat);

    QTextDocument doc;

    doc.documentLayout()->setPaintDevice(&_printer);
    doc.setPageSize(_printer.pageLayout().fullRectPixels(_printer.resolution()).size());

    bragg::createBraggTextDoc(doc, _p);

    QPrintDialog printDialog(&_printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        doc.print(&_printer);
    }
}


void braggCalc::setDecimals(int decimals)
{
    _p.decimals = decimals;
    ui->energyDoubleSpinBox->setDecimals(_p.decimals);
    ui->lambdaDoubleSpinBox->setDecimals(_p.decimals);
    ui->twoDDoubleSpinBox->setDecimals(_p.decimals);
    ui->braggDoubleSpinBox->setDecimals(_p.decimals);
    ui->normalDoubleSpinBox->setDecimals(_p.decimals);
}
