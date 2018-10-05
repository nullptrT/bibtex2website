/*
 * BibTeX2Website - A program and library that can generate an ordered website out of BibTeX files
 * Copyright (C) 2018 Sebastian Lau <lauseb644@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "config.hpp"

#ifdef _WINDOWS
#include "windows.h"
#endif

#include "bibtex.hpp"
#include "html.hpp"

#include "log.hpp"
#include "color_feature.hpp"


void help() {
    std::cout << "Usage: bibtex2website <PATH_TO_FILES> <OUTPUT> <PAGE_TITLE> [<COLOR_CODE>] [--verbose]" << std::endl;
    std::cout << std::endl;
    std::cout << "\tPATH_TO_FILES\tThe path to the top-level directory, where all BibTeX files are located." << std::endl;
    std::cout << "\t\t\tThe maximum level of directories is two, so you can create subfolders that order by month or category." << std::endl;
    std::cout << "\tOUTPUT\t\tThe path to the html file to write the html output to." << std::endl;
    std::cout << "\tPAGE_TITLE\tThe title of the website." << std::endl;
    std::cout << "\tCOLOR_CODE\tBy default, a green is chosen for the titles. Optionally you can define an own color code like #ffffff here." << std::endl;
    std::cout << std::endl;
    std::cout << "\t--verbose\tGet more output about what the program does." << std::endl;
    std::cout << std::endl;
}



int main(int argc, char *argv[])
{   
    stdlog.enable_print_severity(false);
    stdlog << logcpp::warning;
#ifdef __unix__
    stdlog << logcpp::sty_bold;
#endif
    stdlog << "BibTeX2Website v" << bibtex2website_VERSION << " (https://git.0ptr.de/nullptr_t/bibtex2website)";
#ifdef __unix__
    stdlog << logcpp::ctl_reset_all;
#endif
    stdlog << logcpp::normal << logcpp::endrec;
    stdlog.enable_print_severity();
    
    if ( argc < 4 ) {
        help();
        if ( std::string(argv[1]).compare("--help") == 0
          || std::string(argv[1]).compare("-h") == 0
        ) {
            exit(0);
        } else {
            exit(1);
        }
    } 
    
    if ( std::string(argv[argc-1]).compare( 0, 1, "#" ) == 0 ) {
        program_config::color_titles = std::string(argv[argc-1]);
    } else if ( std::string(argv[argc-2]).compare( 0, 1, "#" ) == 0 ) {
        program_config::color_titles = std::string(argv[argc-2]);
    }
    
    if ( std::string(argv[argc-1]).compare("--verbose") == 0 ) {
        stdlog.set_max_severity_level( logcpp::verbose );
    } else {
        stdlog.set_max_severity_level( logcpp::normal );
    }
    
    stdlog.set_critical_log_function(&std::abort);
    
    stdlog << logcpp::normal << "[BibTeX2Website/BibTeX] - Parsing BibTeX files..." << logcpp::endrec;
    BibTeX* tex = new BibTeX();
    try {
        tex->parse_bibtex_files( argv[1] );
    } catch ( BibTeX::Exception& texe ) {
        stdlog << logcpp::critical << "Failed to parse BibTeX: " << texe.what() << logcpp::endrec;
    }
    
    stdlog << logcpp::normal << "[BibTeX2Website/HTML] - Generating HTML..." << logcpp::endrec;
    try {
        HTML_File* html = HTML::generate( tex );
        html->to_file( argv[2], argv[3] );
    } catch ( HTML::Exception& htmle ) {
        stdlog << logcpp::critical << "Failed to generate HTML: " << htmle.what() << logcpp::endrec;
    } catch ( std::exception& e ) {
        stdlog << logcpp::critical << "Failed to write HTML: " << e.what() << logcpp::endrec;
    }
    
    exit(0);
}
