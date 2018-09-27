
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

/**
 * @brief Test, if the string contains whitespace characters and linebreaks only
 * @param str String to test
 * @returns True on success
 */
bool only_whitespace_characters( const std::string str );

/**
 * @brief Remove all whitespace and newline characters from a string
 * @param str Original string
 * @returns A copy of the string with the characters removed
 */
const std::string strip_whitespace_characters( const std::string str );

/**
 * @brief Remove the characters '"', '{', '}' and a comma at the last position from a string
 * @param str Original string
 * @returns A copy of the string with the characters removed
 */
const std::string strip_delimiter_characters( const std::string str );

/**
 * @brief Escape 'Ä', 'Ö', 'Ü', 'ä', 'ö', 'ü' and 'ß' for HTML
 * @param str Original string
 * @returns A copy of the string with characters escaped for HTML
 */
std::string escape_string( const std::string str );
