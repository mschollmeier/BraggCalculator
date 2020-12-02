/***** GPL *******************************************************************
**                                                                          **
** This file is part of BraggCalculator, a GUI-based program to quickly     **
** evaluate the Bragg equation for x-ray reflection.                        **
**                                                                          **
** Copyright (c) 2020  Marius S. Schollmeier                                **
**                                                                          **
** This program is free software: you can redistribute it and/or modify     **
** it under the terms of the GNU General Public License as published by     **
** the Free Software Foundation, either version 3 of the License, or        **
** (at your option) any later version.                                      **
**                                                                          **
** This program is distributed in the hope that it will be useful,          **
** but WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            **
** GNU General Public License for more details.                             **
**                                                                          **
** You should have received a copy of the GNU General Public License        **
** along with this program.  If not, see <https://www.gnu.org/licenses/     **
**                                                                          **
******************************************************************************
** Author:  Marius Schollmeier,                                             **
** Contact: mschollmeier01@gmail.com                                        **
** Date:    Dec. 02, 2020                                                   **
** Version: 1.0                                                             **
*****************************************************************************/

#ifndef UNICODECHARACTERS_H
#define UNICODECHARACTERS_H

#include <QString>

namespace UnicodeCharacters {

// unicode symbols using \x escape code, which is compatible with MSVC as well as clang/gcc
// converter: https://r12a.github.io/app-conversion/ -> use "Percent encoding for URIs" and replace % with \x
// also: Mac -> Show Emoji and Symbols -> copy character info

// Greek letters
// https://en.wikipedia.org/wiki/Greek_alphabet#Greek_in_Unicode
// upper case
const auto Alpha = QString::fromUtf8("\xCE\x91");           //unicode \u0391
const auto Beta = QString::fromUtf8("\xCE\x92");            //unicode \u0392
const auto Gamma = QString::fromUtf8("\xCE\x93");           //unicode \u0393
const auto Delta = QString::fromUtf8("\xCE\x94");           //unicode \u0394
const auto Epsilon = QString::fromUtf8("\xCE\x95");         //unicode \u0395
const auto Zeta = QString::fromUtf8("\xCE\x96");            //unicode \u0396
const auto Eta = QString::fromUtf8("\xCE\x97");             //unicode \u0397
const auto Theta = QString::fromUtf8("\xCE\x98");           //unicode \u0398
const auto Iota = QString::fromUtf8("\xCE\x99");            //unicode \u0399
const auto Kappa = QString::fromUtf8("\xCE\x9A");           //unicode \u039A
const auto Lambda = QString::fromUtf8("\xCE\x9B");          //unicode \u039B
const auto Mu = QString::fromUtf8("\xCE\x9C");              //unicode \u039C
const auto Nu = QString::fromUtf8("\xCE\x9D");              //unicode \u039D
const auto Xi = QString::fromUtf8("\xCE\x9E");              //unicode \u039E
const auto Omicron = QString::fromUtf8("\xCE\x9F");         //unicode \u039F
const auto Pi = QString::fromUtf8("\xCE\xA0");              //unicode \u03A0
const auto Rho = QString::fromUtf8("\xCE\xA1");             //unicode \u03A1
// \u03A2 is not assigned
const auto Sigma = QString::fromUtf8("\xCE\xA3");           //unicode \u03A3
const auto Tau = QString::fromUtf8("\xCE\xA4");             //unicode \u03A4
const auto Upsilon = QString::fromUtf8("\xCE\xA5");         //unicode \u03A5
const auto Phi = QString::fromUtf8("\xCE\xA6");             //unicode \u03A6
const auto Chi = QString::fromUtf8("\xCE\xA7");             //unicode \u03A7
const auto Psi = QString::fromUtf8("\xCE\xA8");             //unicode \u03A8
const auto Omega = QString::fromUtf8("\xCE\xA9");           //unicode \u03A9
// lower case
const auto alpha = QString::fromUtf8("\xCE\xB1");           //unicode \u03B1
const auto beta = QString::fromUtf8("\xCE\xB2");            //unicode \u03B2
const auto gamma = QString::fromUtf8("\xCE\xB3");           //unicode \u03B3
const auto delta = QString::fromUtf8("\xCE\xB4");           //unicode \u03B4
const auto epsilon = QString::fromUtf8("\xCE\xB5");         //unicode \u03B5
const auto zeta = QString::fromUtf8("\xCE\xB6");            //unicode \u03B6
const auto eta = QString::fromUtf8("\xCE\xB7");             //unicode \u03B7
const auto theta = QString::fromUtf8("\xCE\xB8");           //unicode \u03B8
const auto iota = QString::fromUtf8("\xCE\xB9");            //unicode \u03B9
const auto kappa = QString::fromUtf8("\xCE\xBA");           //unicode \u03BA
const auto lambda = QString::fromUtf8("\xCE\xBB");          //unicode \u03BB
const auto mu = QString::fromUtf8("\xCE\xBC");              //unicode \u03BC
const auto nu = QString::fromUtf8("\xCE\xBD");              //unicode \u03BD
const auto xi = QString::fromUtf8("\xCE\xBE");              //unicode \u03BE
const auto omicron = QString::fromUtf8("\xCE\xBF");         //unicode \u03BF
const auto pi = QString::fromUtf8("\xCF\x80");              //unicode \u03C0
const auto rho = QString::fromUtf8("\xCF\x81");             //unicode \u03C1
const auto finalSigma = QString::fromUtf8("\xCF\x82");      //unicode \u03C2
const auto sigma = QString::fromUtf8("\xCF\x83");           //unicode \u03C3
const auto tau = QString::fromUtf8("\xCF\x84");             //unicode \u03C4
const auto upsilon = QString::fromUtf8("\xCF\x85");         //unicode \u03C5
const auto phi = QString::fromUtf8("\xCF\x86");             //unicode \u03C6
const auto chi = QString::fromUtf8("\xCF\x87");             //unicode \u03C7
const auto psi = QString::fromUtf8("\xCF\x88");             //unicode \u03C8
const auto omega = QString::fromUtf8("\xCF\x89");           //unicode \u03C9
// variants
const auto varphi = QString::fromUtf8("\xCF\x95");          //unicode \u03D5
const auto varkappa = QString::fromUtf8("\xCF\xB0");        //unicode \u03F0
const auto varrho = QString::fromUtf8("\xCF\xB1");          //unicode \u03F1
const auto vartheta = QString::fromUtf8("\xCF\x91");        //unicode \u03D1


// Math and engineering symbols
// MacOS -> Emoji and Symbols
const auto multiplyBy = QString::fromUtf8("\xC3\x97");      //unicode \u00D7
const auto divideBy = QString::fromUtf8("\xC3\xB7");        //unicode \u00F7
const auto almostEqual = QString::fromUtf8("\xE2\x89\x88"); //unicode \u2248
const auto plusMinus = QString::fromUtf8("\xC2\xB1");       //unicode \u00B1
const auto minusPlus = QString::fromUtf8("\xE2\x88\x93");   //unicode \u2213
const auto infinity = QString::fromUtf8("\xE2\x88\x9E");    //unicode \u221E

const auto angstrom = QString::fromUtf8("\xC3\x85");        //unicode \u00C5
const auto diameter = QString::fromUtf8("\xE2\x8C\x80");    //unicode \u2300
const auto degree = QString::fromUtf8("\xC2\xB0");          //unicode \u00B0
const auto hBar = QString::fromUtf8("\xE2\x84\x8F");        //unicode \u210F

// Arrows
// https://en.wikipedia.org/wiki/Arrow_(symbol)#Arrows_in_Unicode
// and MacOS -> Emoji and Symbols
const auto downArrow = QString::fromUtf8("\xE2\x86\x93");           //unicode \u2193
const auto leftArrow = QString::fromUtf8("\xE2\x86\x90");           //unicode \u2190
const auto leftRightArrow = QString::fromUtf8("\xE2\x86\x94\xEF\xB8\x8E"); //unicode \u2194
const auto longLeftArrow = QString::fromUtf8("\xE2\x9F\xB5");       //unicode \u27F5
const auto longLeftDoubleArrow = QString::fromUtf8("\xE2\x9F\xB8"); //unicode \u27F8
const auto longLeftRightArrow = QString::fromUtf8("\xE2\x9F\xB7");  //unicode \u27F7
const auto longLeftRightDoubleArrow = QString::fromUtf8("\xE2\x9F\xBA"); //unicode \u27FA
const auto longRightArrow = QString::fromUtf8("\xE2\x9F\xB6");      //unicode \u27F6
const auto longRightDoubleArrow = QString::fromUtf8("\xE2\x9F\xB9"); //unicode \u27F9
const auto rightArrow = QString::fromUtf8("\xE2\x86\x92");          //unicode \u2192
const auto upArrow = QString::fromUtf8("\xE2\x86\x91");             //unicode \u2191

} // end of namespace

#endif // UNICODECHARACTERS_H
