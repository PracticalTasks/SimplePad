#include "SimplePad.h"
#include<QDir>
#include<QTextStream>
#include"FileSys.h"

#pragma warning(disable : 4834)

SimplePad::SimplePad(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    treeView = std::make_unique<QTreeView>();
    model = std::make_unique<QFileSystemModel>();
    treeView->setModel(model.get());
    
    ui.gridLayout_2->addWidget(treeView.get());
    treeView->hide();

    ui.mainToolBar->addAction(QIcon(":/Resource/open-file.png"), tr("Open"), this, SLOT(openFile()));
    ui.mainToolBar->addAction(QIcon(":/Resource/save.png"), tr("Save"), this, SLOT(saveFile()));
    ui.mainToolBar->addAction(QIcon(":/Resource/print.png"), tr("Print"), this, SLOT(doPrint()));
    ui.mainToolBar->addAction(QIcon(":/Resource/font.png"), tr("Font edit"), this, SLOT(setFont()));
    ui.mainToolBar->addAction(QIcon(":/Resource/left.png"), tr("Alignment left"), this, [&] {ui.textEdit->setAlignment(Qt::AlignLeft); });
    ui.mainToolBar->addAction(QIcon(":/Resource/centr.png"), tr("Alignment center"), this, [&] {ui.textEdit->setAlignment(Qt::AlignCenter); });
    ui.mainToolBar->addAction(QIcon(":/Resource/right.png"), tr("Alignment center"), this, [&] {ui.textEdit->setAlignment(Qt::AlignRight); });


    connect(ui.action_Open_File, SIGNAL(triggered()), SLOT(openFile()));
    connect(ui.action_Save, SIGNAL(triggered()), SLOT(saveFile()));
    connect(ui.actionEnglish, SIGNAL(triggered()), SLOT(enLanguage()));
    connect(ui.action_Russian, SIGNAL(triggered()), SLOT(ruLanguage()));
    connect(ui.action_About_SimplePad, SIGNAL(triggered()), SLOT(info()));
    connect(ui.action_Dark, SIGNAL(triggered()), SLOT(darkTheme()));
    connect(ui.action_Light, SIGNAL(triggered()), SLOT(lightTheme()));
    connect(ui.actionOpe_n_folder_as_project, SIGNAL(triggered()), SLOT(openFolder()));
    connect(treeView.get(), SIGNAL(doubleClicked(const QModelIndex &)), SLOT(selectItem(const QModelIndex &)));
    connect(ui.action_Print, SIGNAL(triggered()), SLOT(doPrint()));

//Установка русской локализации по умолчанию
    ruLanguage();
    lightTheme();

}

void SimplePad::saveFile()
{
    FileSys fs;

    fs.saveFile(ui.textEdit->toPlainText());

}

void SimplePad::openFile()
{
    FileSys fs;

    ui.textEdit->setPlainText(fs.openFile());

}

void SimplePad::info()
{
    FileSys fs;

    QMessageBox::information(nullptr, tr("Info"), fs.loadFile(":/Resource/info.txt"));

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
    FileSys fs;

    this->setStyleSheet(fs.loadFile(":/Resource/dark.qss"));
}

void SimplePad::openFolder()
{
    QString str = QFileDialog::getExistingDirectory(this, tr("Select folder"), "", QFileDialog::ShowDirsOnly);
    model->setRootPath(QDir::currentPath());
    treeView->setRootIndex(model->index(str));

    for (int i = 1; i < model->columnCount(); ++i)
        treeView->hideColumn(i);

    treeView->setHeaderHidden(true);
    treeView->show();

}

void SimplePad::selectItem(const QModelIndex &index)
{
    QString str = model->filePath(index);

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

