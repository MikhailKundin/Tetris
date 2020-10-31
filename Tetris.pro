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
    src/Database.cpp \
    src/TetrisInfo.cpp \
    src/controller/GeneralController.cpp \
    src/controller/OfflineController.cpp \
    src/model/AbstractFigure.cpp \
    src/model/Block.cpp \
    src/view/LevelFigurePnl.cpp \
    src/view/LevelPnl.cpp \
    src/view/MainMenuWgt.cpp \
    src/view/MainWindow.cpp \
    src/view/NextFigurePnl.cpp \
    src/view/PlaygroundPnl.cpp \
    src/view/PointsPnl.cpp \
    src/view/PushLabel.cpp \
    src/view/RecordTablePnl.cpp \
    src/main.cpp \
    src/view/SaveResultsWgt.cpp \
    src/view/SingleWgt.cpp \
    src/view/WidgetInfo.cpp

HEADERS += \
	src/Database.h \
	src/TetrisInfo.h \
	src/controller/GeneralController.h \
	src/controller/OfflineController.h \
	src/model/AbstractFigure.h \
	src/model/Block.h \
	src/view/LevelFigurePnl.h \
	src/view/LevelPnl.h \
	src/view/MainMenuWgt.h \
	src/view/MainWindow.h \
	src/view/NextFigurePnl.h \
	src/view/PlaygroundPnl.h \
	src/view/PointsPnl.h \
	src/view/PushLabel.h \
	src/view/RecordTablePnl.h \
	src/view/SaveResultsWgt.h \
	src/view/SingleWgt.h \
	src/view/WidgetInfo.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
	src/ui/MainMenuWgt.ui \
	src/ui/MainWindow.ui \
	src/ui/PointsPnl.ui \
	src/ui/SingleWgt.ui \
	src/ui/LevelPnl.ui \
	src/ui/LevelFigurePnl.ui \
	src/ui/SaveResultsWgt.ui

RESOURCES += \
	resources.qrc
