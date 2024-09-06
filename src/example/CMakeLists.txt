cmake_minimum_required(VERSION 3.14)

# Define the project name and version
project(qfi_example2 VERSION 1.0 LANGUAGES CXX)

# Find required packages (Qt5 or Qt6 based on the environment)
find_package(Qt5 COMPONENTS Core Gui Widgets Svg REQUIRED)

# If Qt5.6 or higher, also include svgwidgets
if(Qt5_VERSION VERSION_GREATER_EQUAL 5.6)
    find_package(Qt5 COMPONENTS SvgWidgets REQUIRED)
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable target
add_executable(qfi_example2)

# Set the include directories
target_include_directories(qfi_example2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add source files
set(SOURCES
    LayoutSquare.cpp # example/LayoutSquare.cpp
    MainWindow.cpp # example/MainWindow.cpp
    WidgetAI.cpp # example/WidgetAI.cpp
    WidgetALT.cpp # example/WidgetALT.cpp
    WidgetASI.cpp # example/WidgetASI.cpp
    WidgetEADI.cpp # example/WidgetEADI.cpp
    WidgetEHSI.cpp # example/WidgetEHSI.cpp
    WidgetHI.cpp # example/WidgetHI.cpp
    WidgetTC.cpp # example/WidgetTC.cpp
    WidgetVSI.cpp # example/WidgetVSI.cpp
    WidgetSix.cpp # example/WidgetSix.cpp
    main.cpp # example/main.cpp
)

# Add header files
set(HEADERS
    LayoutSquare.h # example/LayoutSquare.h
    MainWindow.h # example/MainWindow.h
    WidgetAI.h # example/WidgetAI.h
    WidgetALT.h # example/WidgetALT.h
    WidgetASI.h # example/WidgetASI.h
    WidgetEADI.h # example/WidgetEADI.h
    WidgetEHSI.h # example/WidgetEHSI.h
    WidgetHI.h # example/WidgetHI.h
    WidgetTC.h # example/WidgetTC.h
    WidgetVSI.h # example/WidgetVSI.h
    WidgetSix.h # example/WidgetSix.h
)

# Add UI forms
set(FORMS
    MainWindow.ui #example/MainWindow.ui
    WidgetAI.ui #example/WidgetAI.ui
    WidgetALT.ui #example/WidgetALT.ui
    WidgetASI.ui #example/WidgetASI.ui
    WidgetEADI.ui #example/WidgetEADI.ui
    WidgetEHSI.ui #example/WidgetEHSI.ui
    WidgetHI.ui #example/WidgetHI.ui
    WidgetTC.ui #example/WidgetTC.ui
    WidgetVSI.ui #example/WidgetVSI.ui
    WidgetSix.ui #example/WidgetSix.ui
)

# Add the source, headers, and UI files to the executable
target_sources(qfi_example2 PRIVATE ${SOURCES} ${HEADERS})

# Add the UI forms to the project
qt5_wrap_ui(UI_HEADERS ${FORMS})

# Link the UI headers with the project
target_sources(qfi_example2 PRIVATE ${UI_HEADERS})

# Link against the necessary Qt libraries
target_link_libraries(qfi_example2 PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Svg)
if (Qt5_VERSION VERSION_GREATER_EQUAL 5.6)
    target_link_libraries(qfi_example2 PRIVATE Qt5::SvgWidgets)
endif()

# Link against the qfi library
target_link_libraries(qfi_example2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libqfi.so)

# Define preprocessor definitions
target_compile_definitions(qfi_example2 PRIVATE QFI_DLL_IMPORTS QT_DEPRECATED_WARNINGS)

# Conditional compilation for Windows
if(WIN32)
    target_compile_definitions(qfi_example2 PRIVATE NOMINMAX WIN32 _WINDOWS _CRT_SECURE_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS _USE_MATH_DEFINES)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO")
endif()

# Conditional compilation for Linux
if(UNIX)
    target_compile_definitions(qfi_example2 PRIVATE _LINUX_)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

# Set output directory for the executable
set_target_properties(qfi_example2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
)
