
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

#include "bibtex.hpp"
#include "string.hpp"
#include "log.hpp"

#include <fstream>
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;


BibTeXItem::BibTeXItem()
    :   Dict< std::string >()
{
    // type, author, title, subtitle, url, publisher
    std::string str_empty;
    this->add_item( "type", str_empty );
    this->add_item( "author", str_empty );
    this->add_item( "booktitle", str_empty );
    this->add_item( "title", str_empty );
    this->add_item( "subtitle", str_empty );
    this->add_item( "publisher", str_empty );
    this->add_item( "url", str_empty );
    this->add_item( "volume", str_empty );
    this->add_item( "series", str_empty );
    this->add_item( "school", str_empty );
    this->add_item( "organization", str_empty );
    this->add_item( "year", str_empty );
    this->add_item( "journal", str_empty );
    this->add_item( "number", str_empty );
    this->add_item( "pages", str_empty );
    this->add_item( "description", str_empty );
}


BibTeXItem* BibTeXItem::parse( const std::vector< std::string > bibtex_text ) {
    BibTeXItem* item = new BibTeXItem();
    
    for ( unsigned int i = 0; i < bibtex_text.size(); i++ ) {
        const std::string text = bibtex_text.at( i );
        if ( text.compare(0, 1, "@") == 0 ) {
            size_t type_end = text.find("{");
            std::string type = text.substr(1, type_end-1);
            item->get_item( "type" )->second = type;
        } else {
            std::string no_ws = strip_whitespace_characters( text );
            size_t def_end = no_ws.find("=");
            std::string def = no_ws.substr(0, def_end);
            size_t val_start = text.find("=");
            std::string val = text.substr(val_start+1, std::string::npos);
            
            val = escape_string( val );

            if ( item->get_item( def ) == 0 ) {
                stdlog << logcpp::warning << "Could not find item entry of type '" << def << "'...Skipping." << logcpp::endrec;
            } else {
                val = strip_delimiter_characters( val );
                item->get_item( def )->second = val;
            }
        }
    }
    
    return item;
}


BibTeXFile::BibTeXFile(const std::string file)
    :   m_file( file )
    ,   m_items()
{}


const std::vector< BibTeXItem* > BibTeXFile::get_items() const {
    return m_items;
}


bool BibTeXFile::parse_bibtex_file() {
    std::ifstream file( m_file );
    if ( !file.good() ) {
        return false;
    }
    
    std::string line;
    std::vector< std::string > lines;
    while ( std::getline( file, line ) ) {
        lines.push_back( line );
    }
    
    std::vector< std::string > bibtex_item_text;
    this->m_items.clear();
    for ( unsigned int i = 0; i < lines.size(); i++ ) {
        if ( only_whitespace_characters( lines.at( i ) ) ) {
            continue;
        } else if ( lines.at( i ).compare( 0, 1, "@" ) == 0 ) {
            bibtex_item_text.clear();
        }
        
        if ( lines.at( i ).compare( 0, 1, "}" ) != 0 ) {
            bibtex_item_text.push_back( lines.at( i ) );
        } else {
            BibTeXItem* bibtex_item = BibTeXItem::parse( bibtex_item_text );
            this->m_items.push_back( bibtex_item );
        } 
    }
    
    return true;
}


BibTeX::Exception::Exception( const std::string msg )
    :   std::exception()
    ,   m_what( msg )
{}


const char* BibTeX::Exception::what() const noexcept {
    return this->m_what.c_str();
}


BibTeX::BibTeX()
    :   m_files()
    ,   m_items()
{}


BibTeX::YearList* BibTeX::by_year() const {    
    BibTeX::YearList* years = new BibTeX::YearList();
    
    for ( BibTeX::TypeList::const_iterator cIt = this->m_items.begin()
        ; cIt != this->m_items.end()
        ; ++cIt
    ) {
        std::string type = cIt->first;
        std::vector< BibTeXItem* >* items = cIt->second;
        
        for ( BibTeXItem* item : *items ) {
            std::string year_str = item->get_item( "year" )->second;
            const unsigned int year = std::stoi( year_str );
            
            BibTeX::TypeList* list_of_year = 0;
            try {
                list_of_year = years->at( year );
            } catch ( std::out_of_range& oor ) {
                list_of_year = new BibTeX::TypeList();
                years->insert( std::make_pair( year, list_of_year ) );
            }
            
            std::string type = item->get_item( "type" )->second;
            ItemList* list_of_type = 0;
            try {
                list_of_type = list_of_year->at( type );
            } catch ( std::out_of_range& oor ) {
                list_of_type = new ItemList();
                list_of_year->insert( std::make_pair( type, list_of_type ) );
            }
            
            list_of_type->push_back( item );
        }
    }
    
    return years;
}


bool BibTeX::parse_bibtex_files(const std::string path) {
    this->m_files.clear();
    
    stdlog << logcpp::verbose;
    
    if ( !fs::exists( path ) ) {
        throw BibTeX::Exception("Path '" + path + "' does not exist.");
    }
    
    std::vector< fs::path > paths;
    paths.push_back( fs::path(path) );
    for ( auto& p : fs::directory_iterator( path ) ) {
        if ( fs::is_directory( p.path() ) ) {
            paths.push_back( p.path() );
        }
    }
    
    stdlog << "  -> Globbing BibTeX files at '" << path << "'..." << logcpp::endrec;
    for ( fs::path current_path : paths ) {
        for ( auto& p : fs::directory_iterator( current_path ) ) {
            if ( p.path().string().compare(p.path().string().length()-4, p.path().string().length()-1, ".bib") == 0 ) {
                this->m_files.push_back( p.path().string() );
                stdlog << "    -> Adding '" << p.path().string() << "'" << logcpp::endrec;
            }
        }
    }
    
    stdlog << "  -> Parsing BibTeX files..." << logcpp::endrec;
    for ( unsigned int f = 0; f < this->m_files.size(); f++ ) {
        stdlog << logcpp::verbose << "    -> Parsing '" << this->m_files.at( f ) << "'..." << logcpp::endrec;
        BibTeXFile* file = new BibTeXFile( this->m_files.at( f ) );
        file->parse_bibtex_file();
        for ( unsigned int i = 0; i < file->get_items().size(); i++ ) {
            BibTeXItem* item = file->get_items().at( i );
            try {
                std::vector< BibTeXItem* >* items_of_type = this->m_items.at( item->get_item("type")->first );
                items_of_type->push_back( item );
            } catch ( std::out_of_range& oor ) {
                std::vector< BibTeXItem* >* items_of_type = new std::vector< BibTeXItem* >();
                items_of_type->push_back( item );
                
                this->m_items.insert( std::make_pair(item->get_item("type")->first, items_of_type) );
            }
        }
    }
    
    return true;
}


