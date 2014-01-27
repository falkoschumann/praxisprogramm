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

#include <QVBoxLayout>

namespace Core {

struct FormPrivate
{
    int indexOfHeader() {
        return 0;
    }

    int indexOfBody() {
        if (!header) return 0;

        return 1;
    }

    int indexOfFooter() {
        if (!header && !body) return 0;
        if (!header || !body) return 1;
        return 2;
    }

    QVBoxLayout *layout;
    QWidget *header;
    QWidget *body;
    QWidget *footer;
};

Form::Form(QWidget *parent) :
    QWidget(parent),
    d_ptr(new FormPrivate())
{
    d_ptr->layout = new QVBoxLayout();
    setLayout(d_ptr->layout);
}

Form::~Form()
{
    delete d_ptr;
}

QWidget *Form::header() const
{
    return d_ptr->header;
}

void Form::setHeader(QWidget *header)
{
    header->setObjectName(QString::fromUtf8("header"));
    d_ptr->layout->insertWidget(d_ptr->indexOfHeader(), header);
    d_ptr->header = header;
}

QWidget *Form::body() const
{
    return d_ptr->body;
}

void Form::setBody(QWidget *body)
{
    body->setObjectName(QString::fromUtf8("body"));
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Expanding);
    body->setSizePolicy(sp);
    d_ptr->layout->insertWidget(d_ptr->indexOfBody(), body);
    d_ptr->body = body;
}

QWidget *Form::footer() const
{
    return d_ptr->footer;
}

void Form::setFooter(QWidget *footer)
{
    footer->setObjectName(QString::fromUtf8("footer"));
    d_ptr->layout->insertWidget(d_ptr->indexOfFooter(), footer);
    d_ptr->footer = footer;
}

} // namespace Core
