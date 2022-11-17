#include "MyGraphicsItem.h"

#include<QPainter>

MyGraphicsItem::MyGraphicsItem(const QPointF& pos, const QString& txt, const QPixmap& pix,
    QGraphicsItem* parent) :QGraphicsItem{ parent },  txt(txt),pix(pix)
    
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
    painter->drawText(boundingRect(), Qt::AlignCenter, txt);
}

void MyGraphicsItem::setText(const QString& str)
{
    txt = str;
    show();
}

QRectF MyGraphicsItem::boundingRect() const
{
    return QRectF(lt, QSizeF(pix.width(), pix.height()));
}

void MyGraphicsItem::setPix(const QPixmap& p)
{
    pix = p;
    show();
}

