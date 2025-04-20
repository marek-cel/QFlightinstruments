set(TARGET_NAME qfi)

################################################################################

if(WIN32)
    if(BUILD_SHARED_LIBS)
        add_definitions(-DQFI_DLL_EXPORTS)
    endif()
endif()

################################################################################

set(CPP_FILES
    qfi_AI.cpp
    qfi_ALT.cpp
    qfi_ASI.cpp
    qfi_Colors.cpp
    qfi_EADI.cpp
    qfi_EHSI.cpp
    qfi_Fonts.cpp
    qfi_HI.cpp
    qfi_TC.cpp
    qfi_VSI.cpp
)

set(MOC_SRC_FILES
    qfi_AI.h
    qfi_ALT.h
    qfi_ASI.h
    qfi_EADI.h
    qfi_EHSI.h
    qfi_HI.h
    qfi_TC.h
    qfi_VSI.h
)

set(RCC_SRC_FILES
    qfi.qrc
)

set(SOURCES ${CPP_FILES} ${MOC_SRC_FILES} ${RCC_SRC_FILES})

set(HEADERS
    ${MOC_SRC_FILES}
    qfi_defs.h
    qfi_doxygen.h
    qfi_Colors.h
    qfi_Fonts.h
)

################################################################################

add_library(${TARGET_NAME} ${SOURCES})

################################################################################

qt5_use_modules(${TARGET_NAME} Core Widgets Svg)

################################################################################

set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION ${QFI_VERSION_STRING}
    SOVERSION ${QFI_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qfi
)
