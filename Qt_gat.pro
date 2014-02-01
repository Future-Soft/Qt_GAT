#-------------------------------------------------
#
# Project created by QtCreator 2012-03-23T01:45:35
#
#-------------------------------------------------

QT       += network
QT       += webkit

#QT       -= gui

TARGET = Qt_gat
TEMPLATE = lib
CONFIG += staticlib
CONFIG += mobility
MOBILITY += systeminfo

SOURCES += tracker.cpp \
    request.cpp \
    event.cpp \
    pageview.cpp \
    trackingurl.cpp #\
   # main.cpp

HEADERS += tracker.h \
    request.h \
    event.h \
    pageview.h \
    trackingurl.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

















