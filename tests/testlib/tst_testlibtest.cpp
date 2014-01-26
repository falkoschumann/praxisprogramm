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

#include <QString>
#include <QtTest>

class TestlibTest : public QObject
{
    Q_OBJECT

public:
    TestlibTest();

private Q_SLOTS:
    void initTestCase();     // run once before all test cases
    void cleanupTestCase();  // run once after all test cases
    void init();             // run before every test case
    void cleanup();          // run after every test case

    void testCase1();
    void testCase2();
};

TestlibTest::TestlibTest()
{
    qDebug() << "constructor";
}

void TestlibTest::initTestCase()
{
    qDebug() << "initTestCase";
}

void TestlibTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

void TestlibTest::init()
{
    qDebug() << "init";
}

void TestlibTest::cleanup()
{
    qDebug() << "cleanup";
}

void TestlibTest::testCase1()
{
    qDebug() << "testCase1";
    QVERIFY2(true, "Failure");
}

void TestlibTest::testCase2()
{
    qDebug() << "testCase2";
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestlibTest)

#include "tst_testlibtest.moc"
