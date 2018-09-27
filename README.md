# BibTeX2WebsiteGenerator
#### A program that can generate an ordered website out of BibTeX files
##### v1.0.0

This program creates an ordered website from a directory and its subdirectories out of the BibTeX files in these directories.


### LICENSES

This program is licensed under the conditions of the GPLv3.

* Copyright (C) 2018 Sebastian Lau <lauseb644@gmail.com>

BibTeX2WebsiteGenerator uses libraries and programs of 3rd parties:
* BibTeX2WebsiteGenerator uses LibLogC++ under the terms of the LGPL3 license.

The 3rd party programs and licenses are included in the folder `3rdparty`


### Requirements

* cmake>=3.0
* a c++ compiler supporting stdc++17 (tested for gcc7 and msvc2017)

### Building

You can simply build this with:

```
 % cd /path/to/clone/in
 % git clone https://github.com/nullptrT/bibtex2website
 % cd bibtex2website
 % mkdir build # or some other build directory
 % cd build
 % cmake ..
 % make
```

On windows you may use the `cmake-gui` or `qtcreator` to create build files for MSVC 2015 or later.

## Command line interface

You can convert a set of BibTeX files in a folder and subdirectories to an html file ordered by year.

```
 % 
LibLogC++ v1.9.3 (https://git.0ptr.de/nullptr_t/liblogcpp)
BibTeX2WebsiteGenerator v1.0.0 (https://git.0ptr.de/nullptr_t/bibtex2website)

Usage: bibtex2website_generator <PATH_TO_FILES> <OUTPUT> <PAGE_TITLE> [--verbose]
```


## Graphical user interface

The program has a graphical user interface that can be enabled with the cmake option `-DENABLE_QT_GUI=1`. Qt5Core is required to build this.

