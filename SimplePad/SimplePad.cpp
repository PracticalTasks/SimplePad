#include "SimplePad.h"
#include<QDir>
#include<QTextStream>

#pragma warning(disable : 4834)

SimplePad::SimplePad(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    tbar = addToolBar("ToolBar");
    tbar->addAction(QIcon(":/Resource/Newfile.png"), "New File");
    tbar->addAction(QIcon(":/Resource/open-file.png"), "Open");
    tbar->addAction(QIcon(":/Resource/open-file.png"), "Open(Read only)");
    tbar->addAction(QIcon(":/Resource/save.png"), "Save");
    tbar->addAction(QIcon(":/Resource/print.png"), "Print");

    textEdit = new QTextEdit(this);
    ui.mdiArea->addSubWindow(textEdit);
    
    connect(ui.action_New_file, SIGNAL(triggered()), SLOT(newFile()));
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
    connect(ui.action_Print, SIGNAL(triggered()), SLOT(doPrint()));
    connect(tbar, SIGNAL(actionTriggered(QAction *)), SLOT(toolBar(QAction*)));

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
                stream << textEdit->toPlainText();
                file.close();
            }
        }
    }
}

void SimplePad::openFile()
{
    QString str = QFileDialog::getOpenFileName(this, tr("Open file"),
        QDir::currentPath(), tr("Text file(*.txt);; All(*.*)"));

    //QTextEdit* textEdit = nullptr;

    //Почему то возвращает nullptr в не зависимости от активности подокон
    //QMdiSubWindow* actSubWnd = ui.mdiArea->activeSubWindow();

    //if (actSubWnd)
    //{
    //    QWidget* Wdg = actSubWnd->widget();
    //    textEdit = qobject_cast<QTextEdit*>(Wdg);
    //}
    
    
    if (str.length() > 0)
    {
        if (!str.isEmpty())
        {
            QFile file(str);
            if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
            {
                QTextStream stream(&file);
                if(textEdit)
                    textEdit->setPlainText(stream.readAll());
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

void SimplePad::doPrint()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    if (dlg.exec() == QDialog::Accepted)
        textEdit->print(&printer);
}

void SimplePad::newFile()
{
    createNewFile()->show();
}

void SimplePad::toolBar(QAction* action)
{
   
}

QTextEdit* SimplePad::createNewFile()
{
    QTextEdit* txtEdt = new QTextEdit(this);
    ui.mdiArea->addSubWindow(txtEdt);
    txtEdt->setAttribute(Qt::WA_DeleteOnClose);
    txtEdt->setWindowTitle("Unnamed Document");
    txtEdt->setWindowIcon(QPixmap(":/filenew.png"));

    return txtEdt;
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
            textEdit->clear();
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
    qApp->installTranslator(nullptr);
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
                textEdit->setPlainText(stream.readAll());
                file.close();
            }
        }
    }
}
