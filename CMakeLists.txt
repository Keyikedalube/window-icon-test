cmake_minimum_required(VERSION 3.15)

project(window-icon-test)

# Check for gtkmm
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# Check for glib
pkg_check_modules(GLIB REQUIRED glib-2.0)

# Update submodules as needed
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
                message(STATUS "Submodule update")
                execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                RESULT_VARIABLE GIT_SUBMOD_RESULT)
                if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
                endif()
        endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/GCR_CMake/macros/GlibCompileResourcesSupport.cmake")
        message(FATAL_ERROR "The submodules were not downloaded!")
endif()

# Add GCR_CMake module for compiling ui and icon files
list(APPEND CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/GCR_CMake/macros)
include(GlibCompileResourcesSupport)

# Set the resources to bundle
set(RESOURCE_LIST
        window_content.glade
        synfig_icon.png)

compile_gresources(RESOURCE_FILE
	XML_OUT
	TYPE EMBED_C
	RESOURCES ${RESOURCE_LIST}
        PREFIX "/io/github/window-icon-test/")

add_custom_target(ALL DEPENDS ${RESOURCE_FILE})

set(SOURCES
	main.cpp)

# Configure warnings for GCC
if(CMAKE_COMPILER_IS_GNUCC)
	add_compile_options(
                -Wno-overlength-strings
                -Wno-implicit-fallthrough
                -Werror -Wall -Wextra -pedantic)
endif()

add_executable(window-icon-test ${SOURCES} ${RESOURCE_FILE})
target_link_libraries(window-icon-test ${GTKMM_LIBRARIES})

