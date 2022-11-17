#pragma once

#include <QGraphicsItem>

class MyGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MyGraphicsItem(const QPointF& pos, const QString& txt, const QPixmap &pix,
        QGraphicsItem* parent = nullptr);

    void setText(const QString& str);

private:
    QString txt;
    QPointF lt; 
    QPixmap pix;


signals:


    // QGraphicsItem interface
public:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
    QRectF boundingRect() const;
    void setPix(const QPixmap& p);
};

