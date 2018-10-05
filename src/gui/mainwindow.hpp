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

#include <exception>
#include <QMainWindow>

class QFileDialog;
class QString;
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow of the GUI
 */
class MainWindow
    :   public QMainWindow
{
    Q_OBJECT

protected:
    /**
     * @brief A QFileDialog
     */
    QFileDialog* mw_file_dialog;
    /**
     * @brief The UI of the MainWindow
     */
    Ui::MainWindow *ui;
public:
    /**
     * @brief Constructor
     */
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

private slots:
    /**
     * @brief Constructs and shows a QFileDialog that can choose a directory
     * @note Is invoced, when a directory is to be chosen by QFileDialog
     * @note Connects to slots on_choose_Directory_Chosen and on_choose_FileDialog_Close
     */
    void on_choose_Directory();
    /**
     * @brief Constructs and shows a QFileDialog that can choose a file
     * @note Is invoced, when a directory is to be chosen by QFileDialog
     * @note Connects to slots on_choose_File_Chosen and on_choose_FileDialog_Close
     */
    void on_choose_File();
    /**
     * @brief Generates HTML from the values given to the GUI
     * @note Is invoced, when the "Generieren..." button is pressed
     */
    void on_generate();
    
    /**
     * @brief Closes the QFileDialog, if opened
     */
    void on_choose_FileDialog_Close();
    /**
     * @brief Reads the currently selected directory path from the QFileDialog, replaces the field value and closes the QFileDialog
     */
    void on_choose_Directory_Chosen();
    
    /**
     * @brief Reads the currently selected file path from the QFileDialog, replaces the field value and closes the QFileDialog
     */
    void on_choose_File_Chosen();
};

