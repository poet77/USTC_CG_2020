#include "Elli.h"

Elli::Elli()
{
}

Elli::~Elli()
{
}
//Qt�Դ��Ļ���Բ����
void Elli::Draw(QPainter& painter)
{
    //���û���
    painter.setPen(QPen(color, width));
    painter.setBrush(brush);
    painter.drawEllipse(start.x(), start.y(),
        end.x() - start.x(), end.y() - start.y());
}

