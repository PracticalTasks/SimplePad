#pragma once
//#include"SimplePad.h"
#include<QtWidgets>


class SearchWdg : public QWidget
{
	Q_OBJECT

public:
	SearchWdg(QString _strValidPath, QWidget* parent = nullptr);

private:
	QLineEdit* lineSearch = nullptr;
	QListWidget* lstWidget = nullptr;
	QVBoxLayout* vBoxLayout = nullptr;
	

	QString strValidPath = QDir::currentPath();
public slots:
	void findFile();

};

