#include "shape.h"

Shape::Shape()
{
    start=QPoint(0,0);
    end=QPoint(0,0);
    color=Qt::black;
    width=1;
}

Shape::~Shape()
{
}

void Shape::Append(QPointF s)
{
    points << s;
}

//�趨���
void Shape::set_start(QPoint s)
{
	start = s;
}

//�趨�յ�
void Shape::set_end(QPoint e)
{
	end = e;
}


void Shape::Setshape(QPoint s, QPoint e)
{
    start = s;
    end = e;
}


//�趨��ɫ����
void Shape::set_line(QColor line_color, int line_width)
{
    color=line_color;
    width=line_width;
}

void Shape::set_brush(QBrush shape_brush)
{
    brush = shape_brush;
}


//��ȡ���
QPoint Shape::get_start()
{
    return start;
}
//��ȡ�յ�
QPoint Shape::get_end()
{
    return end;
}



