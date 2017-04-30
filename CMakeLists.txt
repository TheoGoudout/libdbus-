cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Define parameters
option(BUILD_SHARED_LIBRARY "Whether the shared library should be built." ON)
option(BUILD_STATIC_LIBRARY "Whether the static library should be built." OFF)

SET(LIBDBUS_VERSION 0.1)

# Compile plugin
add_subdirectory(plugin/ ${CMAKE_CURRENT_SOURCE_DIR}/plugin/build/)

# Compile examples if requested
option(EXAMPLES "Compile and install examples." ON)
if(EXAMPLES AND libdbusplugin_BINARY_DIR)
    add_subdirectory(examples/ ${CMAKE_CURRENT_SOURCE_DIR}/examples/build/)
endif()
