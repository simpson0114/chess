#ifndef CHESS_H
#define CHESS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QFont>
#include <QBrush>
#include <QObject>
#include "tile.h"
#include "button.h"

class Chess: public QGraphicsView {
    Q_OBJECT
public:
    Chess();
    void BlackWin();
    void WhiteWin();
    void Menu();

public slots:
    void Edit();
    void Play();
    void giveup();
    void mousePress(QPoint ipt);
    void chessEdit(QPoint ipt);

private:
    bool wrc;
    bool wlc;
    bool brc;
    bool blc;
    bool editchess;
    bool startgame;
    int number;
    int blackkingnum;
    int whitekingnum;
    QGraphicsScene *scene;
    QGraphicsRectItem *cover;
    QGraphicsTextItem *ChessGame;
    QGraphicsTextItem *whowin;
    static const int N = 8;
    Tile *tile[N][N];
    Tile *chesstile[2][6];
    QPoint lastpos;
    QPoint lastchess;
    QList <QPoint> Valid;
    Button *EditButton;
    Button *PlayButton;
    Button *ExitButton;
    Button *Giveup;
    const QPoint NONE = QPoint(-1, -1);
};



#endif // CHESS_H
