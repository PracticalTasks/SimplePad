#include "SimplePad.h"
#include<QDir>
#include<QTextStream>

#pragma warning(disable : 4834)

SimplePad::SimplePad(QMainWindow *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    model = new QFileSystemModel(this);
    ui.treeView->setModel(model);
    
    model->setRootPath(QDir::currentPath());
    ui.treeView->setRootIndex(model->index(QDir::currentPath()));
    for (int i = 1; i < model->columnCount(); ++i)
        ui.treeView->hideColumn(i);
    ui.treeView->setHeaderHidden(true);

    ui.lineEdit->setText(QDir::currentPath());

    ui.mainToolBar->addAction(QIcon(":/Resource/open-file.png"), tr("Open"), this, SLOT(openFile()));
    ui.mainToolBar->addAction(QIcon(":/Resource/save.png"), tr("Save"), this, SLOT(saveFile()));
    ui.mainToolBar->addAction(QIcon(":/Resource/print.png"), tr("Print"), this, SLOT(doPrint()));
    ui.mainToolBar->addAction(QIcon(":/Resource/font.png"), tr("Font edit"), this, SLOT(setFont()));
    ui.mainToolBar->addAction(QIcon(":/Resource/left.png"), tr("Alignment left"), this, [&] {ui.textEdit->setAlignment(Qt::AlignLeft); });
    ui.mainToolBar->addAction(QIcon(":/Resource/centr.png"), tr("Alignment center"), this, [&] {ui.textEdit->setAlignment(Qt::AlignCenter); });
    ui.mainToolBar->addAction(QIcon(":/Resource/right.png"), tr("Alignment center"), this, [&] {ui.textEdit->setAlignment(Qt::AlignRight); });
    ui.mainToolBar->addAction(QIcon(":/Resource/paint.png"), tr("Paint shapes"), this, SLOT(paintShapes()));
    ui.mainToolBar->addAction(QIcon(":/Resource/date.png"), tr("Date and time"), this, SLOT(dateAndTime()));
    ui.mainToolBar->addAction(QIcon(":/Resource/date.png"), tr("Find file"), this, SLOT(findFile()));

    connect(ui.action_Open_File, SIGNAL(triggered()), SLOT(openFile()));
    connect(ui.action_Save, SIGNAL(triggered()), SLOT(saveFile()));
    connect(ui.actionEnglish, SIGNAL(triggered()), SLOT(enLanguage()));
    connect(ui.action_Russian, SIGNAL(triggered()), SLOT(ruLanguage()));
    connect(ui.action_About_SimplePad, SIGNAL(triggered()), SLOT(info()));
    connect(ui.action_Dark, SIGNAL(triggered()), SLOT(darkTheme()));
    connect(ui.action_Light, SIGNAL(triggered()), SLOT(lightTheme()));
    connect(ui.actionOpe_n_folder_as_project, SIGNAL(triggered()), SLOT(openFolder()));
    connect(ui.treeView, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(selectItem(const QModelIndex &)));
    connect(ui.action_Print, SIGNAL(triggered()), SLOT(doPrint()));
    connect(ui.actionPaint_shapes, SIGNAL(triggered()), SLOT(paintShapes()));
    connect(ui.lineEdit, SIGNAL(editingFinished()), SLOT(setPath()));
    //connect(ui.lineSearch, SIGNAL(editingFinished()), SLOT(findFile()));
    connect(ui.treeView, SIGNAL(expanded(const QModelIndex &)), SLOT(expandedPath(const QModelIndex &)));
    connect(ui.treeView, SIGNAL(collapsed(const QModelIndex &)), SLOT(collapsedPath(const QModelIndex&)));
    
//Установка русской локализации по умолчанию
    ruLanguage();
    lightTheme();

}


void SimplePad::saveFile()
{
    auto str = QFileDialog::getSaveFileName(this, tr("Save file"),
        QDir::currentPath(), tr("Text file(*.txt);; All(*.*)"));
    if (!str.isEmpty())
    {
        if (str.endsWith(".txt"))
        {
            QFile file(str);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << ui.textEdit->toPlainText();
                file.close();
            }
        }
    }
}

void SimplePad::setIndex(const QString& str)
{
    //model->setRootPath(QDir::currentPath());
    ui.treeView->setRootIndex(model->index(str));
    for (int i = 1; i < model->columnCount(); ++i)
        ui.treeView->hideColumn(i);
    ui.treeView->setHeaderHidden(true);
}

