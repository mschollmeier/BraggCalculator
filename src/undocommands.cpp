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

#include "undocommands.h"

template <typename T, typename spBox>
spinBoxUndoCommand<T, spBox>::spinBoxUndoCommand(T newValue,
                                     T oldValue,
                                     spBox *spinBox,
                                     QUndoCommand *parent)
    : QUndoCommand(parent),
      _newValue(newValue),
      _oldValue(oldValue),
      _spinBox(spinBox)

{
#ifdef QT_DEBUG
    setText(QObject::tr("Value changed from %1 to %2")
            .arg(_oldValue)
            .arg(_newValue));
#endif
}


template <typename T, typename spBox>
void spinBoxUndoCommand<T, spBox>::undo()
{
#ifdef QT_DEBUG
    setText(QObject::tr("Undo from %1 to %2")
            .arg(_newValue)
            .arg(_oldValue));
#endif
    _spinBox->blockSignals(true);
    _spinBox->setValue(_oldValue);
    _spinBox->update();
    _spinBox->blockSignals(false);
}


template <typename T, typename spBox>
void spinBoxUndoCommand<T, spBox>::redo()
{
#ifdef QT_DEBUG
    setText(QObject::tr("Redo from %1 to %2")
            .arg(_oldValue)
            .arg(_newValue));
#endif

    // check if redo is called right after construction when
    // the command is being pushed onto the undo stack.
    // If so, do nothing but set _isFirstRun to false.
    if (_isFirstRun) {
      _isFirstRun = false; //set to false for subsequent calls
    } else {
        _spinBox->blockSignals(true);
        _spinBox->setValue(_newValue);
        _spinBox->update();
        _spinBox->blockSignals(false);
    }

}

template <typename T, typename spBox>
bool spinBoxUndoCommand<T, spBox>::mergeWith(const QUndoCommand *command)
{
    auto cmd = static_cast<const spinBoxUndoCommand *>(command);

    if (cmd->_spinBox != _spinBox)
        return false;

    _newValue = cmd->_newValue;
#ifdef QT_DEBUG
    setText(QObject::tr("merge to %1")
        .arg(_newValue));
#endif

    return true;
}



// template type specializations
template class spinBoxUndoCommand<double, QDoubleSpinBox>;
template class spinBoxUndoCommand<int, QSpinBox>;
