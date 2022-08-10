#include<QtTest/QtTest>
#include<QtWidgets>
#include"SimplePad.h"
#include"FileSys.h"

class TestSimplePad : public QObject
{
	Q_OBJECT
private slots:
	void testTextEdit();
	void testOpenFile();
	void testSaveFile();
};

void TestSimplePad::testTextEdit()
{
	SimplePad sp;
	QString testStr = "Hello QT Test";
	QTest::keyClicks(sp.getUi().textEdit, testStr);
	QCOMPARE(sp.getUi().textEdit->toPlainText(), testStr);
}

//Полу автомотический тест
void TestSimplePad::testOpenFile()
{
	FileSys fs;
	//Нажать ESQ
	fs.openFile();
	QCOMPARE(fs.getAddrFile()->fileName(), "");
	//Нажать ENTER
	fs.openFile("Test.txt");
	QString str = QFINDTESTDATA("Test.txt");
	QCOMPARE(fs.getAddrFile()->fileName(), str);

}

//Полу автомотический тест
void TestSimplePad::testSaveFile()
{
	SimplePad sp;
	FileSys fs;
	//Нажать ENTER
	sp.openFile("SaveFileTest.txt");
	sp.getUi().textEdit->clear();
	QString testStr= "Test save file";
	QTest::keyClicks(sp.getUi().textEdit, testStr);
	//Нажать ENTER
	sp.saveFile("SaveFileTest.txt");
	//Нажать ENTER
	sp.openFile("SaveFileTest.txt");
	QCOMPARE(sp.getUi().textEdit->toPlainText(), testStr);

}

QTEST_MAIN(TestSimplePad)
#include"test.moc"