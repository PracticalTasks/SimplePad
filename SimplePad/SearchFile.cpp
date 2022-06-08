#include"SearchFile.h"

SearchFile::SearchFile(QWidget* parent) :  QWidget(parent)
{
	this->resize(500, 300);

	label = new QLabel(this);
	label->setText(tr("Search line"));
	searchLine = new QLineEdit(this);
	layout = new QGridLayout(this);
	//layout->addWidget(label,0,0,0,1);
	layout->addWidget(label, 0, 0, 0, 1);
	layout->addWidget(searchLine);
	//layout->setContentsMargins(5, 5, 5, 5);
	//layout->setSpacing(15);
	//QWidget* centralWgt = new QWidget(this);
	//centralWgt->setLayout(layout);
	this->setLayout(layout);

}
