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

#include "createbraggtextdoc.h"

#include <QAbstractTextDocumentLayout>
#include <QObject>

void bragg::createBraggTextDoc(QTextDocument &doc, const braggParams &p)
{
    doc.setUseDesignMetrics(true);

    QFont f(doc.defaultFont());
    f.setPointSize(10);
    doc.setDefaultFont(f);

    QString text("Bragg Angle Calculator:\n\n");
    text.append("X-Ray Parameters:\n");
    text.append(QObject::tr("    - Energy: %1 %2\n")
                .arg(QString::number(p.energy, 'f', p.decimals))
                .arg(p.energyUnitList[p.energyCurIndex]));
    text.append(QObject::tr("    - Wavelength: %1 %2\n\n")
                .arg(QString::number(p.lambda, 'f', p.decimals))
                .arg(p.lambdaUnitList[p.lambdaCurIndex]));

    text.append("Crystal Parameters:\n");
    text.append(QObject::tr("    - 2d spacing: %1 %2\n")
                .arg(QString::number(p.twoD, 'f', p.decimals))
                .arg(p.twoDUnitList[p.twoDCurIndex]));
    text.append(QObject::tr("    - Reflection order: %1\n\n")
                .arg(p.reflOrder));

    text.append("Bragg Angle:\n");
    text.append(QObject::tr("    - Angle to surface: %1 %2\n")
                .arg(QString::number(p.bragg, 'f', p.decimals))
                .arg(p.braggUnitList[p.braggCurIndex]));
    text.append(QObject::tr("    - Angle to normal: %1 %2\n")
                .arg(QString::number(p.normal, 'f', p.decimals))
                .arg(p.normalUnitList[p.normalCurIndex]));

    doc.setPlainText(text);
}
