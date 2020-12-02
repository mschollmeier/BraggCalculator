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

#ifndef BRAGGPARAMS_H
#define BRAGGPARAMS_H

// struct that stores all required variables for Bragg calculator

#include <QDir>
#include <QStandardPaths>

#include "unicodecharacters.h"
#include "constants.h"

struct braggParams {

    int decimals {3};       // decimals of QComboBox, can be changed by user

    int energyCurIndex {0}; //index of currently selected energy multiplier
    int lambdaCurIndex {0};
    int twoDCurIndex {0};
    int braggCurIndex {0};
    int normalCurIndex {0};

    bool braggInDegree {true};  //tracks whether selected unit is degree (true) or radian (false)
    bool normalInDegree {true};

    bool crystalBoxChecked {true};
    bool xrayBoxChecked {false};

    double energy {0.0};    // main variables used to solve Bragg equation and store results
    double lambda {0.0};
    double twoD {0.0};
    int reflOrder {1};
    double bragg {0.0};
    double normal {0.0};

    QDir curFolder {QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)};

    QStringList energyUnitList {"meV", "eV", "keV", "MeV"};
    QVector<double> energyMultiplier {1.0e-6, 1.0e-3, 1.0, 1.0e3}; //standard unit is keV

    QStringList lambdaUnitList {"nm", UnicodeCharacters::angstrom, "pm", "fm"};
    QVector<double> lambdaMultiplier {10.0, 1.0, 0.01, 1.0e-5}; //standard unit is angstrom (1.0e-10 m)

    QStringList twoDUnitList {"nm", UnicodeCharacters::angstrom, "pm", "fm"};
    QVector<double> twoDMultiplier {10.0, 1.0, 0.01, 1.0e-5}; //standard unit is angstrom (1.0e-10 m)

    QStringList braggUnitList {"deg", "rad"};
    QVector<double> braggMultiplier {1.0, Constants::rad2deg}; //standard unit is degree

    QStringList normalUnitList = braggUnitList;
    QVector<double> normalMultiplier = braggMultiplier;

    // clear() allows resetting all variables to their initial settings.
    void clear()
    {
        decimals = 3;
        energyCurIndex = 0;
        lambdaCurIndex = 0;
        twoDCurIndex = 0;
        braggCurIndex = 0;
        normalCurIndex = 0;

        braggInDegree = true;
        normalInDegree = true;

        crystalBoxChecked = true;
        xrayBoxChecked = true;

        energy = 0.0;
        lambda = 0.0;
        twoD = 0.0;
        reflOrder = 0.0;
        bragg = 0.0;
        normal = 0.0;

        curFolder.setPath(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    }
};


#endif // BRAGGPARAMS_H
