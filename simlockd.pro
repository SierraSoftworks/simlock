#-------------------------------------------------
#
# Project created by QtCreator 2011-05-28T12:42:15
#
#-------------------------------------------------

QT       += core
QT	 += dbus
QT	 += sql
QT	 += maemo5

PKGCONFIG	+= mce

QT       -= gui

TARGET = simlock
CONFIG   += console
CONFIG   -= app_bundle
CONFIG	 += link_pkgconfig

TEMPLATE = app


SOURCES += main.cpp \
    simlockservice.cpp \
    databaseinterface.cpp \
    simlock.cpp \
    notifications.cpp

HEADERS += \
    simlockservice.h \
    databaseinterface.h \
    simlock.h \
    notifications.h


# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    simlockd
