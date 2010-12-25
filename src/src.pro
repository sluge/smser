
QT += network xml

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
release:OBJECTS_DIR = .obj/release
debug:OBJECTS_DIR = .obj/debug
RCC_DIR = .rc

#windows icon and file info
win32:
{ 
    RC_FILE = smser.rc 
    QMAKE_LFLAGS *= -static-libgcc
}
