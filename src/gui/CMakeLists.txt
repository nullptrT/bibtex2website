
#  
#  BibTeX2WebsiteGenerator - A program and library that can generate an ordered website out of BibTeX files
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

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

include_directories( ${Qt5Core_INCLUDE_DIRS}
                     ${Qt5Widgets_INCLUDE_DIRS}
                     ${Qt5Gui_INCLUDE_DIRS} )

add_library( bibtex2website_gui mainwindow.cpp )
target_link_libraries( bibtex2website_gui bibtex2html logcpp Qt5::Core Qt5::Widgets Qt5::Gui )

if ( UNIX )
    add_executable( BibTeX2WebsiteGUI main.cpp )
else()
    add_executable( BibTeX2WebsiteGUI WIN32 main.cpp )
endif()
target_link_libraries( BibTeX2WebsiteGUI bibtex2html bibtex2website_gui logcpp Qt5::Core )
