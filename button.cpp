#include "button.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>
#include <QFont>

Button::Button(QString name, int width, int height, int size) {
    setAcceptHoverEvents(true);
    rect = new QGraphicsRectItem();
    rect->setRect(0, 0, width, height);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(5);
    rect->setPen(pen);
    rect->setBrush(Qt::black);

    text = new QGraphicsTextItem();
    text->setPlainText(name);
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("", size));
    double xPos = width / 2 - text->boundingRect().width() / 2;
    double yPos = height / 2 - text->boundingRect().height() / 2;
    text->setPos(xPos, yPos);


    addToGroup(rect);
    addToGroup(text);

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    rect->setBrush(Qt::gray);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    rect->setBrush(Qt::black);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}
