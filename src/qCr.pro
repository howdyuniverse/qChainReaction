#-------------------------------------------------
#
# Project created by QtCreator 2011-05-27T21:22:37
#
#-------------------------------------------------

QT       += opengl

TARGET = qCr
TEMPLATE = app

INCLUDEPATH += . \
    widgets \
    core

SOURCES += main.cpp \
        widgets/mainwindow.cpp \
    widgets/glwidget.cpp \
    widgets/recordsdialog.cpp \
    core/Game.cpp \
    core/Drawing.cpp \
    core/Circles.cpp \
    core/Circle.cpp

HEADERS  += widgets/mainwindow.h \
    widgets/glwidget.h \
    widgets/recordsdialog.h \
    core/Game.h \
    core/Drawing.h \
    core/Circles.h \
    core/Circle.h

RESOURCES += \
    resources/cr.qrc
