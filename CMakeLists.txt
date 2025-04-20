cmake_minimum_required(VERSION 3.22)

################################################################################

set(QFI_VERSION_MAJOR 1)
set(QFI_VERSION_MINOR 0)
set(QFI_VERSION_PATCH 0)
set(QFI_VERSION_STRING
    ${QFI_VERSION_MAJOR}.${QFI_VERSION_MINOR}.${QFI_VERSION_PATCH}
)

project(QFlightInstruments VERSION ${QFI_VERSION_STRING})

################################################################################

include(GNUInstallDirs)

################################################################################

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME ${QFI_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR ${QFI_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${QFI_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${QFI_VERSION_PATCH})

set(CPACK_GENERATOR "ZIP")

include(CPack)

################################################################################

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

################################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################

if(UNIX)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_definitions(-D_LINUX_)
    endif()
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_WINDOWS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_USE_MATH_DEFINES)
endif()

################################################################################

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -std=c++20")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG   "-Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
    if (MSVC_VERSION GREATER_EQUAL "1930")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++20" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++20")
        endif()
    endif()
endif()

################################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Svg)
# include_directories(${Qt5

################################################################################

include_directories(.)

################################################################################

add_subdirectory(qfi)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
