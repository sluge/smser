
QT += core gui network xml

TARGET = smser

TEMPLATE = app

CONFIG += debug warn_on

SOURCES += main.cpp \
    mainwidget.cpp \
    utils.cpp

HEADERS += \
    mainwidget.h \
    defines.h \
    types.h \
    config.h \
    utils.h

FORMS += \
    mainwidget.ui

RESOURCES += \
    icons.qrc

UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj
RCC_DIR = .rc
