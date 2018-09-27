
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

include_directories(.)

file(GLOB WEBSITE_GENERATOR_CORE_SRC *.cpp)

add_library( website_generator_core ${WEBSITE_GENERATOR_CORE_SRC} )
target_link_libraries( website_generator_core logcpp )
if ( UNIX )
    find_package(Threads)
    target_link_libraries( website_generator_core  ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} stdc++fs )
endif( UNIX )
