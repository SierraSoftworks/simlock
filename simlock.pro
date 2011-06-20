#-------------------------------------------------
#
# Project created by QtCreator 2011-05-28T12:42:15
#
#-------------------------------------------------

QT       += core
QT	 += dbus
QT	 += sql

PKGCONFIG	+= mce

QT       -= gui
QT	 -= xml

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
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/postinst \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    simlock \
    SIMLock.install \
    qtc_packaging/debian_fremantle/rules.autobuilder \
    qtc_packaging/debian_fremantle/rules
