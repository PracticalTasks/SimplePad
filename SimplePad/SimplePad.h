#pragma once

#include<QtWidgets>
#include<QTranslator>
#include<QPrinter>
#include<QPrintDialog>
#include "ui_SimplePad.h"
#include "MyPaint.h"
#include "SearchWdg.h"


class MyPaint;
class SearchWdg;

class SimplePad : public QMainWindow
{
    Q_OBJECT

public:
    SimplePad(QMainWindow *parent = Q_NULLPTR);
    ~SimplePad();

private:
    Ui::SimplePadClass ui;

    QTranslator translator;
    QStyle* style = nullptr;
    QFileSystemModel* model = nullptr;
    MyPaint* paintWnd = nullptr;
    std::unique_ptr<SearchWdg> searchWdg;

    QString strValidPath = QDir::currentPath();
    std::vector<SearchWdg*> arrDeletePtr;

    void setIndex(const QString &str);

signals:
    void startSearch(QString &validPath);

private slots:
    void saveFile();
    void openFile();
    void info();
    void enLanguage();
    void ruLanguage();
    void darkTheme();
    void lightTheme();
    void openFolder();
    void selectItem(const QModelIndex&);
    void doPrint();
    void setFont();
    void paintShapes();
    void dateAndTime();
    void setPath();
    void expandedPath(const QModelIndex &);
    void collapsedPath(const QModelIndex&);
    void findFile();

protected:
    void keyPressEvent(QKeyEvent* pe) override;
};
