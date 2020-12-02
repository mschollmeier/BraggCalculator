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


#include "aboutwindow.h"
#include "ui_aboutwindow.h"

aboutWindow::aboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutWindow)
{
    ui->setupUi(this);

    // make default font 20% smaller
    QFont font = ui->copyrightLabel->font();
    auto fontSize = font.pointSizeF();
    font.setPointSize(qRound(fontSize * 0.8));
    ui->copyrightLabel->setFont(font);
    ui->versionLabel->setFont(font);

    ui->copyrightLabel->setText("Copyright 2020 \xC2\xA9 Marius Schollmeier\nAll rights reserved.");
    auto txt = QString("Version: %1").arg(VERSION_STRING); //see BraggCalculator.pro
    ui->versionLabel->setText(txt);

    this->resize(this->sizeHint());
    this->setFixedSize(this->size());

}

aboutWindow::~aboutWindow()
{
    delete ui;
}
