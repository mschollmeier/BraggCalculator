[![License](https://img.shields.io/github/license/mschollmeier/BraggCalculator?style=plastic)](https://github.com/mschollmeier/BraggCalculator/LICENSE.txt)

# What is BraggCalculator?
BraggCalculator, is a simple, GUI-based tool to quickly evaluate the [Bragg equation](https://en.wikipedia.org/wiki/Bragg's_law) for x-ray reflection:<br><br>
*m*&lambda; = 2*d* sin &theta;<br>

where *m* is the order of reflection, &lambda; the x-ray wavelength, *d* the lattice spacing of the crystal, and &theta; the angle of incidence with respect to the surface.

BraggCalculate will be part of a larger suite to design x-ray optical instruments that is currently under development.

# Overview
* evaluates the Bragg equation for any given x-ray energy or wavelength, lattice spacing, and reflection order
* calculates both the angle to the surface and to the normal
* PDF and text export
* adjustable precision
* load/save files
* Undo/Redo (mainly for me as a learning experience)

# Build instructions
BraggCalculator requires Qt5, which can be obtained from [https://www.qt.io](https://www.qt.io/download-qt-installer)

Once Qt5 is installed, run the following:
```
qmake
(n)make
```
This creates an executable in the `binaries/<operating system>/release` folder.

