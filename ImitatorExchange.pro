QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    nwdgraphicview.cpp \
    nwindow.cpp \
    wdcom.cpp \
    wddoc.cpp \
    wdgraphicview.cpp \
    wdobj.cpp \
    window.cpp

HEADERS += \
    nwdgraphicview.h \
    nwindow.h \
    wdcom.h \
    wddoc.h \
    wdgraphicview.h \
    wdobj.h \
    window.h

FORMS += \
    nwindow.ui \
    wdcom.ui \
    wddoc.ui \
    wdobj.ui \
    window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
