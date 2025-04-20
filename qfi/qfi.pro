QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

################################################################################

DESTDIR = $$PWD/../lib
TARGET = qfi

################################################################################

win32: CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2
unix:  CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2

win32: QMAKE_LFLAGS += /INCREMENTAL:NO


################################################################################

DEFINES += QFI_DLL_EXPORTS

DEFINES += QT_DEPRECATED_WARNINGS

greaterThan(QT_MAJOR_VERSION, 4):win32: DEFINES += USE_QT5

win32: DEFINES += \
    NOMINMAX \
    WIN32 \
    _WINDOWS \
    _CRT_SECURE_NO_DEPRECATE \
    _SCL_SECURE_NO_WARNINGS \
    _USE_MATH_DEFINES

win32: CONFIG(release, debug|release): DEFINES += NDEBUG
win32: CONFIG(debug, debug|release):   DEFINES += _DEBUG

unix: DEFINES += _LINUX_

INCLUDEPATH += ..

################################################################################

HEADERS += \
    $$PWD/qfi_defs.h \
    $$PWD/qfi_doxygen.h

################################################################################

HEADERS += \
    $$PWD/qfi_Colors.h \
    $$PWD/qfi_Fonts.h

SOURCES += \
    $$PWD/qfi_Colors.cpp \
    $$PWD/qfi_Fonts.cpp

################################################################################
# Electronic Flight Instrument System (EFIS)
################################################################################

HEADERS += \
    $$PWD/qfi_EADI.h \
    $$PWD/qfi_EHSI.h

SOURCES += \
    $$PWD/qfi_EADI.cpp \
    $$PWD/qfi_EHSI.cpp

################################################################################
# Basic Six
################################################################################

HEADERS += \
    $$PWD/qfi_AI.h \
    $$PWD/qfi_HI.h \
    $$PWD/qfi_VSI.h \
    $$PWD/qfi_ASI.h \
    $$PWD/qfi_ALT.h \
    $$PWD/qfi_TC.h

SOURCES += \
    $$PWD/qfi_AI.cpp \
    $$PWD/qfi_HI.cpp \
    $$PWD/qfi_VSI.cpp \
    $$PWD/qfi_ASI.cpp \
    $$PWD/qfi_ALT.cpp \
    $$PWD/qfi_TC.cpp

################################################################################
# Resources
################################################################################

RESOURCES += \
    $$PWD/qfi.qrc
