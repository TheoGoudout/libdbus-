cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Define parameters
option(BUILD_SHARED_LIBRARY "Whether the shared library should be built." ON)
option(BUILD_STATIC_LIBRARY "Whether the static library should be built." OFF)

# Define project
project(dbus_attributes_plugin VERSION ${LIBDBUS_VERSION} LANGUAGES CXX)

SET(
    PLUGIN_PATH
    "${dbus_attributes_plugin_BINARY_DIR}/libdbusplugin${CMAKE_SHARED_LIBRARY_SUFFIX}.${LIBDBUS_VERSION}"
)

# Set source files of the project
set(BDUS_PLUGIN_SOURCE_FILES
    src/plugin.cpp
)

# Set header files of the project
set(DBUS_PLUGIN_HEADER_FILES
)

execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=plugin
    OUTPUT_VARIABLE CMAKE_INSTALL_PREFIX
    ERROR_VARIABLE CMAKE_INSTALL_PREFIX_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (CMAKE_INSTALL_PREFIX_ERROR OR CMAKE_INSTALL_PREFIX STREQUAL "plugin")
    error("Unable to find include folder for GCC plugin API")
endif()

# Set include directory of library
include_directories(include)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

# Set compilation flags
set(CMAKE_CXX_FLAGS_DEFAULT "-O2 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
set(CMAKE_CXX_FLAGS "-Wall -Werror -fno-rtti" )

add_definitions("-DPLUGIN_VERSION=\"${LIBDBUS_VERSION}\"")

# Add source files to library
add_library(dbus_attributes SHARED ${BDUS_PLUGIN_SOURCE_FILES})

# Set C++11 flag
target_compile_features(dbus_attributes PRIVATE cxx_nullptr)

# Set targets properties
set_target_properties(dbus_attributes PROPERTIES
    VERSION ${dbus_attributes_plugin_VERSION}
    SOVERSION ${dbus_attributes_plugin_VERSION}
)

# Install library
install(TARGETS dbus_attributes
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
)

# Install headers
install(FILES ${DBUS_PLUGIN_HEADER_FILES}
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/xml/${dbus_attributes_VERSION}"
)
