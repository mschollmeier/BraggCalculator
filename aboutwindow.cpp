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

    ui->copyrightLabel->setText("Copyright 2020 \xC2\xA9 Marius Schollmeier\nSandia National Laboratories\nAll rights reserved.");
    auto txt = QString("Version: %1").arg(VERSION_STRING); //see BraggCalculator.pro
    ui->versionLabel->setText(txt);

    this->resize(this->sizeHint());
    this->setFixedSize(this->size());

}

aboutWindow::~aboutWindow()
{
    delete ui;
}
