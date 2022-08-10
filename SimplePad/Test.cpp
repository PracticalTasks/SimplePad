#include<QtTest/QtTest>
#include<QtWidgets>
#include"HotKeys.h"

class TestFileSys : public QObject
{
	Q_OBJECT
private slots:
	void testOpenFile();

};

//Полу автамотический тест
void TestFileSys::testOpenFile()
{

}

QTEST_MAIN(TestFileSys)
#include"test.moc"