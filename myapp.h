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
