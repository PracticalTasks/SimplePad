//#pragma once
//#include"SimplePad.h"
//
//class WorkerThread : QObject
//{
//	Q_OBJECT
//
//public:
//	WorkerThread(QObject* parent) : QObject(parent)
//	{
//	}
//
//public slots:
//    void findFile()
//    {
//        lstWidget->clear();
//        auto str = lineSearch->text();
//
//        QDirIterator it(strValidPath, QDirIterator::Subdirectories);
//        while (it.hasNext()) {
//            QFile file(it.next());
//            QFileInfo item(file);
//            if ((item.isFile() || item.isDir()) && item.fileName().contains(str, Qt::CaseInsensitive))
//            {
//                lstWidget->addItem(item.absoluteFilePath());
//
//            }
//        }
//
//    }
//
//};