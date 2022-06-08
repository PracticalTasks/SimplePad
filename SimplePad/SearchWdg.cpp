#include"SearchWdg.h"

SearchWdg::SearchWdg(QString _strValidPath, QWidget* parent)
	: strValidPath(_strValidPath), QWidget(parent)
{
    lineSearch = new QLineEdit(this);
    lstWidget = new QListWidget(this);
    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addWidget(lineSearch);
    vBoxLayout->addWidget(lstWidget);
    this->setLayout(vBoxLayout);
    this->resize(400, 300);
    this->show();

    connect(lineSearch, SIGNAL(editingFinished()), SLOT(findFile()));

}

void SearchWdg::findFile()
{
    lstWidget->clear();
    auto str = lineSearch->text();

    QDirIterator it(strValidPath, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFile file(it.next());
        QFileInfo item(file);
        if ((item.isFile() || item.isDir()) && item.fileName().contains(str, Qt::CaseInsensitive))
        {
            lstWidget->addItem(item.absoluteFilePath());

        }
    }

}

