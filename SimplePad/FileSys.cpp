#include"FileSys.h"
#include<QFileDialog>

FileSys::FileSys() 
    : file(new QFile)
{
}

FileSys::~FileSys()
{
    file->close();
    delete file;
}

QString FileSys::openFile()
{
    QString str = QFileDialog::getOpenFileName(this, "Open file",
        QDir::currentPath(), "Text file(*.txt);; All(*.*)");

    if (!str.isEmpty())
    {
        file->setFileName(str);
        if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            QTextStream stream(file);
            return stream.readAll();
        }
    }

    return nullptr;
}

void FileSys::saveFile(QString txt)
{
    QString str = QFileDialog::getSaveFileName(this, tr("Save file"),
        QDir::currentPath(), tr("Text file(*.txt);; All(*.*)"));

    if (!str.isEmpty())
    {
        if (str.endsWith(".txt"))
        {
            file->setFileName(str);
            if (file->open(QFile::WriteOnly))
            {
                QTextStream stream(file);
                stream << txt;
            }
        }
    }
}

QString FileSys::loadFile(QString str)
{
    file->setFileName(str);
    if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
        str = file->readAll();

    return str;
}
