#ifndef BUTTOM_H
#define BUTTOM_H

#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

class Button : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    Button(QString name, int width = 200, int heigh = 80, int size = 30);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    QGraphicsRectItem *rect;
    QGraphicsTextItem *text;
};

#endif // BUTTOM_H
