#pragma once
#include<QGraphicsLineItem>
class MyGraphicsItem;


//coordinate
class MyLineItem:public QGraphicsLineItem 
{
public:
	MyLineItem(MyGraphicsItem* front, MyGraphicsItem* end, QGraphicsItem* parent);
	void setTwo(MyGraphicsItem*, MyGraphicsItem*);
private:
	MyGraphicsItem* front;
	MyGraphicsItem* end;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};
