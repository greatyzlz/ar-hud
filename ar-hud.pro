TEMPLATE = app
#CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt
CONFIG += console c++11 app_bundle
QT += core gui widgets

INCLUDEPATH += -I/usr/local/include
LIBS += -L/usr/local/lib/ -L/home/bot/samba/ar-hud/libs -lhvUtilty -lhvLog -ldl -lhascoqt -lassimp -lpthread


SOURCES += \
        hvanimation.cpp \
        hvglobaldata.cpp \
        hvhmi.cpp \
        hvhmiconfig.cpp \
        hvlayermanager.cpp \
        hvldwscene.cpp \
        hvprioritymanager.cpp \
        hvregionmanager.cpp \
        hvscene.cpp \
        hvscreen.cpp \
        hvscreenmanager.cpp \
        hvstrategymanager.cpp \
        main.cpp \
    hvbsdscene.cpp \
    hvfcwscene.cpp

HEADERS += \
    graphengine.h \
    hvanimation.h \
    hvglobaldata.h \
    hvhmi.h \
    hvhmiconfig.h \
    hvlayermanager.h \
    hvldwscene.h \
    hvprioritymanager.h \
    hvregionmanager.h \
    hvscene.h \
    hvscenedeclarations.h \
    hvscreen.h \
    hvscreenmanager.h \
    hvstrategymanager.h \
    hvTypes.h \
    hvbsdscene.h \
    hvfcwscene.h

DISTFILES += \
    hmi_config.json \
    ldw.png \
    bsd_R.png
