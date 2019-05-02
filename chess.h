#ifndef CHESS_H
#define CHESS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QFont>
#include <QBrush>
#include "tile.h"

class Chess: public QGraphicsView {
public:
    Chess();

private:

    QGraphicsScene *scene;
    static const int N = 8;
    Tile *tile[N][N];
};



#endif // CHESS_H
