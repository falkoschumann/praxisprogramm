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

#include "patientform.h"
#include "ui_patientformbody.h"

#include <core/recordnavigation.h>

#include <QHBoxLayout>
#include <QLabel>

using namespace Core;

namespace Stammdaten {

class PatientFormPrivate {
public:
    Ui::PatientForm *uiBody;
};

PatientForm::PatientForm(QWidget *parent) :
    Form(parent),
    d_ptr(new PatientFormPrivate())
{
    Q_D(PatientForm);
    QWidget *header = new QWidget();
    header->setStyleSheet("background-color:red;");
    QLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(new QLabel("Patient"));
    header->setLayout(headerLayout);
    setHeader(header);

    QWidget *body = new QWidget();
    d->uiBody = new Ui::PatientForm();
    d->uiBody->setupUi(body);
    setBody(body);

    RecordNavigation *footer  = new RecordNavigation();
    setFooter(footer);
}

PatientForm::~PatientForm()
{
    delete d_ptr;
}

} // namespace Stammdaten
