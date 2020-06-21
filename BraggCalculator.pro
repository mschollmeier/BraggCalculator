QT       += core gui printsupport help
QTPLUGIN += cocoaprintersupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

requires(qtConfig(undoview))

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutwindow.cpp \
    braggserialize.cpp \
    braggspinbox.cpp \
    createbraggtextdoc.cpp \
    main.cpp \
    braggcalc.cpp \
    undocommands.cpp

HEADERS += \
    aboutwindow.h \
    braggcalc.h \
    braggparams.h \
    braggserialize.h \
    braggspinbox.h \
    createbraggtextdoc.h \
    myapp.h \
    undocommands.h

FORMS += \
    aboutwindow.ui \
    braggcalc.ui

TARGET = "Bragg Angle Calculator"

# major, minor, patch level, and build number
VERSION = 1.0.0.0
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"

macx {
    ICON = BraggCalculator.icns
}

win32{
    RC_ICONS = BraggCalcIcon.ico
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    braggResources.qrc