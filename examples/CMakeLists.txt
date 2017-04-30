cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Define project
project(examples VERSION ${LIBDBUS_VERSION} LANGUAGES CXX)

SET(
    PLUGIN_PATH
    "${dbus_attributes_plugin_BINARY_DIR}/libdbusplugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)
MESSAGE(STATUS ${PLUGIN_PATH})

# Set header files of the project
set(DBUS_EXAMPLES
    server
    client
)

# For each example to create
foreach(DBUS_EXAMPLE ${DBUS_EXAMPLES})

    # Set source files of library
    add_executable(
        dbus_${DBUS_EXAMPLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/${DBUS_EXAMPLE}.cpp
    )

    # Set include directory of library
    include_directories(include)

    # Add dependency to XML library
    if(TARGET xml)
        add_dependencies(dbus_${DBUS_EXAMPLE} xml)
    endif()

    # Set compilation flags
    set(CMAKE_CXX_FLAGS_DEFAULT "-O2 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wno-unused-function -fPIC -fno-rtti -fplugin=\"${PLUGIN_PATH}\"" )

    # Set C++11 flag
    target_compile_features(dbus_${DBUS_EXAMPLE} PRIVATE cxx_nullptr)

    # Link against XML library
    target_link_libraries(dbus_${DBUS_EXAMPLE})


    # Install examples
    install(TARGETS dbus_${DBUS_EXAMPLE}
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    )

endforeach()
