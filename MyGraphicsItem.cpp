#include "MyGraphicsItem.h"
#include <QGraphicsScene>
#include<QPainter>
#include "MyLineItem.h"
#include <QString>
MyGraphicsItem::MyGraphicsItem(const QPointF& pos, int val, const QPixmap& pix,
    QGraphicsItem* parent) :QGraphicsItem{ parent },  val(val),pix(pix)
    
{

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    int x = pix.width() / 2;
    int y = pix.height() / 2;
    lt = QPointF(-x, -y);
    setPos(pos);

    //pix = QPixmap(R"(E:\C++\TreeShow\img\fang1.png)"); 
}
void MyGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    painter->drawPixmap(lt, pix); //¸ß¶È 30 
    QFont font("Î¢ÈíÑÅºÚ", 15);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(val));
}

void MyGraphicsItem::setVal(int num)
{
    val = num;
    show();
}

int MyGraphicsItem::getVal()
{
    return val;
}

void MyGraphicsItem::addLine(MyLineItem* line)
{
    lineArry.push_back(line);
}

int MyGraphicsItem::reMoveLines()
{
    int re = lineArry.size();
    for (auto line : lineArry)
    {
        line->hide();
    }
    lineArry.clear();
    return re;
}

void MyGraphicsItem::clearLines()
{
    lineArry.clear();
}

QRectF MyGraphicsItem::boundingRect() const
{
    return QRectF(lt, QSizeF(pix.width(), pix.height()));
}

void MyGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);
    if (this->isSelected())
        this->scene()->update();
}

void MyGraphicsItem::setPix(const QPixmap& p)
{
    pix = p;
    show();
}

