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
#include "recordnavigation_p.h"
#include "ui_recordnavigation.h"

#include <QAbstractItemModel>
#include <QStandardItemModel>

namespace Core {

RecordNavigationPrivate::RecordNavigationPrivate(RecordNavigation *q) :
    q_ptr(q),
    currentIndex(0),
    ui(new Ui::RecordNavigation),
    model(new QStandardItemModel())
{
    ui->setupUi(q);
    ui->currentRow->setFocus();
}

RecordNavigationPrivate::~RecordNavigationPrivate()
{
    delete ui;
}

void RecordNavigationPrivate::update()
{
    // Current state
    int rowCount = model->rowCount();
    bool currentIsFirst = currentIndex == 0;
    bool currentIsLast = currentIndex == rowCount - 1;
    bool currentIsNew = currentIndex == RecordNavigation::NEW_RECORD;

    // Texts
    if (currentIndex == RecordNavigation::NEW_RECORD) {
        ui->currentRow->setText(QString::number(rowCount + 1));
        ui->rowCountLabel->setText(QString("of %1").arg(rowCount + 1));
    } else {
        ui->currentRow->setText(QString::number(currentIndex + 1));
        ui->rowCountLabel->setText(QString("of %1").arg(rowCount));
    }

    // Buttons
    ui->toFirstButton->setEnabled(!currentIsFirst);
    ui->toPreviousButton->setEnabled(!currentIsFirst);
    ui->toNextButton->setEnabled(!currentIsNew);
    ui->toLastButton->setEnabled(!currentIsLast);
    ui->toNewButton->setEnabled(!currentIsNew);
}

void RecordNavigationPrivate::currentRowEdited()
{
    Q_Q(RecordNavigation);
    bool ok;
    int newIndex = ui->currentRow->text().toInt(&ok);
    if (ok) q->setCurrentIndex(newIndex - 1);
}

const int RecordNavigation::NEW_RECORD = -1;

/*!
 * \brief Ein Widget zum Navigieren innerhalb eines Modells.
 *
 * Man kann einen Datensatz vor- oder zurückspringen oder zum ersten oder letzten Datensatz
 * springen. Der aktuelle Datensatz und die Anzahl der Datensätze werden angezeigt. Man kann direkt
 * zu einem bestimmten Datensatz springen, in dem man den Datensatzindex angibt. Und natürlich kann
 * ein neuer Datensatz angelegt werden.
 *
 * \remarks Die Klasse übernimmt nicht den Besitz des Modells und löscht es auch nicht, wenn sie
 *     zerstört wird.
 * \todo support root index \see QDataWidgetMapper
 */
RecordNavigation::RecordNavigation(QWidget *parent) :
    QWidget(parent),
    d_ptr(new RecordNavigationPrivate(this))
{
    Q_D(RecordNavigation);
    connect(d->ui->toFirstButton, SIGNAL(clicked()), this, SLOT(toFirst()));
    connect(d->ui->toPreviousButton, SIGNAL(clicked()), this, SLOT(toPrevious()));
    connect(d->ui->currentRow, SIGNAL(editingFinished()), d, SLOT(currentRowEdited()));
    connect(d->ui->toNextButton, SIGNAL(clicked()), this, SLOT(toNext()));
    connect(d->ui->toLastButton, SIGNAL(clicked()), this, SLOT(toLast()));
    connect(d->ui->toNewButton, SIGNAL(clicked()), this, SLOT(toNew()));
}

RecordNavigation::~RecordNavigation()
{
    delete d_ptr;
}

QAbstractItemModel *RecordNavigation::model() const
{
    Q_D(const RecordNavigation);
    return d->model;
}

void RecordNavigation::setModel(QAbstractItemModel *newModel)
{
    Q_D(RecordNavigation);
    d->model = newModel;
    setCurrentIndex(0);

    Q_ASSERT_X(model() == newModel, "set model", "post condition");
}

int RecordNavigation::currentIndex() const
{
    Q_D(const RecordNavigation);
    return d->currentIndex;
}

void RecordNavigation::setCurrentIndex(int index)
{
    Q_ASSERT_X((0 <= index && index <= model()->rowCount()) || (index == NEW_RECORD), "set current index", "pre condition");

    Q_D(RecordNavigation);
    d->currentIndex = index;
    d->update();
    emit currentIndexChanged(index);

    Q_ASSERT_X((currentIndex() == index), "set current index", "post condition");
}

void RecordNavigation::toFirst()
{
    setCurrentIndex(0);

    Q_ASSERT_X(currentIndex() == 0, "go to first", "post condition");
}

void RecordNavigation::toLast()
{
    setCurrentIndex(model()->rowCount() - 1);

    Q_ASSERT_X(currentIndex() == (model()->rowCount() - 1), "go to last", "post condition");
}

void RecordNavigation::toNext()
{
    const int index = currentIndex();
    Q_ASSERT_X(currentIndex() <= model()->rowCount(), "go to next", "pre condition");

    if (currentIndex() < model()->rowCount()) {
        setCurrentIndex(currentIndex() + 1);
    } else {
        toNew();
    }

    Q_ASSERT_X(currentIndex() == (index + 1), "go to next", "post condition");
}

void RecordNavigation::toPrevious()
{
    const int index = currentIndex();
    Q_ASSERT_X((currentIndex() > 0) || (currentIndex() == NEW_RECORD), "go to previous", "pre condition");

    if (currentIndex() == NEW_RECORD) {
        setCurrentIndex(model()->rowCount() - 1);
    } else {
        setCurrentIndex(currentIndex() - 1);
    }

    Q_ASSERT_X((currentIndex() == index - 1) || (currentIndex() == (model()->rowCount() - 1)), "go to previous", "post condition");
}

void RecordNavigation::toNew()
{
    setCurrentIndex(NEW_RECORD);

    Q_ASSERT_X(currentIndex() == NEW_RECORD, "go to new", "post condition");
}

} // namespace Core
