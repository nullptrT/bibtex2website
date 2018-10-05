
#
#  BibTeX2Website - A program and library that can generate an ordered website out of BibTeX files
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

project(bibtex2website LANGUAGES CXX)
set (VERBOSE 1)
set (bibtex2website_VERSION_MAJOR 1)
set (bibtex2website_VERSION_MINOR 1)
set (bibtex2website_VERSION_RELEASE 1)
set (bibtex2website_VERSION_PATCH "")
set (bibtex2website_VERSION "${bibtex2website_VERSION_MAJOR}.${bibtex2website_VERSION_MINOR}.${bibtex2website_VERSION_RELEASE}${bibtex2website_VERSION_PATCH}")
set (bibtex2website_VERSION "${bibtex2website_VERSION}")
add_definitions( -Dbibtex2website_VERSION="${bibtex2website_VERSION}" )


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
        message("-- Enabled doc_bibtex_to_website target for make")
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(doc_bibtex_to_website ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen")
    endif()
endif()

if( DESTDIR )
else()
    set( DESTDIR ${CMAKE_CURRENT_BINARY_DIR} )
endif()

set( BIBTEX_TO_WEBSITE_BIN_INSTALL_DIR ${DESTDIR}/bin )
set( BIBTEX_TO_WEBSITE_LIB_INSTALL_DIR ${DESTDIR}/lib )
set( BIBTEX_TO_WEBSITE_HEADER_INSTALL_DIR ${DESTDIR}/include/bibtex2html )

if( UNIX )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()


# Add sub-directories
add_subdirectory(3rdparty/liblogcpp)
include_directories(3rdparty/liblogcpp/src)
add_subdirectory(src)
