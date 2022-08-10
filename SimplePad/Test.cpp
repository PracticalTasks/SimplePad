#include<QtTest/QtTest>
#include<QtWidgets>
#include"FileSys.h"

class TestFileSys : public QObject
{
	Q_OBJECT
private slots:
	void testOpenFile();

};

//���� �������������� ����
void TestFileSys::testOpenFile()
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

QTEST_MAIN(TestFileSys)
#include"test.moc"