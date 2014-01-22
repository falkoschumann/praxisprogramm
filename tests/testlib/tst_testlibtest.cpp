#include <QString>
#include <QtTest>

class TestlibTest : public QObject
{
    Q_OBJECT

public:
    TestlibTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
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
