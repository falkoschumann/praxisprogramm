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

#ifndef PATIENTFORM_P_H
#define PATIENTFORM_P_H

#include <core/form.h>

class QSqlTableModel;
class QDataWidgetMapper;

namespace Stammdaten {

namespace Ui {
    class PatientFormBody;
}

class PatientForm;

class PatientFormPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PatientFormPrivate)

public:
    enum {
        Patient_Anrede       = 0,
        Patient_Vorname      = 1,
        Patient_Nachname     = 2,
        Patient_Wohnort      = 3,
        Patient_Geburtsdatum = 4
    };

    PatientFormPrivate(QObject *parent = 0);
    virtual ~PatientFormPrivate();

    QSqlTableModel *model;
    QWidget *body;
    Ui::PatientFormBody *uiBody;
    QDataWidgetMapper *mapper;
};

}

#endif // PATIENTFORM_P_H