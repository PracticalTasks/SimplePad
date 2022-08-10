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
	QString strTest = "Hello QT Test";
	QTest::keyClicks(sp.getUi().textEdit, strTest);
	QCOMPARE(sp.getUi().textEdit->toPlainText(), strTest);
}

//���� �������������� ����
void TestSimplePad::testOpenFile()
{
	FileSys fs;
	//������ ������
	fs.openFile();
	QCOMPARE(fs.getAddrFile()->fileName(), "");
	//������ �������
	fs.openFile("Test.txt");
	QString str = QFINDTESTDATA("Test.txt");
	QCOMPARE(fs.getAddrFile()->fileName(), str);

}

void TestSimplePad::testSaveFile()
{

}

QTEST_MAIN(TestSimplePad)
#include"test.moc"