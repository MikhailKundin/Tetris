QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= debug_and_release debug_and_release_target

CONFIG(debug, debug|release){
DESTDIR = build/debug
OBJECTS_DIR = build/debug/bin
MOC_DIR = build/debug/bin
RCC_DIR = build/debug/bin
UI_DIR = build/debug/bin
}

CONFIG(release, debug|release){
DESTDIR = build/release
OBJECTS_DIR = build/release/bin
MOC_DIR = build/release/bin
RCC_DIR = build/release/bin
UI_DIR = build/release/bin
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/mainmenuwdt.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/playground.cpp \
    src/pointswgt.cpp \
    src/recordtable.cpp \
    src/singlewgt.cpp

HEADERS += \
	src/mainmenuwdt.h \
	src/mainwindow.h \
	src/playground.h \
	src/pointswgt.h \
	src/recordtable.h \
	src/singlewgt.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
	src/mainmenuwdt.ui \
	src/mainwindow.ui \
	src/pointswgt.ui \
	src/recordtable.ui \
	src/singlewgt.ui

RESOURCES += \
	resources.qrc
