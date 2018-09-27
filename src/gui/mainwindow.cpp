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
#include "ui_mainwindow.h"

#include "bibtex.hpp"
#include "../config.hpp"
#include "html.hpp"
#include "log.hpp"

#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QString>
#include <QWidget>


MainWindow::MainWindow( QWidget* parent )
    :   QMainWindow( parent )
    ,   mw_file_dialog( 0 )
    ,   ui( new Ui::MainWindow )
{    
    ui->setupUi(this);

    this->setWindowTitle( "BibTeX2Website" );
    ui->status->setText("BibTeX2WebsiteGUI v" + QString(website_generator_VERSION));
    
    QObject::connect( ui->button_choose_folder, &QPushButton::clicked
                    , this, &MainWindow::on_choose_Directory );
    QObject::connect( ui->button_choose_file, &QPushButton::clicked
                    , this, &MainWindow::on_choose_File );
    QObject::connect( ui->button_generate, &QPushButton::clicked
                    , this, &MainWindow::on_generate );
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_choose_Directory() {
    if ( ui->folder->text().length() > 0 ) {
        if ( QFile::exists( ui->folder->text() ) ) {
            mw_file_dialog = new QFileDialog( 0, "Verzeichnis mit BibTeX-Dateien wählen..."
                                            , ui->folder->text() );
        }
    } else {
        mw_file_dialog = new QFileDialog( 0, "Verzeichnis mit BibTeX-Dateien wählen..." );
    }
    
    mw_file_dialog->setFileMode( QFileDialog::Directory );
    mw_file_dialog->setOption( QFileDialog::ShowDirsOnly );
    
    QObject::connect( mw_file_dialog, &QFileDialog::accepted
                    , this, &MainWindow::on_choose_Directory_Chosen );
    QObject::connect( mw_file_dialog, &QFileDialog::rejected
                    , this, &MainWindow::on_choose_FileDialog_Close );

    mw_file_dialog->show();
}


void MainWindow::on_choose_File() {
    if ( ui->file->text().length() > 0 ) {
        if ( QFile::exists( ui->file->text() ) ) {
            mw_file_dialog = new QFileDialog( 0, "HTML-Ausgabe-Datei wählen..."
                                            , ui->file->text() );
        }
    } else {
        mw_file_dialog = new QFileDialog( 0, "HTML-Ausgabe-Datei wählen..." );
    }
    
    mw_file_dialog->setFileMode( QFileDialog::AnyFile );
    
    QObject::connect( mw_file_dialog, &QFileDialog::accepted
                    , this, &MainWindow::on_choose_File_Chosen );
    QObject::connect( mw_file_dialog, &QFileDialog::rejected
                    , this, &MainWindow::on_choose_FileDialog_Close );

    mw_file_dialog->show();
}


void MainWindow::on_generate() {
    if ( ui->title->text().length() > 0
      && ui->folder->text().length() > 0
      && ui->file->text().length() > 0
    ) {
        if ( QFile::exists( ui->folder->text() ) ) {
            
            if ( ui->color_code->text() > 0 ) {
                program_config::color_titles = ui->color_code->text().toStdString();
            }
            
            ui->status->setText("[WebsiteGenerator/BibTeX] - Parse BibTeX-Dateien...");
            BibTeX* tex = new BibTeX();
            try {
                tex->parse_bibtex_files( ui->folder->text().toStdString() );
            } catch ( BibTeX::Exception& texe ) {
                ui->status->setText("Konnte BibTeX nicht parsen: " + QString(texe.what()));
            }
            
            ui->status->setText("[WebsiteGenerator/HTML] - Generiere HTML...");
            try {
                HTML_File* html = HTML::generate( tex );
                html->to_file( ui->file->text().toStdString()
                             , ui->title->text().toStdString() );
            } catch ( HTML::Exception& htmle ) {
                ui->status->setText("Konnte HTML nicht generieren: " + QString(htmle.what()));
            } catch ( std::exception& e ) {
                ui->status->setText("Konnte HTML nicht schreiben: " + QString(e.what()));
            }
            ui->status->setText("Generiert.");
        } else {
            ui->status->setText("Verzeichnis existiert nicht.");
        }
    } else {
        ui->status->setText("Alle Felder müssen ausgefüllt sein.");
    }
}


void MainWindow::on_choose_FileDialog_Close() {
    if ( mw_file_dialog != 0 ) {
        mw_file_dialog->close();
        mw_file_dialog->disconnect();
        delete mw_file_dialog;
    }
}


void MainWindow::on_choose_Directory_Chosen() {
    ui->folder->setText( mw_file_dialog->directory().absolutePath() );
    this->on_choose_FileDialog_Close();
}


void MainWindow::on_choose_File_Chosen() {
    ui->file->setText( mw_file_dialog->selectedFiles()[0] );
    this->on_choose_FileDialog_Close();
}
