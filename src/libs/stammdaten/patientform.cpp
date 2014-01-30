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
#include "patientform_p.h"
#include "ui_patientformbody.h"

#include <QDataWidgetMapper>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlTableModel>

using namespace Core;

namespace Stammdaten {

PatientFormPrivate::PatientFormPrivate(QObject *parent) :
    QObject(parent),
    uiBody(new Ui::PatientFormBody())
{
    body = new QWidget();
    uiBody->setupUi(body);
}

PatientFormPrivate::~PatientFormPrivate()
{
    delete uiBody;
}

/*!
 * \todo RecordNavigation aus Header entfernen und in Form einbauen.
 * \todo Neuen Datensatz anlegen unterstützen.
 */
PatientForm::PatientForm(QWidget *parent) :
    Form(parent),
    d_ptr(new PatientFormPrivate())
{
    Q_D(PatientForm);

    QWidget *header = new QWidget();
    QLayout *headerLayout = new QHBoxLayout();
    QLabel *headerLabel = new QLabel("Patient");
    QFont headerFont;
    headerFont.setPointSize(20);
    headerFont.setBold(true);
    headerLabel->setFont(headerFont);
    headerLayout->addWidget(headerLabel);
    header->setLayout(headerLayout);
    setHeader(header);

    setBody(d->body);

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("patient");
    model->setSort(Patient_Nachname, Qt::AscendingOrder);
    model->select();
    setModel(model);

    dataWidgetMapper()->addMapping(d->uiBody->anrede, Patient_Anrede);
    dataWidgetMapper()->addMapping(d->uiBody->vorname, Patient_Vorname);
    dataWidgetMapper()->addMapping(d->uiBody->nachname, Patient_Nachname);
    dataWidgetMapper()->addMapping(d->uiBody->wohnort, Patient_Wohnort);
    dataWidgetMapper()->addMapping(d->uiBody->geburtsdatum, Patient_Geburtsdatum);
    dataWidgetMapper()->toFirst();
}

PatientForm::~PatientForm()
{
    delete d_ptr;
}

} // namespace Stammdaten
