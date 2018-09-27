
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

#include <string>
#include <vector>
#include <utility>


/**
 * @brief A Dict item of a generic typename
 */
template< typename T >
class DictItem
    :   public std::pair< std::string, T >
{
public:
    /**
     * @brief Constructor
     * @param name The key of this element
     * @param element The element
     */
    DictItem( const std::string name, T& element )
        :   std::pair< std::string, T >( name, element )
    {}
};


/**
 * @brief A dictionary of a generic typename
 */
template< typename T >
class Dict
    :   public std::vector< DictItem<T>* >
{
public:
    /**
     * @brief Constructor
     */
    Dict()
        :   std::vector< DictItem<T>* >()
    {}
    
    /**
     * @brief Add a dictionary item to the dictionary
     * @param name The key of the new element
     * @param element The element
     * @returns The dictionary item newly constructed
     */
    DictItem<T>* add_item( const std::string name, T& element ) {
        DictItem<T>* dict_item = new DictItem<T>( name, element );
        this->push_back( dict_item );
        return dict_item;
    }
    
    /**
     * @brief Get a dictionary item
     * @param name The key to search for
     * @returns The dictionary item found for name or 0, if the key is not included
     */
    DictItem<T>* get_item( const std::string name ) const {
        for ( unsigned int i = 0; i < this->size(); i++ ) {
            DictItem<T>* current_item = this->at( i );
            if ( current_item->first.compare( name ) == 0 ) {
                return current_item;
            }
        }
        
        return 0;
    }
};


