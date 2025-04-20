set(TARGET_NAME qfi_example)

################################################################################

set(CPP_FILES
    main.cpp
    LayoutSquare.cpp
    MainWindow.cpp
    WidgetAI.cpp
    WidgetALT.cpp
    WidgetASI.cpp
    WidgetEADI.cpp
    WidgetEHSI.cpp
    WidgetHI.cpp
    WidgetSix.cpp
    WidgetTC.cpp
    WidgetVSI.cpp
)

set(MOC_SRC_FILES
    LayoutSquare.h
    MainWindow.h
    WidgetAI.h
    WidgetALT.h
    WidgetASI.h
    WidgetEADI.h
    WidgetEHSI.h
    WidgetHI.h
    WidgetSix.h
    WidgetTC.h
    WidgetVSI.h
)

set(UIC_SRC_FILES
    MainWindow.ui
    WidgetAI.ui
    WidgetALT.ui
    WidgetASI.ui
    WidgetEADI.ui
    WidgetEHSI.ui
    WidgetHI.ui
    WidgetSix.ui
    WidgetTC.ui
    WidgetVSI.ui
)

set(SOURCES ${CPP_FILES} ${MOC_SRC_FILES} ${UIC_SRC_FILES})

################################################################################

add_executable(${TARGET_NAME} WIN32 ${SOURCES})

set(LIBS
    qfi
    ${QT_LIBRARIES}
)

target_link_libraries(${TARGET_NAME} ${LIBS})

qt5_use_modules(${TARGET_NAME} Core Widgets Svg)

################################################################################

set_target_properties(${TARGET_NAME} PROPERTIES
    EXCLUDE_FROM_ALL True
)

