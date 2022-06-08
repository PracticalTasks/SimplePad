#pragma once
#include"WorkerThread.h"

class WorkerThread;

class SearchWdg : public QWidget
{
	Q_OBJECT

public:
	SearchWdg(QString& _strValidPath, QWidget* parent = nullptr);
	~SearchWdg();
private:
	QLineEdit* lineSearch = nullptr;
	QListWidget* lstWidget = nullptr;
	QVBoxLayout* vBoxLayout = nullptr;
	std::unique_ptr<WorkerThread> workerThread;

	QThread trWorker;

	QString path = QDir::currentPath();
private slots:
	void findFile();

public slots:
	void foundFile(QString&);

signals:
	void startSearch(QString&, QString&);



};

