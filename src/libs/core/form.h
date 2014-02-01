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

#ifndef CORE_FORM_H
#define CORE_FORM_H

#include <QWidget>

class QAbstractItemModel;
class QDataWidgetMapper;

namespace Core {

class FormPrivate;

class Form : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(Form)
    Q_DECLARE_PRIVATE(Form)

public:
    explicit Form(QWidget *parent = 0);
    virtual ~Form();

    QWidget *header() const;
    void setHeader(QWidget *header);

    QWidget *body() const;
    void setBody(QWidget *body);

    QWidget *footer() const;
    void setFooter(QWidget *footer);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QDataWidgetMapper *dataWidgetMapper() const;

private:
    FormPrivate *d_ptr;
};

} // namespace Core

#endif // CORE_FORM_H
