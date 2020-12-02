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


#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QUndoCommand>

template <typename T, typename spBox>
class spinBoxUndoCommand : public QUndoCommand
{
public:

    enum { Id = 815}; //id of this undocommand
    spinBoxUndoCommand(T newValue,
                      T oldValue,
                      spBox *spinBox,
                      QUndoCommand *parent = nullptr);
    ~spinBoxUndoCommand() override = default;

    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *command) override;
    int id() const override { return Id; }


private:
    /* The variable _isFirstRun is being tested in "redo()".
       If true, will not set spinbox value. This is needed to not
       interrupt user editing when the qundocommand is pushed onto
       the undo stack. When being pushed, as call to redo()
       is invoked.
       */
    bool _isFirstRun {true};
    T _newValue {0.0};
    T _oldValue {0.0};
    spBox *_spinBox;
};

#endif // UNDOCOMMANDS_H
