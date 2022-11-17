#include "MyLineItem.h"
#include"MyGraphicsItem.h"
#include<QPen>
#include<QPainter>
MyLineItem::MyLineItem(MyGraphicsItem* front, MyGraphicsItem* end, QGraphicsItem* parent = nullptr) :QGraphicsLineItem{ parent },front(front), end(end)
{
	setZValue(front->zValue()-1); //让线的图层在 front的下面
	setFlag(QGraphicsItem::ItemIsSelectable); //线段可选择的
	//QPen(Qt::red, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
	QPen pen(Qt::red);
	pen.setWidth(2);
	setPen(pen);

}

void MyLineItem::setTwo(MyGraphicsItem* one, MyGraphicsItem* two)
{
	front = one;
	end = two;
}

void MyLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (front->collidesWithItem(end))
		return;
	painter->setPen(this->pen());
	painter->drawLine(front->pos(), end->pos());
}


