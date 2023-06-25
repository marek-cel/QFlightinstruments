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
