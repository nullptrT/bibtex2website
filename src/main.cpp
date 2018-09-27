/*
 * BibTeX2WebsiteGenerator - A program that can generate an ordered website out of BibTeX files
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
    std::cout << "Usage: bibtex2website_generator <PATH_TO_FILES> <OUTPUT> <PAGE_TITLE> [<COLOR_CODE>] [--verbose]" << std::endl;
}



int main(int argc, char *argv[])
{   
    stdlog.enable_print_severity(false);
    stdlog << logcpp::warning;
#ifdef __unix__
    stdlog << logcpp::sty_bold;
#endif
    stdlog << "BibTeX2WebsiteGenerator v" << website_generator_VERSION << " (https://git.0ptr.de/nullptr_t/bibtex2website)";
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
    
    stdlog << logcpp::normal << "[WebsiteGenerator/BibTeX] - Parsing BibTeX files..." << logcpp::endrec;
    BibTeX* tex = new BibTeX();
    try {
        tex->parse_bibtex_files( argv[1] );
    } catch ( BibTeX::Exception& texe ) {
        stdlog << logcpp::critical << "Failed to parse BibTeX: " << texe.what() << logcpp::endrec;
    }
    
    stdlog << logcpp::normal << "[WebsiteGenerator/HTML] - Generating HTML..." << logcpp::endrec;
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
