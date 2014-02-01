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

#include "form.h"
#include "form_p.h"

#include <core/recordnavigation.h>

#include <QDataWidgetMapper>
#include <QVBoxLayout>
#include <QAbstractItemModel>

namespace Core {

FormPrivate::FormPrivate(Form *q) :
    q_ptr(q),
    layout(new QVBoxLayout()),
    header(0),
    body(0),
    footer(0),
    recordNavigation(new RecordNavigation()),
    mapper(new QDataWidgetMapper(this)),
    model(0)
{
    layout->addWidget(recordNavigation);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    connect(recordNavigation, SIGNAL(currentIndexChanged(int)), mapper, SLOT(setCurrentIndex(int)));
}

FormPrivate::~FormPrivate()
{
}

int FormPrivate::indexOfHeader() {
    return 0;
}

int FormPrivate::indexOfBody() {
    if (!header) return 0;

    return 1;
}

int FormPrivate::indexOfFooter() {
    if (!header && !body) return 0;
    if (!header || !body) return 1;
    return 2;
}

/*!
 * \todo support root index \see QDataWidgetMapper
 */
Form::Form(QWidget *parent) :
    QWidget(parent),
    d_ptr(new FormPrivate(this))
{
    Q_D(Form);
    setLayout(d->layout);
}

Form::~Form()
{
    delete d_ptr;
}

QWidget *Form::header() const
{
    Q_D(const Form);
    return d->header;
}

void Form::setHeader(QWidget *header)
{
    Q_D(Form);
    header->setObjectName(QString::fromUtf8("header"));
    d->layout->insertWidget(d_ptr->indexOfHeader(), header);
    d->header = header;
}

QWidget *Form::body() const
{
    Q_D(const Form);
    return d->body;
}

void Form::setBody(QWidget *body)
{
    Q_D(Form);
    body->setObjectName(QString::fromUtf8("body"));
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Expanding);
    body->setSizePolicy(sp);
    d->layout->insertWidget(d_ptr->indexOfBody(), body);
    d->body = body;
}

QWidget *Form::footer() const
{
    Q_D(const Form);
    return d->footer;
}

void Form::setFooter(QWidget *footer)
{
    Q_D(Form);
    footer->setObjectName(QString::fromUtf8("footer"));
    d->layout->insertWidget(d_ptr->indexOfFooter(), footer);
    d->footer = footer;
}

QAbstractItemModel *Form::model() const
{
    Q_D(const Form);
    return d->model;
}

/*!
 * \note Das Form übernimmt nicht den Besitz des model-Objekts.
 * \todo Was passiert, wenn das model 0 ist?
 */
void Form::setModel(QAbstractItemModel *model)
{
    Q_D(Form);
    d->model = model;
    d->recordNavigation->setModel(model);
    d->mapper->setModel(model);
}

QDataWidgetMapper *Form::dataWidgetMapper() const
{
    Q_D(const Form);
    return d->mapper;
}

} // namespace Core
