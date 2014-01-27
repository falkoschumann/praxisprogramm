/* Copyright (c) 2014, Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "mainwindow.h"

#include <core/form.h>

#include <QHBoxLayout>
#include <QLabel>

using namespace Core;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Praxisprogramm");
    resize(1000, 600);

    QWidget *header = new QWidget();
    header->setStyleSheet("background-color:red;");
    QLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(new QLabel("Header"));
    header->setLayout(headerLayout);

    QWidget *body = new QWidget();
    body->setStyleSheet("background-color:yellow;");
    QLayout *bodyLayout = new QHBoxLayout();
    bodyLayout->addWidget(new QLabel("Body"));
    body->setLayout(bodyLayout);

    QWidget *footer = new QWidget();
    footer->setStyleSheet("background-color:green;");
    QLayout *footerLayout = new QHBoxLayout();
    footerLayout->addWidget(new QLabel("Footer"));
    footer->setLayout(footerLayout);

    Form *form = new Form(this);
    form->setBody(body);
    form->setHeader(header);
    form->setFooter(footer);
    setCentralWidget(form);
}

MainWindow::~MainWindow()
{
}
