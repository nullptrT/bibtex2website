
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

#include "dict.hpp"

#include <map>


/**
 * @brief A BibTeX entry
 */
class BibTeXItem
    :   public Dict< std::string >
{
public:
    /**
     * @brief Constructor
     * @note Constructs the dict elements "type", "author", "booktitle", "title", "subtitle", "publisher", "url", "volume", "series", "school", "organization", "year", "journal", "number", "pages" and "description" with empty strings
     */
    BibTeXItem();
    
    /**
     * @brief Parse one BibTeX entry to an BibTeX item
     * @param bibtex_text The text of the BibTeX entry by lines
     * @returns A newly constructed BibTeXItem
     */
    static BibTeXItem* parse( const std::vector< std::string > bibtex_text );
};


/**
 * @brief A BibTeX file that can contain of N entries
 */
class BibTeXFile {
    /**
     * @brief Path to the bibtex file
     */
    std::string m_file;
    /**
     * @brief List with parsed BibTeXItems of this file
     */
    std::vector< BibTeXItem* > m_items;
public:
    /**
     * @brief Constructor
     * @param file Path to the file
     */
    BibTeXFile( const std::string file );
    
    /**
     * @brief Get all BibTeXItems of this file
     * @returns A vector containing all BibTeXItem of this file
     * @note Will be empty, if parse_bibtex_file() is not called before
     */
    const std::vector< BibTeXItem* > get_items() const;
    
    /**
     * @brief Parse all entries of the BibTeX file
     * @returns True on success
     */
    bool parse_bibtex_file();
};


/**
 * @brief The top-level BibTeX datastructure containing all parsed files
 */
class BibTeX {
public:
    /**
     * @brief A list of BibTeXItem
     */
    typedef std::vector< BibTeXItem* > ItemList;
    /**
     * @brief A list of ItemList mapped to a string key
     */
    typedef std::map< std::string, ItemList* > TypeList;
    /**
     * @brief A list of TypeList mapped to an unsigned integer key
     */
    typedef std::map< const unsigned int, TypeList* > YearList;
    
    /**
     * @brief A BibTeX exception
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
    
private:
    /**
     * @brief List of BibTeX files
     */
    std::vector< std::string > m_files;
    /**
     * @brief List of parsed BibTeX items of all files
     */
    TypeList m_items;
    
public:
    /**
     * @brief Constructor
     */
    BibTeX();
    
    /**
     * @brief Get all BibTeXItem ordered by year and type
     * @returns An ordered YearList
     * @note Returns an empty YearList, if parse_bibtex_files was not called before
     */
    YearList* by_year() const;
    
    /**
     * @brief Parse the BibTeX files (*.bib) from a directory and its subdirectories
     * @param path Path of the root directory to start parsing with
     * @returns True on success
     */
    bool parse_bibtex_files( const std::string path );
};

