#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QPixmap>
#include <QGraphicsItemGroup>
#include <QColor>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

class Tile : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:

    Tile(int color_code);
    void setType(QString type);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();

private:
    QColor color;
    QGraphicsRectItem *rect;
    QGraphicsPixmapItem *pic;
    static const int width = 100;
    static const int length = 100;
};

#endif // TILE_H
