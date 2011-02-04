
QT += network xml

TARGET = smser

TEMPLATE = app

CONFIG += debug warn_on

win32{
PRECOMPILED_HEADER = stable.h
CONFIG += precompile_header
}

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
    logger.h \
    stable.h

FORMS += \
    mainwidget.ui

RESOURCES += \
    icons.qrc


UI_DIR = .ui
MOC_DIR = .moc
release:OBJECTS_DIR = .obj/release
debug:OBJECTS_DIR = .obj/debug
RCC_DIR = .rc

#turn on extra g++ warninngs
QMAKE_CXXFLAGS += -Wold-style-cast -Woverloaded-virtual -Wsign-promo
#huge list of warnings are come from Qt
#QMAKE_CXXFLAGS += -Weffc++ 

#windows icon and file info
win32:
{ 
    RC_FILE = smser.rc 
    QMAKE_LFLAGS *= -static-libgcc
}

#symbian
#{

#    RSS_RULES ="group_name=\"SMSER\";"

#   vendorinfo = \
#   "; Igor Sobinov" \
#    "%{\"Igor Sobinov\"}" \
#    " " \
#    "; Igor Sobinov" \
#    ":\"Igor Sobinov\"" \
#    " "

#    examples_deployment.pkg_prerules += vendorinfo
#    DEPLOYMENT += examples_deployment

#    ICON = img/heardt2.png
#}
