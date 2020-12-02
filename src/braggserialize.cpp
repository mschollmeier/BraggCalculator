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

#include "braggserialize.h"

bool braggSerialize::saveToFile(QFile &file, const braggParams &p)
{
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_14);
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);

    // write header
    out << static_cast<quint32>(magicNumber);
    out << static_cast<qint32>(braggVersion);
    out << p;

    file.close();
    return true;
}


braggParams braggSerialize::loadFromFile(QFile &file)
{
    QDataStream in(&file);

    // Read and check the header
    quint32 magic;
    in >> magic;
    if (magic != this->magicNumber)
        throw std::runtime_error("Wrong file format.");

    // Read the version
    qint32 version;
    in >> version;
    if (version < braggVersion)
        throw std::runtime_error("File format too old.");
    if (version > braggVersion)
        throw std::runtime_error("File format too new, please upgrade Bragg Calculator");

    if (version == braggVersion)
        in.setVersion(QDataStream::Qt_5_14);

    // Read the actual data
    braggParams p {};
    in >> p;

    file.close();

    return p;
}
