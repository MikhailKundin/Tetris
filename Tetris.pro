QT       += core gui network sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big
CONFIG -= debug_and_release debug_and_release_target

CONFIG(debug, debug|release){
DESTDIR = build/debug
OBJECTS_DIR = build/temp/debug/obj
MOC_DIR = build/temp/debug/moc
RCC_DIR = build/temp/debug/rcc
UI_DIR = build/temp/debug/ui
}

CONFIG(release, debug|release){
DESTDIR = build/release
OBJECTS_DIR = build/temp/release/obj
MOC_DIR = build/temp/release/moc
RCC_DIR = build/temp/release/rcc
UI_DIR = build/temp/release/ui
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Database.cpp \
    src/TetrisInfo.cpp \
    src/controllers/GeneralController.cpp \
    src/controllers/OfflineController.cpp \
    src/AbstractFigure.cpp \
    src/Block.cpp \
    src/controllers/OnlineController.cpp \
    src/controllers/SoundController.cpp \
    src/views/ButtonPanel.cpp \
    src/views/ConnectOnlineWgt.cpp \
    src/views/LevelFigurePnl.cpp \
    src/views/LevelPnl.cpp \
    src/views/MainMenuWgt.cpp \
    src/views/MainWindow.cpp \
    src/views/NextFigurePnl.cpp \
    src/views/OnlineWgt.cpp \
    src/views/PlaygroundPnl.cpp \
    src/views/PointsPnl.cpp \
    src/views/PushLabel.cpp \
    src/views/RecordTablePnl.cpp \
    src/main.cpp \
    src/views/SaveResultsWgt.cpp \
    src/views/SingleWgt.cpp \
    src/views/WidgetInfo.cpp

HEADERS += \
	src/Database.h \
	src/TetrisInfo.h \
	src/controllers/GeneralController.h \
	src/controllers/OfflineController.h \
	src/AbstractFigure.h \
	src/Block.h \
	src/controllers/OnlineController.h \
	src/controllers/SoundController.h \
	src/views/ButtonPanel.h \
	src/views/ConnectOnlineWgt.h \
	src/views/LevelFigurePnl.h \
	src/views/LevelPnl.h \
	src/views/MainMenuWgt.h \
	src/views/MainWindow.h \
	src/views/NextFigurePnl.h \
	src/views/OnlineWgt.h \
	src/views/PlaygroundPnl.h \
	src/views/PointsPnl.h \
	src/views/PushLabel.h \
	src/views/RecordTablePnl.h \
	src/views/SaveResultsWgt.h \
	src/views/SingleWgt.h \
	src/views/WidgetInfo.h

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
	src/ui/SaveResultsWgt.ui \
	src/ui/ConnectOnlineWgt.ui \
	src/ui/OnlineWgt.ui \
	src/ui/ButtonPanel.ui

RESOURCES += \
	resources.qrc
