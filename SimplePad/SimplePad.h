#pragma once

#include <QtWidgets>
#include <QTranslator>
#include <QPrinter>
#include <QPrintDialog>
#include "ui_SimplePad.h"



class SimplePad : public QMainWindow
{
    Q_OBJECT

public:
    SimplePad(QWidget *parent = Q_NULLPTR);

private:
    Ui::SimplePadClass ui;
    QTranslator translator;
    QStyle *style;
    QToolBar* tbar = nullptr;
    QAction *acttool = nullptr;
    QTextEdit* textEdit = nullptr;

    std::unique_ptr<QTreeView> treeView;
    std::unique_ptr<QFileSystemModel> model;


private slots:
    void saveFile();
    void openFile();
    void info();
    void enLanguage();
    void ruLanguage();
    void darkTheme();
    void lightTheme();
    void selectItem(const QModelIndex&);
    void doPrint();
    void newFile();
    QTextEdit* createNewFile();
    void toolBar(QAction*);

protected:
    void keyPressEvent(QKeyEvent* pe) override;
};
