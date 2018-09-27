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

#include "mainwindow.hpp"

#include "log.hpp"
#include "color_feature.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    stdlog.enable_print_severity(false);
    stdlog << logcpp::warning;
#ifdef __unix__
    stdlog << logcpp::sty_bold;
#endif
    stdlog << "BibTeX2WebsiteGUI v" << website_generator_VERSION << " (https://git.0ptr.de/nullptr_t/bibtex2website)";
#ifdef __unix__
    stdlog << logcpp::ctl_reset_all;
#endif
    stdlog << logcpp::normal << logcpp::endrec;
    stdlog.enable_print_severity();
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
