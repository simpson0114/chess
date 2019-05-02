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
#include <QObject>
#include "tile.h"

class Chess: public QGraphicsView {
    Q_OBJECT
public:
    Chess();

public slots:
    void mousePress(QPoint ipt);

private:

    QGraphicsScene *scene;
    static const int N = 8;
    Tile *tile[N][N];
};



#endif // CHESS_H
