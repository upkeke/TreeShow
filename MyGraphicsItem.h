#pragma once

#include <QGraphicsItem>
#include <vector>
using std::vector;
class MyLineItem;
#include <QPen>

#ifndef NODECOLOR
#define NODECOLOR
enum class NodeColor
{
	yellow,
	green,
	red,
	black,
};
#endif

class MyGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //https://blog.csdn.net/kenfan1647/article/details/116991074
    explicit MyGraphicsItem(const QPointF& pos, int val, NodeColor pix_c,
        QGraphicsItem* parent = nullptr);

    void setVal(int num);
    int getVal();
    void addLine(MyLineItem*);
    int reMoveLines(); //�뵱ǰͼԪ���ӵ�ֱ��ͼԪȫ�����أ��������Ƴ��ĸ���
    void clearLines(); //���ֻ�����lineArry�������������е�ͼԪ

private:
    int val; //ͼԪ�ϵ�����
    QPointF lt; //���Ͻǵ�����
    QPixmap pix; //ͼԪ�ı���ͼƬ
    vector<MyLineItem*> lineArry; //�뵱ǰͼԪ���ӵ�ͼԪ����
    QPen pen;
    NodeColor color;
     

signals:


    // QGraphicsItem interface
public:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
    QRectF boundingRect() const override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;
    void setBackColor(NodeColor pix_c);
};

