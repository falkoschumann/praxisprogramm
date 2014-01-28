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

#include "mainwindow.h"

#include <stammdaten/patientform.h>

#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using namespace Stammdaten;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Praxisprogramm");
    resize(1000, 600);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) qFatal("Can't open database.");
    QSqlQuery query;
    if (!query.exec("CREATE TABLE patient (anrede TEXT default '', vorname TEXT default '', nachname TEXT default '', wohnort TEXT default '', geburtsdatum TEXT default 0)")) qCritical() << QString("Can't create patient table: %1").arg(query.lastError().text());
    if (!query.exec(QString("INSERT INTO patient (anrede, vorname, nachname, wohnort, geburtsdatum) VALUES ('%1', '%2', '%3', '%4', '%5')").arg("Herr").arg("Lukas").arg("Maurer").arg("Beuron").arg("1939-11-01"))) qCritical() << QString("Can't insert patient Lukas Maurer: %1").arg(query.lastError().text());
    if (!query.exec(QString("INSERT INTO patient (anrede, vorname, nachname, wohnort, geburtsdatum) VALUES ('%1', '%2', '%3', '%4', '%5')").arg("Frau").arg("Johanna").arg("Gottlieb").arg("Brücken").arg("1930-11-18"))) qCritical() << QString("Can't insert patient Johanna Gottlieb: %1").arg(query.lastError().text());
    if (!query.exec(QString("INSERT INTO patient (anrede, vorname, nachname, wohnort, geburtsdatum) VALUES ('%1', '%2', '%3', '%4', '%5')").arg("Herr").arg("Andreas").arg("Schmitz").arg("Bottenbach").arg("1992-07-13"))) qCritical() << QString("Can't insert patient Andreas Schmitz: %1").arg(query.lastError().text());
    if (!query.exec(QString("INSERT INTO patient (anrede, vorname, nachname, wohnort, geburtsdatum) VALUES ('%1', '%2', '%3', '%4', '%5')").arg("Herr").arg("Michael").arg("Lehmann").arg("Putzbrunn").arg("1967-12-10"))) qCritical() << QString("Can't insert patient Michael Lehmann: %1").arg(query.lastError().text());
    if (!query.exec(QString("INSERT INTO patient (anrede, vorname, nachname, wohnort, geburtsdatum) VALUES ('%1', '%2', '%3', '%4', '%5')").arg("Frau").arg("Christina").arg("Eisenhauer").arg("Nannhausen").arg("1989-02-09"))) qCritical() << QString("Can't insert patient Christina Eisenhauer: %1").arg(query.lastError().text());

    setCentralWidget(new PatientForm(this));
}

MainWindow::~MainWindow()
{
    {
        QSqlDatabase db;
        db.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
