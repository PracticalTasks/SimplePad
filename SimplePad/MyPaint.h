#pragma once
#include"SimplePad.h"
#include<iostream>
#include<ctime>
#include"Shape.h"



class MyPaint : public QMainWindow
{
public:
    MyPaint(QMainWindow* parent = nullptr);

private:
    QPainter qp;
    int countLftBtn = 0;
    QSize szScreen;
    std::vector<int> endLine;
    Shape shape;
    std::vector<Shape> vec;
    

protected:
    void paintEvent(QPaintEvent* event)override;
    void mousePressEvent(QMouseEvent* pe) override;
};