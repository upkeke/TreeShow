#include "MyLineItem.h"
#include"MyGraphicsItem.h"
#include<QPen>
#include<QPainter>
#include<QDebug>
MyLineItem::MyLineItem(MyGraphicsItem* front, MyGraphicsItem* end, QGraphicsItem* parent) :QGraphicsLineItem{ parent },front(front), end(end)
{
	if (front == nullptr || end == nullptr)
	{
		qDebug() << "itemAtû�ҵ�ͼԪ1";
		return;
	}
		
	setZValue(this->front->zValue()-1); //���ߵ�ͼ�� ��front������
	setFlag(QGraphicsItem::ItemIsSelectable); //�߶ο�ѡ���
	//QPen(Qt::red, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
	QPen pen(Qt::red);
	pen.setWidth(2);
	setPen(pen);

}

void MyLineItem::setTwo(MyGraphicsItem* one, MyGraphicsItem* two)
{
	if (front == nullptr || end == nullptr)
		qDebug() << "itemAtû�ҵ�ͼԪ2";
	front = one;
	end = two;
}

//https://blog.csdn.net/qq_32046111/article/details/121565965
//https://blog.csdn.net/Fallinlove520/article/details/105727096
void MyLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (front->collidesWithItem(end))
		return;
	painter->setPen(this->pen());
	painter->drawLine(front->pos(), end->pos());
}



