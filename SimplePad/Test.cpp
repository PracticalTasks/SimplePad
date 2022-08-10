#include<QtTest/QtTest>
#include<QtWidgets>
#include"SimplePad.h"

class TestSimplePad : public QObject
{
	Q_OBJECT
private slots:
	void testTextEdit();

};

//Полу автамотический тест
void TestSimplePad::testTextEdit()
{
	SimplePad sp;
	QString strTest = "Hello QT Test";
	QTest::keyClicks(sp.getUi().textEdit, strTest);
	QCOMPARE(sp.getUi().textEdit->toPlainText(), strTest);



}

QTEST_MAIN(TestSimplePad)
#include"test.moc"