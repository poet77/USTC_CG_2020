#include "Rect.h"

Rect::Rect()
{
}

Rect::~Rect()
{
}

//Qt�Դ��Ļ����ι���
void Rect::Draw(QPainter& painter)
{
    //���û���
    painter.setPen(QPen(color,width));
    painter.setBrush(brush);
    painter.drawRect(start.x(), start.y(),
		end.x() - start.x(), end.y() - start.y());

}

