#include<QtTest/QtTest>
#include<QtWidgets>
#include"FileSys.h"

class TestFileSys : public QObject
{
	Q_OBJECT
private slots:
	void testOpenFile();

};

//Полу автамотический тест
void TestFileSys::testOpenFile()
{
	FileSys fs;
	//Нажать Отмена
	fs.openFile();
	QCOMPARE(fs.getAddrFile()->fileName(), "");
	//Нажать открыть
	fs.openFile("Test.txt");
	QString str = QFINDTESTDATA("Test.txt");
	QCOMPARE(fs.getAddrFile()->fileName(), str);

}

QTEST_MAIN(TestFileSys)
#include"test.moc"