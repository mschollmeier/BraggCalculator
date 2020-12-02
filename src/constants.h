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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>

namespace Constants {

// numeric constants
constexpr double const epsilonZero {1.0e-12}; //this is 1e-12 of the currently used units. For example, mm or keV.

// https://www.browserling.com/tools/pi-digits
constexpr long double const pi {3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485L};
constexpr long double const pi_2 {0.5L * pi};
constexpr long double const pi_4 {0.25L * pi};

// physical constants
constexpr double const elemCharge {1.602176634e-19}; //coulomb, elementary charge
constexpr double const speedOfLight {2.99792458e8};   // m/s, speed of light in vacuum
constexpr double const hPlanck {6.62607015e-34};  // Js, Planck constant
constexpr double const hBar {1.054571628e-34}; // Js, Planck constant/2pi
constexpr double const hce {1.2398424509381e-06}; // h * c * e
constexpr double const m_e {9.1093837015e-31}; // kg, electron mass

// conversions
constexpr double const keV2Angstrom {12.398424509381}; // convert keV to angstrom
constexpr double const FWHM2Sigma {0.42466090014400953}; // 1/sqrt(8*log(2))
constexpr double const Sigma2FWHM {2.35482004503095}; // sqrt(8*log(2))

constexpr double const deg2rad = static_cast<double>(pi/180.0L);
constexpr double const rad2deg = static_cast<double>(180.0L/pi);


} //end of namespace

#endif // CONSTANTS_H
