
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

#include "html.hpp"

#include "bibtex.hpp"
#include "../config.hpp"
#include "log.hpp"

#include <cctype>
#include <cstdio>
#include <fstream>
#include <sstream>


HTML::HTML()
{}


HTML_File* HTML::generate( const BibTeX* bibtex ) {
    HTML_File* html_file = new HTML_File();
    BibTeX::YearList* bibtex_by_year = bibtex->by_year();
    
    for ( BibTeX::YearList::const_iterator yIt = bibtex_by_year->begin()
        ; yIt != bibtex_by_year->end()
        ; ++yIt
    ) {
        BibTeX::TypeList* bibtex_year_by_type = yIt->second;
        
        for ( BibTeX::TypeList::const_iterator tIt = bibtex_year_by_type->begin()
            ; tIt != bibtex_year_by_type->end()
            ; ++tIt
        ) {
            BibTeX::ItemList* bibtex_items = tIt->second;
            
            for ( BibTeXItem* item : *bibtex_items ) {
                *html_file += item;
            }
            
        }
    }
    
    return html_file;
}


HTML::Exception::Exception( const std::string msg )
    :   std::exception()
    ,   m_what( msg )
{}


const char* HTML::Exception::what() const noexcept {
    return this->m_what.c_str();
}


HTML_BibTeXItem::HTML_BibTeXItem( const BibTeXItem* bibtex )
    :   HTML()
    ,   m_bibtex( bibtex )
{
    if ( bibtex == 0 ) {
        throw HTML::Exception("BibTeXItem is a nullptr.");
    }
}


const BibTeXItem* HTML_BibTeXItem::item() const {
    return this->m_bibtex;
}


const std::string HTML_BibTeXItem::to_html() const {
    std::stringstream html;
    
    std::string year = this->m_bibtex->get_item( "year" )->second;
    std::string author = this->m_bibtex->get_item( "author" )->second;
    std::string url = this->m_bibtex->get_item( "url" )->second;
    std::string booktitle = this->m_bibtex->get_item( "booktitle" )->second;
    std::string title = this->m_bibtex->get_item( "title" )->second;
    std::string subtitle = this->m_bibtex->get_item( "subtitle" )->second;
    std::string publisher = this->m_bibtex->get_item( "publisher" )->second;
    std::string volume = this->m_bibtex->get_item( "volume" )->second;
    std::string series = this->m_bibtex->get_item( "series" )->second;
    std::string school = this->m_bibtex->get_item( "school" )->second;
    std::string organization = this->m_bibtex->get_item( "organization" )->second;
    std::string journal = this->m_bibtex->get_item( "journal" )->second;
    std::string number = this->m_bibtex->get_item( "number" )->second;
    std::string description = this->m_bibtex->get_item( "description" )->second;
    
    html << "<li>";
    
    html << "<span color: " << program_config::color_titles << ";>" << author << "</span><br>\n";
    
    if ( url.length() > 0 ) {
        html << "<a href=\"" << url << "\"><span style=\"text-decoration: underline;\">";
    }
    if ( booktitle.length() > 0 && title.length() > 0 ) {
        html << "<b>" << booktitle << " - " << title << "</b>";
    } else if ( booktitle.length() > 0 ) {
        html << "<b>" << booktitle << "</b>";
    } else if ( title.length() > 0 ) {
        html << "<b>" << title << "</b>";
    }
    if ( url.length() > 0 ) {
        html << "</span></a>";
    }
    html << "<br>\n";
    
    if ( subtitle.length() > 0 ) {
        html << "<em>" << subtitle << "</em><br>\n";
    }
    
    if ( publisher.length() > 0 ) {
        html << publisher << ", ";
    }
    
    if ( organization.length() > 0 ) {
        html << organization << ", ";
    }
    
    if ( school.length() > 0 ) {
        html << school << ", ";
    }
    
    if ( journal.length() > 0 ) {
        html << journal << ", ";
    }
    
    if ( series.length() > 0 ) {
        html << series << ", ";
    }
    
    if ( volume.length() > 0 ) {
        html << volume << ", ";
    }
    
    if ( number.length() > 0 ) {
        html << number << ", ";
    }
    
    html << year;
    
    if ( description.length() > 0 ) {
        html << "<br>\n<em>" << description << "</em>\n";
    }
    
    html << "<br></li>";
    
    return html.str();
}


HTML_YearList::HTML_YearList( const unsigned int year )
    :   m_year( year )
    ,   m_bibtex()
{}


const unsigned int HTML_YearList::year() const {
    return m_year;
}


void HTML_YearList::operator+=( const BibTeXItem* bibtex ) {
    if ( bibtex != 0 ) {
        HTML_BibTeXItem* html_bibtex = new HTML_BibTeXItem( bibtex );
        this->m_bibtex.push_back( html_bibtex );
    }
}


