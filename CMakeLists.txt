
#
#  BibTeX2WebsiteGenerator - A program that can generate an ordered website out of BibTeX files
#  Copyright (C) 2018 Sebastian Lau <lauseb644@gmail.com>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.0)

set( QT_LIB_PATH "C:\\lib\\Qt" )
set( QT_VERSION "5.10.1" )

project(website_generator LANGUAGES C CXX)
set (VERBOSE 1)
set (website_generator_VERSION_MAJOR 1)
set (website_generator_VERSION_MINOR 0)
set (website_generator_VERSION_RELEASE 0)
set (website_generator_VERSION_PATCH "")
set (website_generator_VERSION "${website_generator_VERSION_MAJOR}.${website_generator_VERSION_MINOR}.${website_generator_VERSION_RELEASE}${website_generator_VERSION_PATCH}")
set (website_generator_VERSION "${website_generator_VERSION}")
add_definitions( -Dwebsite_generator_VERSION="${website_generator_VERSION}" )


if( NOT CMAKE_BUILD_TYPE )
	set(CMAKE_BUILD_TYPE "Debug")
endif()
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if( WIN32 )
	set (CMAKE_PREFIX_PATH "${QT_LIB_PATH}\\${QT_VERSION}\\msvc2017_64\\")
	set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_SOURCE_DIR} )
endif()

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
	add_definitions( -DBUILD_TYPE=1 )
else()
	add_definitions( -DBUILD_TYPE=2 )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
if( WIN32 )
  include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
	add_compile_options( "/std:c++17" )
else()
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC" )
endif()
if( UNIX )
	SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++" )
	add_definitions( "-lstdc++fs" )
endif()

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
set(BUILD_STATIC_LIBRARIES ON)

if( UNIX )
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        message("-- Enabled doc_website_generator target for make")
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(doc_website_generator ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen")
    endif()
endif()


if( UNIX )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()


# Add sub-directories
add_subdirectory(3rdparty/liblogcpp)
include_directories(3rdparty/liblogcpp/src)
add_subdirectory(src)