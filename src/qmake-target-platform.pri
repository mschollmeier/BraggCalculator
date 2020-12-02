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


win32 {
       CONFIG += PLATFORM_WIN
       #message(PLATFORM_WIN)
       win32-g++ {
           CONFIG += COMPILER_GCC
           win32-g++:QMAKE_TARGET.arch = x86_64
           #message(COMPILER_GCC)
       }
       win32-msvc2017 {
           CONFIG += COMPILER_MSVC2017
           #message(COMPILER_MSVC2017)
           win32-msvc2017:QMAKE_TARGET.arch = x86_64
        }
}

linux {
       CONFIG += PLATFORM_LINUX
       #message(PLATFORM_LINUX)
       # Make QMAKE_TARGET arch available for Linux
       !contains(QT_ARCH, x86_64){
           QMAKE_TARGET.arch = x86
       }
       else {
           QMAKE_TARGET.arch = x86_64
       }
       linux-g++{
           CONFIG += COMPILER_GCC
           #message(COMPILER_GCC)
       }
}

macx {
       CONFIG += PLATFORM_OSX
       QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14
       #message(PLATFORM_OSX)
       macx-clang {
           CONFIG += COMPILER_CLANG
           #message(COMPILER_CLANG)
           QMAKE_TARGET.arch = x86_64
       }
       macx-clang-32{
           CONFIG += COMPILER_CLANG
           #message(COMPILER_CLANG)
           QMAKE_TARGET.arch = x86
       }
}

contains(QMAKE_TARGET.arch, x86_64) {
    CONFIG += PROCESSOR_x64
    #message(PROCESSOR_x64)
}
else {
    CONFIG += PROCESSOR_x86
    message("WARNING! 32-bit build! PROCESSOR_x86")
}

CONFIG(debug, release|debug) {
    CONFIG += BUILD_DEBUG
#    message(BUILD_DEBUG)
}
else {
    CONFIG += BUILD_RELEASE
#    message(BUILD_RELEASE)
}

