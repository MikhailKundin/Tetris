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
    src/main.cpp \
    src/model/abstractfigure.cpp \
    src/model/block.cpp \
    src/view/mainmenuwdt.cpp \
    src/view/mainwindow.cpp \
    src/view/playground.cpp \
    src/view/pointswgt.cpp \
    src/view/recordtable.cpp \
    src/view/singlewgt.cpp

HEADERS += \
	src/model/abstractfigure.h \
	src/model/block.h \
	src/view/mainmenuwdt.h \
	src/view/mainwindow.h \
	src/view/playground.h \
	src/view/pointswgt.h \
	src/view/recordtable.h \
	src/view/singlewgt.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
	src/view/mainmenuwdt.ui \
	src/view/mainwindow.ui \
	src/view/pointswgt.ui \
	src/view/recordtable.ui \
	src/view/singlewgt.ui

RESOURCES += \
	resources.qrc
