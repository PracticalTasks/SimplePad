#include<QtTest/QtTest>
#include<QtWidgets>
#include"HotKeys.h"

class TestFileSys : public QObject
{
	Q_OBJECT
private slots:
	void testOpenFile();

};

//���� �������������� ����
void TestFileSys::testOpenFile()
{

}

QTEST_MAIN(TestFileSys)
#include"test.moc"