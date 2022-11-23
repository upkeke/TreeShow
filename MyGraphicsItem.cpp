#include "MyGraphicsItem.h"
#include <QGraphicsScene>
#include<QPainter>
#include "MyLineItem.h"
#include <QString>

namespace
{
	QString getPixFile(const NodeColor &pix_c)
	{
		QString str;
		switch (pix_c)
		{
		case NodeColor::yellow:
			str = "yellow";
			break;
		case NodeColor::red:
			str = "red";
			break;
		case NodeColor::black:
			str = "black";
			break;
		default:
			break;
		}
		return QString("E:/C++/TreeShow/img/%1.jpg").arg(str);
	}
}

MyGraphicsItem::MyGraphicsItem(const QPointF& pos, int val, NodeColor pix_c, QGraphicsItem* parent) :QGraphicsItem{ parent }, val(val), pen(Qt::black), color(pix_c)
    
{
	pix.load("E:/C++/TreeShow/img/yellow.jpg");
	pix = pix.scaledToHeight(30);

    // 红黑树和 平衡树的底图不一样，在上面写数字用的颜色有差别
    if (pix_c == NodeColor::black)
        this->pen.setColor(Qt::white);
    //else
    //    pen.setColor(Qt::black);

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
	if (color == NodeColor::green || color == NodeColor::yellow)
	{
		painter->drawPixmap(lt, pix); //高度 30 
	}
    else
    {
        if (color == NodeColor::red)
        {
			painter->setBrush(Qt::red);
        }
        else
        {
            painter->setBrush(Qt::black);
        }

		//painter->drawEllipse(boundingRect());
		painter->drawEllipse(QPoint(0,0),15,15);
    }
    QFont font("微软雅黑", 15);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(val));
}

void MyGraphicsItem::setVal(int num)
{
    val = num;
    //show();
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

void MyGraphicsItem::setBackColor(NodeColor ncolor)
{
	color = ncolor;

    if (color == NodeColor::green || color == NodeColor::yellow)
    {
		pix.load(getPixFile(ncolor));
		pix = pix.scaledToHeight(30);
    }
    
    if(color == NodeColor::black)
        this->pen.setColor(Qt::white);
    else
        this->pen.setColor(Qt::black);

}

