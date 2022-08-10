#pragma once
#include<QMainWindow>
#include<QDir>

class FileSys : public QMainWindow
{
public:
	FileSys();
	~FileSys();

	QString openFile(QString pathFile = QDir::currentPath());
	void saveFile(QString txt);
	QString loadFile(QString str);
	QFile* getAddrFile();

private:
	QFile* file;
};
