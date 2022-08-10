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

//���� �������������� ����
void TestSimplePad::testOpenFile()
{
	FileSys fs;
	//������ ESQ
	fs.openFile();
	QCOMPARE(fs.getAddrFile()->fileName(), "");
	//������ ENTER
	fs.openFile("Test.txt");
	QString str = QFINDTESTDATA("Test.txt");
	QCOMPARE(fs.getAddrFile()->fileName(), str);

}

//���� �������������� ����
void TestSimplePad::testSaveFile()
{
	SimplePad sp;
	FileSys fs;
	//������ ENTER
	sp.openFile("SaveFileTest.txt");
	sp.getUi().textEdit->clear();
	QString testStr= "Test save file";
	QTest::keyClicks(sp.getUi().textEdit, testStr);
	//������ ENTER
	sp.saveFile("SaveFileTest.txt");
	//������ ENTER
	sp.openFile("SaveFileTest.txt");
	QCOMPARE(sp.getUi().textEdit->toPlainText(), testStr);

}

QTEST_MAIN(TestSimplePad)
#include"test.moc"