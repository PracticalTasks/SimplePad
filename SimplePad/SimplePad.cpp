#include "SimplePad.h"
#include<QDir>
#include<QTextStream>

#pragma warning(disable : 4834)

SimplePad::SimplePad(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    treeView = std::make_unique<QTreeView>();
    model = std::make_unique<QFileSystemModel>();
    treeView->setModel(model.get());
    
    ui.gridLayout->addWidget(treeView.get());
    treeView->hide();

    //ui.mainToolBar->

    connect(ui.action_Open_File, SIGNAL(triggered()), SLOT(openFile()));
    connect(ui.actionO_pen_file_Read_only, SIGNAL(triggered()), SLOT(openFileReadOnly()));
    connect(ui.action_Save, SIGNAL(triggered()), SLOT(saveFile()));
    connect(ui.actionEnglish, SIGNAL(triggered()), SLOT(enLanguage()));
    connect(ui.action_Russian, SIGNAL(triggered()), SLOT(ruLanguage()));
    connect(ui.action_About_SimplePad, SIGNAL(triggered()), SLOT(info()));
    connect(ui.action_Dark, SIGNAL(triggered()), SLOT(darkTheme()));
    connect(ui.action_Light, SIGNAL(triggered()), SLOT(lightTheme()));
    connect(ui.actionOpe_n_folder_as_project, SIGNAL(triggered()), SLOT(openFolder()));
    connect(treeView.get(), SIGNAL(doubleClicked(const QModelIndex &)), SLOT(selectItem(const QModelIndex &)));

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
    if (readOnly)
    {
        ui.textEdit->setReadOnly(true);
        readOnly = false;
    }

    else
        ui.textEdit->setReadOnly(false);

}

void SimplePad::openFileReadOnly()
{
    readOnly = true;
    openFile();
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
    this->setStyleSheet("QMainWindow{background: #EFEFEF}QMenuBar{background: white; \
    color: black} QMenuBar::item:selected {background: #C0C0C0} QMenu{background: white;\
    color: black}QMenu::item:selected {background: #0080D0; border-radius: 4px}QTreeView,QTextEdit{background: white; color: black}");

}

void SimplePad::darkTheme()
{
    this->setStyleSheet("QMainWindow{background: #505050}QMenuBar{background: #505050; \
    color: white} QMenuBar::item:selected {background: #707070} QMenu{background: #101010;\
    color: white}QMenu::item:selected {background: #707070; border-radius: 4px}QTreeView,QTextEdit{background: #202020; color: #D0D080}");
}

void SimplePad::openFolder()
{
    QString str = QFileDialog::getExistingDirectory(this, tr("Select folder"), "", QFileDialog::ShowDirsOnly);
    model->setRootPath(QDir::currentPath());
    //model->setFilter(QDir::AllDirs );
    treeView->setRootIndex(model->index(str));
    for (int i = 1; i < model->columnCount(); ++i)
        treeView->hideColumn(i);
    treeView->setHeaderHidden(true);
    treeView->show();


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
