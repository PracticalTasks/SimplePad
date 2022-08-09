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
    
    ui.gridLayout_2->addWidget(treeView.get());
    treeView->hide();

    ui.mainToolBar->addAction(QIcon(":/Resource/open-file.png"), tr("Open"), this, SLOT(openFile()));
    ui.mainToolBar->addAction(QIcon(":/Resource/save.png"), tr("Save"), this, SLOT(saveFile()));
    ui.mainToolBar->addAction(QIcon(":/Resource/print.png"), tr("Print"), this, SLOT(doPrint()));
    ui.mainToolBar->addAction(QIcon(":/Resource/font.png"), tr("Font edit"), this, SLOT(setFont()));
    ui.mainToolBar->addAction(QIcon(":/Resource/left.png"), tr("Alignment left"), this, [&] {ui.textEdit->setAlignment(Qt::AlignLeft); });
    ui.mainToolBar->addAction(QIcon(":/Resource/centr.png"), tr("Alignment center"), this, [&] {ui.textEdit->setAlignment(Qt::AlignCenter); });
    ui.mainToolBar->addAction(QIcon(":/Resource/right.png"), tr("Alignment center"), this, [&] {ui.textEdit->setAlignment(Qt::AlignRight); });
    ui.mainToolBar->addAction(QIcon(":/Resource/paint.png"), tr("Paint shapes"), this, SLOT(paintShapes()));

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
    connect(ui.actionPaint_shapes, SIGNAL(triggered()), SLOT(paintShapes()));
//
//Установка русской локализации по умолчанию
    ruLanguage();
    lightTheme();

    paintWdg = std::make_unique<MyPaint>(this);
    paintWdg->setWindowTitle("Paint widget");

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

    //QFont font = ui.textEdit->textCursor().charFormat().font();
    //QFontDialog fntDlg(font, this);
    //bool ok;
    //font = fntDlg.getFont(&ok);
    //if (ok)
    //{
    //    QTextCharFormat fmt;
    //    fmt.setFont(font);
    //    ui.textEdit->textCursor().setCharFormat(fmt);
    //}
}

void SimplePad::paintShapes()
{
    paintWdg->show();
    paintWdg->resize(700, 400);

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
    model->setRootPath(QDir::currentPath());
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

