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

#ifndef BRAGGSERIALIZE_H
#define BRAGGSERIALIZE_H

#include <QDataStream>
#include <QFile>

#include "braggparams.h"

// https://stackoverflow.com/questions/25113596/qt-how-to-save-data-for-my-application
class braggSerialize
{
public:

    braggSerialize() = default;
    ~braggSerialize() = default;

    quint32 magicNumber {0xA0B0C0D0}; //magic tag to make sure file version and in/out order of variables are the same
    qint32 braggVersion {100}; //1.0.0

    bool saveToFile(QFile &file, const braggParams &p);
    braggParams loadFromFile(QFile &file);
};


inline QDataStream &operator<<(QDataStream &out, const braggParams &p)
{
    // same order as braggParams struct for easier overview
    out << p.decimals;
    out << p.energyCurIndex;
    out << p.lambdaCurIndex;
    out << p.twoDCurIndex;
    out << p.braggCurIndex;
    out << p.normalCurIndex;
    out << p.braggInDegree;
    out << p.normalInDegree;
    out << p.energy;
    out << p.lambda;
    out << p.twoD;
    out << p.reflOrder;
    out << p.bragg;
    out << p.normal;
    out << p.crystalBoxChecked;
    out << p.xrayBoxChecked;
    out << p.curFolder.absolutePath();
    return out;
}


inline QDataStream &operator>>( QDataStream &in, braggParams &p)
{
    in >> p.decimals;
    in >> p.energyCurIndex;
    in >> p.lambdaCurIndex;
    in >> p.twoDCurIndex;
    in >> p.braggCurIndex;
    in >> p.normalCurIndex;
    in >> p.braggInDegree;
    in >> p.normalInDegree;
    in >> p.energy;
    in >> p.lambda;
    in >> p.twoD;
    in >> p.reflOrder;
    in >> p.bragg;
    in >> p.normal;
    in >> p.crystalBoxChecked;
    in >> p.xrayBoxChecked;
    QString path;
    in >> path;
    p.curFolder.setPath(path);

    return in;
}

#endif // BRAGGSERIALIZE_H
