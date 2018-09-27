
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

#include "string.hpp"

#include <string>


bool only_whitespace_characters( const std::string str ) {
    for ( unsigned int c = 0; c < str.length(); c++ ) {
        if ( str[c] != ' ' || str[c] != '\t' || str[c] != '\n' ) {
            return false;
        }
    }
    return true;
}


const std::string strip_whitespace_characters( const std::string str ) {
    std::string new_str;
    for ( unsigned int c = 0; c < str.length(); c++ ) {
        if ( str[c] != ' ' && str[c] != '\t' && str[c] != '\n' ) {
            new_str += str[c];
        }
    }
    return new_str;
}


const std::string strip_delimiter_characters( const std::string str ) {
    std::string new_str;
    for ( unsigned int c = 0; c < str.length(); c++ ) {
        if ( str[c] != '"' && str[c] != '{' && str[c] != '}' ) {
            new_str += str[c];
        }
    }
    if ( new_str[new_str.length()-1] == ',' ) {
        new_str.erase( new_str.length()-1 );
    }
    return new_str;
}


std::string escape_string( const std::string orig_str ) {
    std::string str = orig_str;
    int ae = str.find("ä");
    while ( ae > -1 ) {
        str.replace( ae, 2, "&auml;");
        ae = str.find("ä");
    }
    int oe = str.find("ö");
    while ( oe > -1 ) {
        str.replace( oe, 2, "&ouml;");
        oe = str.find("ö");
    }
    int ue = str.find("ü");
    while ( ue > -1 ) {
        str.replace( ue, 2, "&uuml;");
        ue = str.find("ü");
    }
    ae = str.find("Ä");
    while ( ae > -1 ) {
        str.replace( oe, 2, "&Auml;");
        ae = str.find("Ä");
    }
    oe = str.find("Ö");
    while ( oe > -1 ) {
        str.replace( oe, 2, "&Ouml;");
        oe = str.find("Ö");
    }
    ue = str.find("Ü");
    while ( ue > -1 ) {
        str.replace( ue, 2, "&Uuml;");
        ue = str.find("Ü");
    }
    int s = str.find("ß");
    while ( s > -1 ) {
        str.replace( s, 2, "&szlig;");
        s = str.find("ß");
    }

    return str;
}
