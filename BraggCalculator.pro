##### GPL ####################################################################
# This file defines the compilation process for qmake                        #
#                                                                            #
# Copyright (c) 2020  Marius S. Schollmeier                                  #
#                                                                            #
# This program is free software: you can redistribute it and/or modify       #
# it under the terms of the GNU General Public License as published by       #
# the Free Software Foundation, either version 3 of the License, or          #
# (at your option) any later version.                                        #
#                                                                            #
# This program is distributed in the hope that it will be useful,            #
# but WITHOUT ANY WARRANTY; without even the implied warranty of             #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
# GNU General Public License for more details.                               #
#                                                                            #
# You should have received a copy of the GNU General Public License          #
# along with this program.  If not, see <https://www.gnu.org/licenses/       #
#                                                                            #
##############################################################################
# Author:  Marius Schollmeier,                                               #
# Contact: mschollmeier01@gmail.com                                          #
# Date:    Dec. 02, 2020                                                     #
# Version: 1.0                                                               #
##############################################################################


include(src/qmake-target-platform.pri)
include(src/qmake-destination-path.pri)

QT       += core gui printsupport help
QTPLUGIN += cocoaprintersupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

requires(qtConfig(undoview))


BINARYPATH = $$PWD/binaries/
DESTDIR = $$BINARYPATH/$$DESTINATION_PATH

BUILDPATH = $$PWD/build/BraggCalculator/
OBJECTS_DIR = $$BUILDPATH/$$DESTINATION_PATH/.obj
MOC_DIR = $$BUILDPATH/$$DESTINATION_PATH/.moc
RCC_DIR = $$BUILDPATH/$$DESTINATION_PATH/.qrc
UI_DIR = $$BUILDPATH/$$DESTINATION_PATH/.ui


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_DEBUG
    msvc{
        QMAKE_CFLAGS = /O2
        QMAKE_CXXFLAGS = /O2
        }
    else{
        QMAKE_CFLAGS -= -O2
        QMAKE_CFLAGS -= -O1
        QMAKE_CXXFLAGS -= -O2
        QMAKE_CXXFLAGS -= -O1
        QMAKE_CFLAGS = -m64 -O3
        QMAKE_LFLAGS = -m64 -O3
        QMAKE_CXXFLAGS = -m64 -O3
    }
}

SOURCES += \
    src/aboutwindow.cpp \
    src/braggserialize.cpp \
    src/braggspinbox.cpp \
    src/createbraggtextdoc.cpp \
    src/main.cpp \
    src/braggcalc.cpp \
    src/undocommands.cpp

HEADERS += \
    src/aboutwindow.h \
    src/braggcalc.h \
    src/braggparams.h \
    src/braggserialize.h \
    src/braggspinbox.h \
    src/createbraggtextdoc.h \
    src/constants.h \
    src/myapp.h \
    src/undocommands.h \
    src/unicodecharacters.h

FORMS += \
    src/aboutwindow.ui \
    src/braggcalc.ui

TARGET = "Bragg Angle Calculator"

# major, minor
VERSION = 1.0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"

macx {
    ICON = res/BraggCalculator.icns
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 13
}

win32{
    RC_ICONS = res/BraggCalcIcon.ico
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/braggResources.qrc
