
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

include_directories( core )
add_subdirectory( core )

if ( ENABLE_QT_GUI )
    include_directories( gui )
    add_subdirectory( gui )
endif()

if ( UNIX )
    add_executable( bibtex2website_generator main.cpp )
else()
    add_executable( bibtex2website_generator WIN32 main.cpp )
endif()
set_target_properties( bibtex2website_generator PROPERTIES LINK_FLAGS "-static" )
target_link_libraries( bibtex2website_generator website_generator_core logcpp )

install_targets( ${DESTDIR}/bin bibtex2website_generator )
