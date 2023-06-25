#include "Poly.h"

Poly::Poly()
{
}

Poly::~Poly()
{
}


//��һ����̬�������������εĶ��㣬���ͼ��ѡ�����Σ�������򽫶������
void Poly::Draw(QPainter& painter)
{
    QPolygon polygon(points_.size());
    for(int i = 0; i < points_.size(); ++i)
    {
        polygon.setPoint(i, *points_[i]);
    }
    //���û���
    painter.setPen(QPen(color,width));
    painter.setBrush(brush);
    painter.drawPolygon(polygon);
}

void Poly::Push(QPoint *p)
{
    points_.push_back(p);
}

QPoint *Poly::top()
{
    return points_.back();
}

