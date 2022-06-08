#include"MyPaint.h"

MyPaint::MyPaint(QMainWindow* parent)
    : QMainWindow(parent)
{
    srand(time(0));
}

void MyPaint::paintEvent(QPaintEvent* event)
{
    qp.begin(this);
    
    if (!vec.empty())
    {
        for (int i = 0; i < vec.size(); ++i)
        {
            qp.setPen(vec[i].pen);
            switch (vec[i].m_shapes)
            {
            case shapes::RECT:
                qp.drawRect(vec[i].pnt.x(), vec[i].pnt.y(), 100, 100);          
                break;

            case shapes::ELLIPSE:
                qp.drawEllipse(vec[i].pnt.x(), vec[i].pnt.y(), 100, 100);
                break;

            case shapes::RECTANGLE:
                qp.drawPolygon(vec[i].rectangle, sizeof(vec[i].rectangle) / sizeof(vec[i].rectangle[0]));
                break;
            }
        }
    }

    qp.end();
}

void MyPaint::mousePressEvent(QMouseEvent* pe)
{
    if (pe->button() == Qt::LeftButton)
    {
        szScreen = this->size();
        if ((shape.pnt.x() + 100) > szScreen.width())
        {
            endLine.push_back(shape.pnt.x());
            shape.pnt.setX(10);
            shape.pnt.setY(shape.pnt.y() + 120);
        }

        shape.setFwdRectangle();
        shape.m_shapes = static_cast<shapes>(++countLftBtn);

        QColor clr(rand() % 256, rand() % 256, rand() % 256);
        QPen pen(clr, 3, Qt::SolidLine);
        shape.pen = pen;
        vec.push_back(shape);
        shape.pnt.setX(shape.pnt.x() + 120);
        

        if (countLftBtn == 3)
            countLftBtn = 0;

    }
    else if (pe->button() == Qt::RightButton)
    {
        if (!vec.empty())
        {
            vec.pop_back();
            if (shape.pnt.x() - 120 < 0)
            {
                shape.pnt.setX(endLine.back() - 120);
                endLine.pop_back();
                shape.pnt.setY(shape.pnt.y() - 120);
            }
            else
                shape.pnt.setX(shape.pnt.x() - 120);

            shape.setFwdRectangle();
        }
    }

    this->repaint();
}