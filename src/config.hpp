
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

#pragma once

#include <string>


class program_config {
public:
// Set global variables
static std::string color_titles;
};


// Check the compiler

#ifndef __cplusplus
#error A C++ compiler supporting -std=c++17 is required!
#elif _WINDOWS
#pragma message ("Please make sure, that your compiler supports c++17.")
/*#elif __cplusplus <= 201603
#error A C++ compiler supporting -std=c++17 is required!*/
#endif
