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

#ifndef CORE_FORM_P_H
#define CORE_FORM_P_H

#include <QObject>

class QDataWidgetMapper;
class QWidget;
class QVBoxLayout;
class QAbstractItemModel;

namespace Core {

class Form;
class RecordNavigation;

class FormPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(FormPrivate)
    Q_DECLARE_PUBLIC(Form)

public:
    FormPrivate(Form *q);
    virtual ~FormPrivate();

    int indexOfHeader();
    int indexOfBody();
    int indexOfFooter();
    void clearAllEditorData();
    QVariant defaultValue(int type);

public slots:
    void setCurrentIndex(int index);

private:
    Form  *q_ptr;
    QVBoxLayout *layout;
    QWidget *header;
    QWidget *body;
    QWidget *footer;
    RecordNavigation *recordNavigation;
    QDataWidgetMapper *mapper;
    QAbstractItemModel *model;
};

} // namespace Core

#endif // CORE_FORM_P_H
