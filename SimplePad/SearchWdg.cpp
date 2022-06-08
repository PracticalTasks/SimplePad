#include"SearchWdg.h"

SearchWdg::SearchWdg(QString& strValidPath, QWidget* parent)
	: path(strValidPath), QWidget(parent)
{
    lineSearch = new QLineEdit(this);
    lstWidget = new QListWidget(this);
    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addWidget(lineSearch);
    vBoxLayout->addWidget(lstWidget);
    this->setLayout(vBoxLayout);
    this->resize(400, 300);
    this->setWindowTitle("Поиск файла");
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->show();
    connect(lineSearch, SIGNAL(editingFinished()), SLOT(findFile()));

}

SearchWdg::~SearchWdg()
{
    trWorker.quit();
    trWorker.wait();
}

void SearchWdg::findFile()
{
    if (!workerThread)
    {
        workerThread = std::make_unique<WorkerThread>();
        workerThread->moveToThread(&trWorker);
        connect(this, SIGNAL(startSearch(QString&, QString&)), workerThread.get(), SLOT(doWork(QString&, QString&)));
        connect(workerThread.get(), SIGNAL(endSearch(QString&)), SLOT(foundFile(QString&)));
        trWorker.start();
    }
     
    lstWidget->clear();
    QString name = lineSearch->text();

    emit startSearch(name, path);

}

void SearchWdg::foundFile(QString& findFile)
{
    lstWidget->addItem(findFile);
}

