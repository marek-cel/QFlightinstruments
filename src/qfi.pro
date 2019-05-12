#-------------------------------------------------
#
# Project created by QtCreator 2013-09-19T16:09:01
#
#-------------------------------------------------

QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qfi
TEMPLATE = lib

#-------------------------------------------------

DEFINES += QFI_LIBRARY

win32: DEFINES += WIN32 _WINDOWS _USE_MATH_DEFINES

win32:CONFIG(release, debug|release):    DEFINES += NDEBUG
else:win32:CONFIG(debug, debug|release): DEFINES += _DEBUG

#-------------------------------------------------

INCLUDEPATH += ./

#-------------------------------------------------

HEADERS += \
    qfi_ADI.h \
    qfi_HSI.h \
    qfi_NAV.h \
    qfi_PFD.h \
    qfi_VSI.h \
    qfi_ASI.h \
    qfi_ALT.h \
    qfi_TC.h

SOURCES += \
    qfi_ADI.cpp \
    qfi_HSI.cpp \
    qfi_NAV.cpp \
    qfi_PFD.cpp \
    qfi_VSI.cpp \
    qfi_ASI.cpp \
    qfi_ALT.cpp \
    qfi_TC.cpp

RESOURCES += \
    qfi.qrc

#-------------------------------------------------

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
