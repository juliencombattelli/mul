cmake_minimum_required(VERSION 3.5)
project(MUL)

set(CORE_PATH core)
set(MODULE_PATH modules)

# Build the core library
add_subdirectory(${CORE_PATH})

# Define all module options
option(WITH_MODULE_SERIAL "Provide cross-platform serial communication library" ON)


# Add the serial library ?
if(WITH_MODULE_SERIAL)
#    include_directories("${PROJECT_SOURCE_DIR}/MathFunctions")
    add_subdirectory(${MODULE_PATH}/serial)
endif(WITH_MODULE_SERIAL)

# Uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)
endif()
