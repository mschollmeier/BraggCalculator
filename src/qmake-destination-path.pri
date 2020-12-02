# ---------------------------------------------------------------------------#
# Preprocessor definitions for qmake. Adapted from the book "End to End GUI  #
# Development with Qt5" by Nicholas Sherriff, Guillaume Lazar, Robin Penea,  #
# and Marco Piccolino.                                                       #
# Copyright (c) 2018 Packt Publishing.                                       #
#                                                                            #
# This program is free software: you can redistribute it and/or modify       #
# it under the terms of the GNU General Public License as published by       #
# the Free Software Foundation, either version 3 of the License, or          #
# (at your option) any later version.                                        #
#                                                                            #
# This program is distributed in the hope that it will be useful,            #
# but WITHOUT ANY WARRANTY; without even the implied warranty of             #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
# GNU General Public License for more details.                               #
#                                                                            #
# You should have received a copy of the GNU General Public License          #
# along with this program.  If not, see <https://www.gnu.org/licenses/       #
#                                                                            #
# ---------------------------------------------------------------------------#
# Author:  Marius Schollmeier                                                #
# Contact: mschollmeier01@gmail.com                                          #
# Date:    Dec. 02, 2020                                                     #
# Version: 1.0                                                               #
# ---------------------------------------------------------------------------#

platform_path = unknown-platform
compiler_path = unknown-compiler
processor_path = unknown-processor
build_path = unknown-build

PLATFORM_WIN {
    platform_path = windows
}
PLATFORM_OSX {
    platform_path = osx
}
PLATFORM_LINUX {
    platform_path = linux
}

COMPILER_GCC {
    compiler_path = gcc
}
COMPILER_MSVC2017 {
    compiler_path = msvc2017
}
COMPILER_CLANG {
    compiler_path = clang
}

PROCESSOR_x64 {
    processor_path = x64
}
PROCESSOR_x86 {
    processor_path = x86
}

BUILD_DEBUG {
    build_path = debug
} else {
    build_path = release
}

#DESTINATION_PATH = $$platform_path/$$compiler_path/$$processor_path/$$build_path
DESTINATION_PATH = $$platform_path/$$build_path
#message(Dest path: $${DESTINATION_PATH})
