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
    int reMoveLines(); //与当前图元连接的直线图元全部隐藏，并返回移出的个数
    void clearLines(); //这个只是清空lineArry，但不隐藏其中的图元

private:
    int val; //图元上的数字
    QPointF lt; //左上角的坐标
    QPixmap pix; //图元的背景图片
    vector<MyLineItem*> lineArry; //与当前图元连接的图元集合
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

