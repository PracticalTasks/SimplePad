#pragma once
#include"SimplePad.h"


class MyPaint : public QMainWindow
{
public:
    MyPaint(QMainWindow* parent = nullptr);

private:
    QPainter qp;
    int countLftBtn = 0;
    //int countIter = 1;

protected:
    void paintEvent(QPaintEvent* event)override;
    void mousePressEvent(QMouseEvent* pe) override;
};