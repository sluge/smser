
QT += core gui network xml

TARGET = smser

TEMPLATE = app

CONFIG += debug warn_on

SOURCES += main.cpp \
    mainwidget.cpp \
    utils.cpp \
    logger.cpp

HEADERS += \
    mainwidget.h \
    defines.h \
    types.h \
    config.h \
    utils.h \
    logger.h

FORMS += \
    mainwidget.ui

RESOURCES += \
    icons.qrc

UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj
RCC_DIR = .rc

#windows icon and file info
win32:
{ 
    RC_FILE = smser.rc 
    QMAKE_LFLAGS *= -static-libgcc
}
