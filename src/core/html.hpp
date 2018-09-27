
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

#pragma once

#include <map>
#include <string>
#include <vector>


class BibTeX;
class HTML_File;


/**
 * @brief Abstract HTML class and top-level static function
 */
class HTML {
protected:
    /**
     * @brief Protected constructor
     */
    HTML();
public:
    /**
     * @brief Conversion to html that is to be implemented by every derived class
     */
    virtual const std::string to_html() const = 0;
    
    /**
     * @brief Generate a HTML_File from a fully parsed BibTeX object
     * @param bibtex A parsed BibTeX object
     * @returns A valid HTML_File object
     * @note Should be executed first before handling html strings
     */
    static HTML_File* generate( const BibTeX* bibtex );
    
    /**
     * @brief HTML exception
     */
    class Exception
        :   public std::exception
    {
        /**
         * @brief The message the exception has
         */
        const std::string m_what;
    public:
        /**
         * @brief Constructor
         * @param msg The message the exception contains
         */
        Exception( const std::string msg );
        
        /**
         * @brief Get the message of this exception
         * @returns The message of this exception
         */
        const char* what() const noexcept override;
    };
};


class BibTeXItem;


/**
 * @brief A class that contains an BibTeXItem and can convert it to HTML
 */
class HTML_BibTeXItem
    :   public HTML
{
protected:
    /**
     * @brief The BibTeXItem of this class
     */
    const BibTeXItem* m_bibtex;
public:
    /**
     * @brief Constructor
     * @param bibtex A non-null BibTeXItem
     * @throws HTML::Exception If (bibtex == 0)
     */
    HTML_BibTeXItem( const BibTeXItem* bibtex );
    
    /**
     * @brief Get the BibTeXItem
     * @returns The BibTeXItem
     */
    const BibTeXItem* item() const;
    
    /**
     * @brief Convert the BibTeXItem to HTML
     * @returns The HTML string of this HTML_BibTeXItem
     */
    virtual const std::string to_html() const override;
};


/**
 * @brief A class that collects HTML_BibTeXItem for a specific year
 */
class HTML_YearList
    :   public HTML
{
protected:
    /**
     * @brief The number of the year, this class collects
     */
    const unsigned int m_year;
    /**
     * @brief All collected HTML_BibTeXItem
     */
    std::vector< HTML_BibTeXItem* > m_bibtex;
public:
    /**
     * @brief Constructor
     * @param year The year this class collects
     */
    HTML_YearList( const unsigned int year );
    
    /**
     * @brief Get the year
     * @returns The year, this class collects
     */
    const unsigned int year() const;
    
    /**
     * @brief Append another BibTeXItem to this year collection class
     * @param bibtex The BibTeXItem to append to this year collection
     * @note If (bibtex == 0), nothing is inserted
     */
    void operator+=( const BibTeXItem* bibtex );
    
    /**
     * @brief Convert all BibTeXItem of this year to HTML, ordered by type
     * @returns The HTML string of this HTML_YearList
     * @note There should be BibTeXItem appended already for an useful result
     */
    virtual const std::string to_html() const override;
};


/**
 * @brief A class that can collect and order BibTeXItem, convert them to HTML and write it to a file
 */
class HTML_File {
protected:
    /**
     * @brief A map that contains HTML_YearList ordered by year
     */
    std::map< const unsigned int, HTML_YearList* > m_years;
    
    /**
     * @brief Create a HTML table of contents that references the years
     * @note There should be BibTeXItem appended before
     */
    virtual const std::string to_html_tableofcontents() const;
public:
    /**
     * @brief Constructor
     */
    HTML_File();
    
    /**
     * @brief Append another BibTeXItem to this class
     * @param bibtex The BibTeXItem to append
     * @note If (bibtex == 0), nothing is inserted
     */
    void operator+=( const BibTeXItem* bibtex );
    
    /**
     * @brief Convert everything to HTML
     * @param pagetitle The title of the page
     * @returns The HTML string of this HTML_File
     * @note There should be BibTeXItem appended already for an useful result
     */
    virtual const std::string to_html( const std::string pagetitle ) const;
    
    /**
     * @brief Write the content of this HTML_File to a file
     * @param path Path of the file to write to
     * @param pagetitle The title of the page
     * @note There should be BibTeXItem appended already for an useful result
     */
    void to_file( const std::string path, const std::string pagetitle ) const;
};