void SimplePad::openFile()
{
    QString str = QFileDialog::getOpenFileName(this, tr("Open file"),
        QDir::currentPath(), tr("Text file(*.txt);; All(*.*)"));

    if (str.length() > 0)
    {
        if (!str.isEmpty())
        {
            QFile file(str);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                QTextStream stream(&file);
                ui.textEdit->setPlainText(stream.readAll());
                file.close();
            }
        }
    }
}

void SimplePad::info()
{
    QString str;
    QFile file(":/Resource/info.txt");
    if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        str = file.readAll();
        file.close();
    }
    QMessageBox::information(nullptr, tr("Info"), str);

}

void SimplePad::keyPressEvent(QKeyEvent* pe)
{
    switch (pe->key())
    {
    case Qt::Key_O:
        if (pe->modifiers() & Qt::ControlModifier)
            openFile();
        break;
    case Qt::Key_S:
        if (pe->modifiers() & Qt::ControlModifier)
            saveFile();
        break;
    case Qt::Key_N:
        if (pe->modifiers() & Qt::ControlModifier)
            ui.textEdit->clear();
        break;
    case Qt::Key_Q:
        if (pe->modifiers() & Qt::ControlModifier)
            this->close();
        break;
    default:
        QWidget::keyPressEvent(pe);
    }
}

void SimplePad::setFont()
{
    ui.textEdit->setFont(QFontDialog::getFont(0, ui.textEdit->font()));

}

void SimplePad::paintShapes()
{
    if (!paintWnd)
    {
        paintWnd = new MyPaint(this);
        paintWnd->setWindowTitle("Paint widget");
    }
        
    paintWnd->show();
    paintWnd->resize(700, 400);

}

void SimplePad::dateAndTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString months[] = { "", " января ", " февраля ", " марта ",
                             " апреля ", " мая ", " июня ",
                             " июля ", " августа ", " сентября ",
                             " октября ", " ноября ", " декабря "
    };


    QString strDate =QString::number(time.hour()) + ':' + QString::number(time.minute()) + ' ' + QString::number(date.day()) + 
        months[date.month()] + QString::number(date.year());
    ui.textEdit->insertPlainText(strDate);
    
}

void SimplePad::setPath()
{
    QString str = ui.lineEdit->text();
    auto idx = model->index(str);
    if (idx.isValid())
    {
        ui.treeView->setRootIndex(idx);
        setIndex(str);
        strValidPath = str;      //Save the valid path
    }
    else
    {
        QMessageBox msgBox;
        msgBox.critical(ui.lineEdit, "Exploer", "Path not found");
        ui.lineEdit->setText(strValidPath);
    }

}

void SimplePad::expandedPath(const QModelIndex& index)
{
    auto str = model->filePath(index);
    ui.lineEdit->setText(str);
    strValidPath = str;
}

void SimplePad::collapsedPath(const QModelIndex& index)
{
    auto str = model->filePath(index.parent());
    ui.lineEdit->setText(str);
    strValidPath = str;
}

void SimplePad::findFile()
{
    if (!searchWdg)
    {
        searchWdg = std::make_unique<SearchWdg>(strValidPath);
       // workerThread->moveToThread(&trWorker);
       // connect(this, SIGNAL(startSearch(QString&)), searchWdg.get(), SLOT(doWork(QString&)));
        //trWorker.start();
    }
    
    
    //emit startSearch(strValidPath);

    //searchWdg = std::make_unique<SearchWdg>(strValidPath);
}

void SimplePad::doPrint()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    if (dlg.exec() == QDialog::Accepted)
        ui.textEdit->print(&printer);
}

void SimplePad::ruLanguage()
{
    translator.load("./simplepad_ru");
    qApp->installTranslator(&translator);
    ui.retranslateUi(this);
}

void SimplePad::enLanguage()
{
    translator.load("./simplepad_en");
    qApp->installTranslator(&translator);
    ui.retranslateUi(this);
}

void SimplePad::lightTheme()
{
    this->setStyleSheet(nullptr);
}

void SimplePad::darkTheme()
{
    QFile file(":/Resource/dark.qss");
    file.open(QIODevice::ReadOnly);
    QString str = file.readAll();
    file.close();
    this->setStyleSheet(str);
}

void SimplePad::openFolder()
{
    QString str = QFileDialog::getExistingDirectory(this, tr("Select folder"), "", QFileDialog::ShowDirsOnly);
    ui.lineEdit->setText(str);
    strValidPath = str;
    setIndex(str);

}

void SimplePad::selectItem(const QModelIndex &index)
{
    auto str = model->filePath(index);

    if (str.length() > 0)
    {
        if (!str.isEmpty())
        {
            QFile file(str);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                QTextStream stream(&file);
                ui.textEdit->setPlainText(stream.readAll());
                file.close();
            }
        }
    }
}

