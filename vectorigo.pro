QT       += core gui
QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ellipse.cpp \
    ellipsetool.cpp \
    main.cpp \
    mainwindow.cpp \
    rectangle.cpp \
    toolmanager.cpp \
    vcolorpicker.cpp \
    vgrabber.cpp \
    vmousetool.cpp \
    vrectangletool.cpp \
    vscene.cpp \
    vshape.cpp \
    vtool.cpp \
    vview.cpp \
    qdialog.cpp

HEADERS += \
    ellipse.h \
    ellipsetool.h \
    mainwindow.h \
    rectangle.h \
    toolmanager.h \
    vcolorpicker.h \
    vgrabber.h \
    vmousetool.h \
    vrectangletool.h \
    vscene.h \
    vshape.h \
    vtool.h \
    vview.h \
    qdialog.h

FORMS += \
    mainwindow.ui\
    qdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
