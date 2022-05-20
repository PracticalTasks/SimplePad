#pragma once
#include"SimplePad.h"
#include<iostream>
#include<ctime>


enum class shapes
{
    EMPTY,
    RECT,
    ELLIPSE,
    RECTANGLE
};

class MyPaint : public QMainWindow
{
public:
    MyPaint(QMainWindow* parent = nullptr);

private:
    QPainter qp;
    int countLftBtn = 0;
    QSize szScreen;
    std::vector<int> endLine;

    struct Shape
    {
        shapes m_shapes = shapes::EMPTY;
        QPoint pnt = { 10, 10 };
        QPoint rectangle[3] = {
            QPoint(0, 0),
            QPoint(0, 0),
            QPoint(0, 0)
        };
        QPen pen;

        void setFwdRectangle()
        {
            rectangle[0] = { pnt.x() + 50, pnt.y()};
            rectangle[1] = { pnt.x(), pnt.y() + 100};
            rectangle[2] = { pnt.x() + 100, pnt.y() +100 };
        }

    }shape;

    std::vector<Shape> vec;
    

protected:
    void paintEvent(QPaintEvent* event)override;
    void mousePressEvent(QMouseEvent* pe) override;
};