QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ellipsedrawstrategy.cpp \
    floodfill.cpp \
    floodfillstrategy.cpp \
    linedrawstrategy.cpp \
    main.cpp \
    mainwindow.cpp \
    pendrawstrategy.cpp \
    rectangledrawstrategy.cpp \
    scribblearea.cpp \
    slider.cpp \
    usersettings.cpp

HEADERS += \
    drawstrategy.h \
    ellipsedrawstrategy.h \
    floodfill.h \
    floodfillstrategy.h \
    linedrawstrategy.h \
    mainwindow.h \
    pendrawstrategy.h \
    rectangledrawstrategy.h \
    scribblearea.h \
    slider.h \
    usersettings.h

FORMS += \
    mainwindow.ui \
    slider.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
