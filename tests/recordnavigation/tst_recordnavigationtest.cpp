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

#include <QtTest>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <core/recordnavigation.h>

using namespace Core;

class RecordNavigationTest : public QObject
{
    Q_OBJECT

public:
    RecordNavigationTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testInitialized();
    void testSetCurrentIndex();
    void testPressToNext();
    void testPressToPrevious();
    void testPressToFirst();
    void testPressToLast();
    void testInputElementNumber();
    void testPressToNew();
    void testPressToNewThanToPrevious();
    void testSetCurrentIndexToNewRecord();
    void testPressToLastThanToNext();

private:
    void createColorTable() const;
    void insertColor(const QString &colorName, int sorting) const;
    void assertInvariant();
    void assertElement(int elementNumber);
    void setModel();
    void setCurrentIndex(int index);
    void inputElement(int elementNumber);
    void pressToNext();
    void pressToPrevious();
    void pressToFirst();
    void pressToLast();
    void pressToNew();

    RecordNavigation *fixture;
    QSqlTableModel *model;
    QToolButton *toFirstButton;
    QToolButton *toPreviousButton;
    QToolButton *toNextButton;
    QLineEdit *currentRow;
    QToolButton *toLastButton;
    QToolButton *toNewButton;
    QLabel *rowCountLabel;
};

RecordNavigationTest::RecordNavigationTest()
{
}

void RecordNavigationTest::initTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) QFAIL("Can't open database.");

    createColorTable();
    insertColor("red", 1);
    insertColor("green", 2);
    insertColor("blue", 3);
    insertColor("cyan", 4);
    insertColor("magenta", 5);
    insertColor("yellow", 6);
    insertColor("black", 7);
}

void RecordNavigationTest::createColorTable() const
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE colors (name TEXT default '', sorting INT default 0)")) QFAIL("Can't create colors table");
}

void RecordNavigationTest::insertColor(const QString &colorName, int sorting) const
{
    QSqlQuery query;
    if (!query.exec(QString("INSERT INTO colors (name, sorting) VALUES ('%1', %2)").arg(colorName).arg(sorting)))
        QFAIL(QString("Can't insert color %1").arg(colorName).toStdString().c_str());
}

void RecordNavigationTest::cleanupTestCase()
{
    {
        QSqlDatabase db;
        db.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void RecordNavigationTest::init()
{
    model = new QSqlTableModel();
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable("colors");
    model->setSort(1, Qt::AscendingOrder);
    model->select();

    fixture = new RecordNavigation();
    assertInvariant();

    toFirstButton = fixture->findChild<QToolButton *>("toFirstButton");
    toPreviousButton = fixture->findChild<QToolButton *>("toPreviousButton");
    toNextButton = fixture->findChild<QToolButton *>("toNextButton");
    toLastButton = fixture->findChild<QToolButton *>("toLastButton");
    toNewButton = fixture->findChild<QToolButton *>("toNewButton");

    currentRow = fixture->findChild<QLineEdit *>("currentRow");
    rowCountLabel = fixture->findChild<QLabel *>("rowCountLabel");

    setModel();
    assertInvariant();
}

void RecordNavigationTest::setModel()
{
    fixture->setModel(model);
}

void RecordNavigationTest::assertInvariant()
{
    QVERIFY2((0 <= fixture->currentIndex() && fixture->currentIndex() <= fixture->model()->rowCount()) || (fixture->currentIndex() == RecordNavigation::NEW_RECORD), "invariant");
}

/**
 * @param elementNumber the element number display to the user
 */
void RecordNavigationTest::assertElement(int elementNumber)
{
    bool firstElement = elementNumber == 1;
    bool lastElement = elementNumber == 7;
    bool newElement = elementNumber == RecordNavigation::NEW_RECORD;
    QCOMPARE(toFirstButton->isEnabled(), !firstElement);
    QCOMPARE(toPreviousButton->isEnabled(), !firstElement);
    QCOMPARE(toNextButton->isEnabled(), !newElement);
    QCOMPARE(toLastButton->isEnabled(), !lastElement);
    QCOMPARE(toNewButton->isEnabled(), !newElement);

    if (newElement) {
        QCOMPARE(fixture->currentIndex(), RecordNavigation::NEW_RECORD);
        QCOMPARE(currentRow->text(), QString("8"));
        QCOMPARE(rowCountLabel->text(), QString("of 8"));
    } else {
        QCOMPARE(fixture->currentIndex(), elementNumber - 1);
        QCOMPARE(currentRow->text(), QString::number(elementNumber));
        QCOMPARE(rowCountLabel->text(), QString("of 7"));
    }
}

void RecordNavigationTest::cleanup()
{
    assertInvariant();

    delete fixture;
    delete model;
}

void RecordNavigationTest::testInitialized()
{
    assertElement(1);
}

void RecordNavigationTest::testSetCurrentIndex()
{
    setCurrentIndex(4);
    assertElement(5);
}

void RecordNavigationTest::setCurrentIndex(int index)
{
    fixture->setCurrentIndex(index);
}

void RecordNavigationTest::testPressToNext()
{
    inputElement(5);
    pressToNext();
    assertElement(6);
}

void RecordNavigationTest::testInputElementNumber()
{
    inputElement(4);
    assertElement(4);
}

void RecordNavigationTest::inputElement(int elementNumber)
{
    QTest::keyEvent(QTest::Click, currentRow, Qt::Key_Backspace);
    QTest::keyClicks(currentRow, QString::number(elementNumber));
    QTest::keyEvent(QTest::Click, currentRow, Qt::Key_Enter);
}

void RecordNavigationTest::pressToNext()
{
    QTest::mouseClick(toNextButton, Qt::LeftButton);
}

void RecordNavigationTest::testPressToPrevious()
{
    inputElement(4);
    pressToPrevious();
    assertElement(3);
}

void RecordNavigationTest::pressToPrevious()
{
    QTest::mouseClick(toPreviousButton, Qt::LeftButton);
}

void RecordNavigationTest::testPressToFirst()
{
    inputElement(3);
    pressToFirst();
    assertElement(1);
}

void RecordNavigationTest::pressToFirst()
{
    QTest::mouseClick(toFirstButton, Qt::LeftButton);
}

void RecordNavigationTest::testPressToLast()
{
    inputElement(4);
    pressToLast();
    assertElement(7);
}

void RecordNavigationTest::pressToLast()
{
    QTest::mouseClick(toLastButton, Qt::LeftButton);
}

void RecordNavigationTest::testPressToNew()
{
    inputElement(5);
    pressToNew();
    assertElement(RecordNavigation::NEW_RECORD);
}

void RecordNavigationTest::pressToNew()
{
    QTest::mouseClick(toNewButton, Qt::LeftButton);
}

void RecordNavigationTest::testPressToNewThanToPrevious()
{
    inputElement(5);
    pressToNew();
    pressToPrevious();
    assertElement(7);
}

void RecordNavigationTest::testSetCurrentIndexToNewRecord()
{
    inputElement(2);
    setCurrentIndex(RecordNavigation::NEW_RECORD);
    assertElement(RecordNavigation::NEW_RECORD);
}

void RecordNavigationTest::testPressToLastThanToNext()
{
    pressToLast();
    pressToNext();
    assertElement(RecordNavigation::NEW_RECORD);
}

QTEST_MAIN(RecordNavigationTest)

#include "tst_recordnavigationtest.moc"
