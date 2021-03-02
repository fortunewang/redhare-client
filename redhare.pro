QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = redhare
TEMPLATE = app

CONFIG += precompile_header

PRECOMPILED_HEADER = stable.h

win32 {
    LIBS += user32.lib
}

SOURCES += \
    logindialog.cpp \
    accountmanager.cpp \
    mainwidget.cpp \
    application.cpp \
    rostermanager.cpp \
    rosterentry.cpp \
    rosterentrywidget.cpp \
    rosterwidget.cpp \
    rostergroupheaderwidget.cpp \
    rostergroupwidget.cpp \
    rhscrollbar.cpp \
    localtest.cpp \
    rhconfig.cpp \
    questiondialog.cpp \
    chatwidget.cpp \
    scrotdialog.cpp \
    photo_processing.cpp

HEADERS  += \
    logindialog.h \
    accountmanager.h \
    stable.h \
    clientsocket.h \
    mainwidget.h \
    rostermanager.h \
    rosterentry.h \
    rosterwidget.h \
    rosterentrywidget.h \
    rostergroupheaderwidget.h \
    rostergroupwidget.h \
    rhscrollbar.h \
    localtest.h \
    rhconfig.h \
    questiondialog.h \
    chatwidget.h \
    scrotdialog.h \
    photo_processing.h

FORMS    += \
    logindialog.ui \
    mainwidget.ui \
    rosterentrywidget.ui \
    rostergroupheaderwidget.ui \
    questiondialog.ui \
    chatwidget.ui

RC_ICONS = res/redhare.ico

RESOURCES += \
    redhare.qrc
