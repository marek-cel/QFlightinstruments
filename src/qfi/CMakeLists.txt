cmake_minimum_required(VERSION 3.14)

# Define the project name and version
project(qfi VERSION 1.0 LANGUAGES CXX)

# Find required packages (Qt5 or Qt6 based on the environment)
find_package(Qt5 COMPONENTS Widgets Svg REQUIRED)

# Create a library target
add_library(qfi SHARED)

# Set the include directories
target_include_directories(qfi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add source files
set(SOURCES
    qfi_Colors.cpp # qfi/qfi_Colors.cpp
    qfi_Fonts.cpp # qfi/qfi_Fonts.cpp
    qfi_EADI.cpp # qfi/qfi_EADI.cpp
    qfi_EHSI.cpp # qfi/qfi_EHSI.cpp
    qfi_AI.cpp # qfi/qfi_AI.cpp
    qfi_HI.cpp # qfi/qfi_HI.cpp
    qfi_VSI.cpp # qfi/qfi_VSI.cpp
    qfi_ASI.cpp # qfi/qfi_ASI.cpp
    qfi_ALT.cpp # qfi/qfi_ALT.cpp
    qfi_TC.cpp # qfi/qfi_TC.cpp
)

# Add header files
set(HEADERS
    qfi_defs.h # qfi/qfi_defs.h
    qfi_doxygen.h # qfi/qfi_doxygen.h
    qfi_Colors.h # qfi/qfi_Colors.h
    qfi_Fonts.h # qfi/qfi_Fonts.h
    qfi_EADI.h # qfi/qfi_EADI.h
    qfi_EHSI.h # qfi/qfi_EHSI.h
    qfi_AI.h # qfi/qfi_AI.h
    qfi_HI.h # qfi/qfi_HI.h
    qfi_VSI.h # qfi/qfi_VSI.h
    qfi_ASI.h # qfi/qfi_ASI.h
    qfi_ALT.h # qfi/qfi_ALT.h
    qfi_TC.h # qfi/qfi_TC.h
)

# Add the resource file
qt5_add_resources(RESOURCES qfi.qrc) # qfi/qfi.qrc

# Add sources, headers, and resources to the library
target_sources(qfi PRIVATE ${SOURCES} ${HEADERS} ${RESOURCES})

# Link against the necessary Qt libraries
target_link_libraries(qfi PRIVATE Qt5::Widgets Qt5::Svg)

# Define preprocessor definitions
target_compile_definitions(qfi PRIVATE QFI_DLL_EXPORTS QT_DEPRECATED_WARNINGS)

# Conditional compilation for Windows
if(WIN32)
    target_compile_definitions(qfi PRIVATE NOMINMAX WIN32 _WINDOWS _CRT_SECURE_NO_DEPRECATE _SCL_SECURE_NO_WARNINGS _USE_MATH_DEFINES)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO")
endif()

# Conditional compilation for Linux
if(UNIX)
    target_compile_definitions(qfi PRIVATE _LINUX_)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

# Set output directory for the shared library
set_target_properties(qfi PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)
