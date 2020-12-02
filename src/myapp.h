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


#ifndef MYAPP_H
#define MYAPP_H

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QOperatingSystemVersion>

#include "braggcalc.h"

// https://www.qtcentre.org/threads/42679-Check-If-Application-now-has-focus-again
class MyApp : public QApplication
{
    Q_OBJECT

public:
    //constructor
    MyApp(int argc, char *argv[]) : QApplication(argc, argv)
    {
#ifndef QT_DEBUG
        if (currentOS == QOperatingSystemVersion::MacOS)
            this->setQuitOnLastWindowClosed(false);
#endif

        _w = new braggCalc;
    }

    //destructor
    ~MyApp()
    {
        delete _w;
    }

    bool event(QEvent *pEvent)
    {

        if (currentOS == QOperatingSystemVersion::MacOS) {
            if (pEvent->type() == QEvent::ApplicationActivate) {
                if (!_w->isVisible()) {
                    _w->reset();
                    _w->show();
                }
            }
            //        else if ( pEvent->type() == QEvent::ApplicationDeactivate )
            //        {
            //            qDebug() << "ApplicationDeactivate";
            ////            _w->hide();
            //        }

        }
        return QApplication::event(pEvent);
    }

private:
    braggCalc *_w;
    QOperatingSystemVersion::OSType currentOS = QOperatingSystemVersion::currentType();
};


#endif // MYAPP_H
