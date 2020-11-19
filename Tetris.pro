QT += core gui widgets network sql multimedia

CONFIG += c++17
CONFIG += resources_big
CONFIG -= debug_and_release debug_and_release_target

CONFIG(debug, debug|release){
win32:DESTDIR = build/Windows/debug
win32:OBJECTS_DIR = build/Windows/temp/debug/obj
win32:MOC_DIR = build/Windows/temp/debug/moc
win32:RCC_DIR = build/Windows/temp/debug/rcc
win32:UI_DIR = build/Windows/temp/debug/ui

unix:DESTDIR = build/Unix/debug
unix:OBJECTS_DIR = build/Unix/temp/debug/obj
unix:MOC_DIR = build/Unix/temp/debug/moc
unix:RCC_DIR = build/Unix/temp/debug/rcc
unix:UI_DIR = build/Unix/temp/debug/ui
}

CONFIG(release, debug|release){
win32:DESTDIR = build/Windows/release
win32:OBJECTS_DIR = build/Windows/temp/release/obj
win32:MOC_DIR = build/Windows/temp/release/moc
win32:RCC_DIR = build/Windows/temp/release/rcc
win32:UI_DIR = build/Windows/temp/release/ui

unix:DESTDIR = build/Unix/release
unix:OBJECTS_DIR = build/Unix/temp/release/obj
unix:MOC_DIR = build/Unix/temp/release/moc
unix:RCC_DIR = build/Unix/temp/release/rcc
unix:UI_DIR = build/Unix/temp/release/ui
}

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
	
win32:RC_ICONS = $$PWD/etc/Images/Icons/Icon.ico

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
