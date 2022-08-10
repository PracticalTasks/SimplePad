#pragma once
#include<QMainWindow>
#include<QDir>

class FileSys : public QMainWindow
{
public:
	FileSys();
	~FileSys();

	QString openFile();
	void saveFile(QString txt);
	QString loadFile(QString str);

private:
	QFile* file;
};
