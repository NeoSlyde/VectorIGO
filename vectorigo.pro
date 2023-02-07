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
    vdocument.cpp \
    vexporter.cpp \
    vgrabber.cpp \
    vmousetool.cpp \
    vpanelvisitor.cpp \
    vrectangletool.cpp \
    vscene.cpp \
    vserializevisitor.cpp \
    vshape.cpp \
    vshapevisitor.cpp \
    vtool.cpp \
    vtoolbutton.cpp \
    vverticallayout.cpp \
    vview.cpp

HEADERS += \
    ellipse.h \
    ellipsetool.h \
    mainwindow.h \
    rectangle.h \
    toolmanager.h \
    vcolorpicker.h \
    vdocument.h \
    vexporter.h \
    vgrabber.h \
    vmousetool.h \
    vpanelvisitor.h \
    vrectangletool.h \
    vscene.h \
    vserializevisitor.h \
    vshape.h \
    vshapevisitor.h \
    vtool.h \
    vtoolbutton.h \
    vverticallayout.h \
    vview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
