#pragma once
#include"SimplePad.h"

class WorkerThread : public QObject
{
    Q_OBJECT
public:
    WorkerThread(QObject* parent = nullptr) : QObject(parent)
    {
    }

public slots:
    void doWork(QString& name, QString& path)
    {
        QDirIterator it(path, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QFile file(it.next());
            QFileInfo item(file);
            if ((item.isFile() || item.isDir()) && item.fileName().contains(name, Qt::CaseInsensitive))
            {
                QString findFile = item.absoluteFilePath();
                emit endSearch(findFile);
            }
        }
    }

signals:
    void endSearch(QString&);
};