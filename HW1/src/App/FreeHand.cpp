#include "FreeHand.h"

FreeHand::FreeHand(QPointF s)
{
    points.push_back(s);
}

FreeHand::~FreeHand()
{
}
//ÿ������ƶ���һ���̵ܶ�ֱ�ߣ��������������ֻ�
void FreeHand::Draw(QPainter &painter)
{
    painter.setPen(QPen(color,width));
    painter.setBrush(brush);
   // painter.drawLine(start,end);
    painter.drawPolyline(points);
}

