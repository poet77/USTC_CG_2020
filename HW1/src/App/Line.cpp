#include "Line.h"

Line::Line()
{
}

Line::~Line()
{
}
//����Qt�Դ��Ļ�ֱ�߹���
void Line::Draw(QPainter& painter)
{
    //���û���
    painter.setPen(QPen(color,width));
    painter.setBrush(brush);
    painter.drawLine(start, end);
}
