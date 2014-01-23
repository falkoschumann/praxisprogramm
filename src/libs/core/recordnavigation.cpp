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

#include "recordnavigation.h"
#include "ui_recordnavigation.h"

#include <QModelIndex>

using namespace Core;

class Core::RecordNavigationPrivate
{
public:
    RecordNavigationPrivate()
        : ui(new Ui::RecordNavigation), model(0)
    {
    }

    ~RecordNavigationPrivate()
    {
        delete ui;
    }

    Ui::RecordNavigation *ui;
    QAbstractItemModel *model;
};

RecordNavigation::RecordNavigation(QWidget *parent)
    : QWidget(parent), d_ptr(new RecordNavigationPrivate)
{
    d_ptr->ui->setupUi(this);
    d_ptr->ui->currentRow->setFocus();
}

RecordNavigation::~RecordNavigation()
{
    delete d_ptr;
}

QAbstractItemModel *RecordNavigation::model() const
{
    return 0;
}

void RecordNavigation::setModel(QAbstractItemModel *model)
{

}

QModelIndex	RecordNavigation::rootIndex() const
{
    return QModelIndex();
}

void RecordNavigation::setRootIndex(const QModelIndex &index)
{

}

int RecordNavigation::currentIndex() const
{
    return -1;
}

void RecordNavigation::setCurrentIndex(int index)
{

}

void RecordNavigation::setCurrentModelIndex(const QModelIndex &index)
{

}

void RecordNavigation::toFirst()
{

}

void RecordNavigation::toLast()
{

}

void RecordNavigation::toNext()
{

}

void RecordNavigation::toPrevious()
{

}
