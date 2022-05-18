#include"MyPaint.h"

MyPaint::MyPaint(QMainWindow* parent) : QMainWindow(parent)
{
}

void MyPaint::paintEvent(QPaintEvent* event)
{
    QPointF points[] = {
        QPointF(340, 10),
        QPointF(290,110),
        QPointF(390,110)
    };

    QPen pen(Qt::red, 3, Qt::SolidLine);
    QPainterPath star;
    qp.begin(this);
    qp.setPen(pen);
    

    if (countLftBtn)
    {
        switch (countLftBtn)
        {
        case 3:     
            qp.drawPolygon(points, sizeof(points) / sizeof(points[0]));     
        case 2:
            qp.drawEllipse(150, 10, 100, 100);
        case 1:
            qp.drawRect(10, 10, 100, 100);

        }
    }

    qp.end();
}

void MyPaint::mousePressEvent(QMouseEvent* pe)
{
    if (pe->button() == Qt::LeftButton)
    {
        if (countLftBtn < 3)
            ++countLftBtn;
        //else if (countLftBtn == 3)
        //{
        //    countLftBtn = 1;
        //    ++countIter;
        //}
    }
    this->repaint();
}