const std::string HTML_YearList::to_html() const {
    std::map< std::string, std::stringstream* > types;
    
    for ( HTML_BibTeXItem* item : this->m_bibtex ) {
        std::string type = item->item()->get_item( "type" )->second;
        
        std::stringstream* html = 0;
        try {
            html = types.at( type );
        } catch ( std::out_of_range& oore ) {
            html = new std::stringstream();
            types.insert( std::make_pair( type, html ) );
        }
        
        *html << item->to_html() << "\n\n";
    }
    
    
    std::stringstream html;
    
    html << "<p><a id=\"" << this->m_year << "\" name=\"" << this->m_year << "\"></a></p>\n";
    html << "<p>&nbsp;</p>\n";
    html << "<h3><strong><span style=\"color: " << program_config::color_titles << ";\"><span class=\"c1\"><span class=\"c1\">\n";
    html << this->m_year << "</span></span></span></strong></h3>\n";
    html << "<p>&nbsp;</p>\n";
    
    for ( std::map< std::string, std::stringstream* >::iterator tIt = types.begin()
        ; tIt != types.end()
        ; ++tIt
    ) {
        std::string type = tIt->first;
        
        type[0] = std::toupper(type[0]);
        
        html << "<h3 style=\"color: " << program_config::color_titles << "\">" << type << "</h3>\n";
        html << "<p></p>\n";
        html << "<ul>\n";
        html << "<ul>\n\n";
        
        html << tIt->second->str();
        
        html << "</ul>\n";
        html << "</ul>\n\n";
    }
    
    return html.str();
}


const std::string HTML_File::to_html_tableofcontents() const {
    if ( this->m_years.size() == 0 ) {
        throw HTML::Exception("No BibTeX added to generate HTML.");
    }
    
    std::stringstream html;
    
    html << "<table style=\"background-color: #ffffff; border-color: #ffffff;";
    html << " margin-left: auto; margin-right: auto;\" align=\"left\" width=\"100%\" class";
    html << "=\"c2\">\n";
    html << "<tbody>\n";
    html << "<tr style=\"text-align: center;\">\n";
    
    unsigned int tableofcontent_items = 0;
    for ( std::map< const unsigned int, HTML_YearList* >::const_reverse_iterator yIt = this->m_years.rbegin()
        ; yIt != this->m_years.rend()
        ; ++yIt, ++tableofcontent_items
    ) {
        if ( tableofcontent_items == 18 ) {
            break;
        }
        
        html << "<td scope=\"col\" style=\"width: 5%; text-align: center;\" width=\"6%\" valign=\"middle\">\n";
        html << "<h3><a href=\"#" << yIt->first << "\" title=\"" << yIt->first << "\"><span style=\"color: #000000;\"><strong>" << yIt->first << "</strong></span></a></h3>\n";
        html << "</td>\n";
    }
    
    html << "</tr>\n";
    html << "</tbody>\n";
    html << "</table>\n";
    html << "<p>&nbsp;</p>\n";
    html << "<hr>\n";
    
    return html.str();
}


HTML_File::HTML_File()
    :   m_years()
{}


void HTML_File::operator+=( const BibTeXItem* bibtex ) {
    if ( bibtex == 0 ) {
        return;
    }
    
    unsigned int year = 0;
    try {
        year = std::stoi( bibtex->get_item( "year" )->second );
    } catch ( std::exception& e ) {
        stdlog << logcpp::verbose << "BibTeXItem without year..." << logcpp::endrec;
    }
    
    HTML_YearList* year_list = 0;
    try {
        year_list = this->m_years.at( year );
    } catch ( std::out_of_range& oore ) {
        year_list = new HTML_YearList( year );
        this->m_years.insert( std::make_pair( year, year_list ) );
    }
    
    *year_list += bibtex;
}


const std::string HTML_File::to_html( const std::string pagetitle ) const {
    std::stringstream html;
    
    html << "<a id=\"inhalt-sprungmarke\"></a>\n";
    html << "<h2 class=\"rubriktitel\">" << pagetitle << "</h2>\n";
    html << "<div class=\"aktuelles_meldung\">\n";
    html << "<p>&nbsp;</p>\n";
    
    html << this->to_html_tableofcontents() << "\n\n";
    
    for ( std::map< const unsigned int, HTML_YearList* >::const_reverse_iterator yIt = this->m_years.rbegin()
        ; yIt != this->m_years.rend()
        ; ++yIt
    ) {
        HTML_YearList* html_year = yIt->second;
        html << html_year->to_html() << "\n\n";
    }
    
    html << "</div>\n";
    html << "</div>\n";
    
    return html.str();
}


void HTML_File::to_file( const std::string path, const std::string pagetitle ) const {
    std::ofstream file( path );
    file << this->to_html( pagetitle );
    file.close();
}



