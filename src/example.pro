#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T17:03:18
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qfi_example
TEMPLATE = app

#-------------------------------------------------

win32: DEFINES += WIN32 _WINDOWS _USE_MATH_DEFINES

win32:CONFIG(release, debug|release):    DEFINES += NDEBUG
else:win32:CONFIG(debug, debug|release): DEFINES += _DEBUG

#-------------------------------------------------

INCLUDEPATH += ./ ./example

#-------------------------------------------------

HEADERS += \
    example/LayoutSquare.h \
    example/MainWindow.h \
    example/WidgetADI.h \
    example/WidgetALT.h \
    example/WidgetASI.h \
    example/WidgetHSI.h \
    example/WidgetNAV.h \
    example/WidgetPFD.h \
    example/WidgetTC.h \
    example/WidgetVSI.h \
    qfi_ADI.h \
    qfi_HSI.h \
    qfi_NAV.h \
    qfi_PFD.h \
    qfi_VSI.h \
    qfi_ASI.h \
    qfi_ALT.h \
    qfi_TC.h \
    example/WidgetSix.h

SOURCES += \
    example/LayoutSquare.cpp \
    example/main.cpp \
    example/MainWindow.cpp \
    example/WidgetADI.cpp \
    example/WidgetALT.cpp \
    example/WidgetASI.cpp \
    example/WidgetHSI.cpp \
    example/WidgetNAV.cpp \
    example/WidgetPFD.cpp \
    example/WidgetTC.cpp \
    example/WidgetVSI.cpp \
    qfi_ADI.cpp \
    qfi_HSI.cpp \
    qfi_NAV.cpp \
    qfi_PFD.cpp \
    qfi_VSI.cpp \
    qfi_ASI.cpp \
    qfi_ALT.cpp \
    qfi_TC.cpp \
    example/WidgetSix.cpp

FORMS += \
    example/MainWindow.ui \
    example/WidgetADI.ui \
    example/WidgetALT.ui \
    example/WidgetASI.ui \
    example/WidgetHSI.ui \
    example/WidgetNAV.ui \
    example/WidgetPFD.ui \
    example/WidgetTC.ui \
    example/WidgetVSI.ui \
    example/WidgetSix.ui

RESOURCES += \
    qfi.qrc
