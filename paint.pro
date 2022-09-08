QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/DrawingStratigies
INCLUDEPATH += $$PWD/Algorithms
INCLUDEPATH += $$PWD/Widgets


SOURCES += \
    Algorithms/zoom.cpp \
    DrawingStratigies/ellipsedrawstrategy.cpp \
    Algorithms/floodfill.cpp \
    DrawingStratigies/floodfillstrategy.cpp \
    DrawingStratigies/linedrawstrategy.cpp \
    main.cpp \
    Widgets/mainwindow.cpp \
    DrawingStratigies/pendrawstrategy.cpp \
    DrawingStratigies/rectangledrawstrategy.cpp \
    Widgets/scribblearea.cpp \
    Widgets/slider.cpp \
    usersettings.cpp

HEADERS += \
    Algorithms/zoom.h \
    DrawingStratigies/drawstrategy.h \
    DrawingStratigies/ellipsedrawstrategy.h \
    Algorithms/floodfill.h \
    DrawingStratigies/floodfillstrategy.h \
    DrawingStratigies/linedrawstrategy.h \
    Widgets/mainwindow.h \
    DrawingStratigies/pendrawstrategy.h \
    DrawingStratigies/rectangledrawstrategy.h \
    Widgets/scribblearea.h \
    Widgets/slider.h \
    usersettings.h

FORMS += \
    Widgets/mainwindow.ui \
    Widgets/slider.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MyIcons.qrc

DISTFILES +=
