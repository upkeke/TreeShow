#pragma once

#include <QGraphicsItem>
#include <vector>
using std::vector;
class MyLineItem;
class MyGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //https://blog.csdn.net/kenfan1647/article/details/116991074
    explicit MyGraphicsItem(const QPointF& pos, int val, const QPixmap &pix,
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


signals:


    // QGraphicsItem interface
public:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
    QRectF boundingRect() const override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;
    void setPix(const QPixmap& p);
};

