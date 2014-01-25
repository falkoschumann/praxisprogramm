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
        : currentIndex(0), ui(new Ui::RecordNavigation), model(0)
    {
    }

    ~RecordNavigationPrivate()
    {
        delete ui;
    }

    int currentIndex;
    Ui::RecordNavigation *ui;
    QAbstractItemModel *model;
};

/*!
 * \brief Ein Widget zum Navigieren innerhalb eines Modells.
 *
 * Man kann einen Datensatz vor- oder zurückspringen oder zum ersten oder letzten Datensatz
 * springen. Der aktuelle Datensatz und die Anzahl der Datensätze werden angezeigt. Man kann direkt
 * zu einem bestimmten Datensatz springen, in dem man den Datensatzindex angibt. Und natürlich kann
 * ein neuer Datensatz angelegt werden.
 *
 * \invariant 0 <= currentIndex() && currentIndex() <= model()->rowCount()
 */
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

/*!
 * \post model() == model;
 */
void RecordNavigation::setModel(QAbstractItemModel *model)
{

}

int RecordNavigation::currentIndex() const
{
    return 0;
}

/*!
 * \pre 0 <= index && index <= model()->rowCount()
 * \post currentIndex() == index
 */
void RecordNavigation::setCurrentIndex(int index)
{

}

/*!
 * \pre 0 <= index.row() && index.row() <= model()->rowCount()
 * \post currentIndex() == index.row()
 */
void RecordNavigation::setCurrentModelIndex(const QModelIndex &index)
{

}

/*!
 * \post currentIndex() == 0
 */
void RecordNavigation::toFirst()
{

}

/*!
 * \post currentIndex() == model()->rowCount() - 1
 */
void RecordNavigation::toLast()
{

}

/*!
 * \pre $index = currentIndex()
 * \post currentIndex() == $index + 1
 */
void RecordNavigation::toNext()
{

}

/*!
 * \pre $index = currentIndex()
 * \post currentIndex() == $index - 1
 */
void RecordNavigation::toPrevious()
{

}
