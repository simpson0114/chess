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
    void setType(QString chess_type);
    void setLoc(QPoint ipt);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setPressColor(bool ifPress);
    void hidePic();
    void showPic();
    QString getType();
    bool Valid;
signals:
    void clicked(QPoint ipt);

private:
    QString type;
    QColor color;
    QPoint pos;
    QGraphicsRectItem *rect;
    QGraphicsPixmapItem *pic;
    static const int width = 100;
    static const int length = 100;
};

#endif // TILE_H
