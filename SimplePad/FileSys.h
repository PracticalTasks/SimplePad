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

private:
	QFile* file;
};
