
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

include_directories(.)

file( GLOB BIBTEX_TO_WEBSITE_GENERATOR_HEADERS *.hpp )
install(FILES ${BIBTEX_TO_WEBSITE_GENERATOR_HEADERS} DESTINATION ${BIBTEX_TO_HTML_HEADER_INSTALL_DIR}/ )

file( GLOB BIBTEX_TO_WEBSITE_GENERATOR_CORE_SRC *.cpp )

add_library( bibtex2html ${BIBTEX_TO_WEBSITE_GENERATOR_CORE_SRC} ../config.cpp )
target_link_libraries( bibtex2html logcpp )
if ( UNIX )
    find_package(Threads)
    target_link_libraries( bibtex2html  ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} stdc++fs )
    install( TARGETS bibtex2html DESTINATION ${BIBTEX_TO_HTML_LIB_INSTALL_DIR}/ )
endif( UNIX )
