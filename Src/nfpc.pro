#-------------------------------------------------
#
# Wacek 6.12.2012 18:26:50
#
#-------------------------------------------------

include(qextserialport/qextserialport.pri)

QT       += core gui

TARGET = nfpc
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    nf/nfv2.c \
    comsender.cpp \
    comreader.cpp \
    nfv2_config.c

HEADERS  += mainwindow.h \
    nfv2_config.h \
    comsender.h \
    comreader.h

FORMS    += mainwindow.ui

INCLUDEPATH += nf/

OTHER_FILES += \
    qextserialport/qextserialport.pri
