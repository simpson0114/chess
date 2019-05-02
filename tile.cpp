#include "tile.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>

Tile::Tile(int color_code) {

    setAcceptHoverEvents(true);

    rect = new QGraphicsRectItem();
    pic = new QGraphicsPixmapItem();
    rect->setRect(0, 0 , width, length);
    rect->setPen(QPen(Qt::transparent));

    if (color_code)
        color.setRgb(170, 121, 95);
    else
        color.setRgb(233, 203, 176);
    rect->setBrush(color);

    addToGroup(rect);
    addToGroup(pic);
}

void Tile::setType(QString type) {
    QString tempt;
    if(type[0] == "w") {
        tempt = ":/pic/white/";
        if(type[1] == "r")
            pic->setPixmap(QPixmap(tempt + "rok.png").scaledToHeight(80));
        else if(type[1] == "n")
            pic->setPixmap(QPixmap(tempt + "knight.png").scaledToHeight(80));
        else if(type[1] == "p")
            pic->setPixmap(QPixmap(tempt + "pawn.png").scaledToHeight(80));
        else if(type[1] == "b")
            pic->setPixmap(QPixmap(tempt + "bishop.png").scaledToHeight(80));
        else if(type[1] == "q")
            pic->setPixmap(QPixmap(tempt + "queen.png").scaledToHeight(80));
        else if(type[1] == "k")
            pic->setPixmap(QPixmap(tempt + "king.png").scaledToHeight(80));
    }
    else if(type[0] == "b") {
        tempt = ":/pic/black/";
        if(type[1] == "r")
            pic->setPixmap(QPixmap(tempt + "rok.png").scaledToHeight(80));
        else if(type[1] == "n")
            pic->setPixmap(QPixmap(tempt + "knight.png").scaledToHeight(80));
        else if(type[1] == "p")
            pic->setPixmap(QPixmap(tempt + "pawn.png").scaledToHeight(80));
        else if(type[1] == "b")
            pic->setPixmap(QPixmap(tempt + "bishop.png").scaledToHeight(80));
        else if(type[1] == "q")
            pic->setPixmap(QPixmap(tempt + "queen.png").scaledToHeight(80));
        else if(type[1] == "k")
            pic->setPixmap(QPixmap(tempt + "king.png").scaledToHeight(80));
    }
    pic->setPos(rect->rect().width() / 2 - pic->boundingRect().width() / 2, rect->rect().height() / 2 - pic->boundingRect().height() / 2);
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    rect->setBrush(Qt::red);
}

void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    rect->setBrush(color);
}
