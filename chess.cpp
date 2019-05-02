#include "chess.h"

Chess::Chess() {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 840, 840);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(840, 840);
    setScene(scene);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int color_code = (i + j) % 2;
            QString type;
            tile[i][j] = new Tile(color_code);
            tile[i][j]->setPos(20 + 100 * j, 20 + 100 * i);
            if(i == 0 && (j == 0 || j == 7))
                type = "wr";
            else if(i == 0 && (j == 1 || j == 6))
                type = "wn";
            else if(i == 0 && (j == 2 || j == 5))
                type = "wb";
            else if(i == 0 && j == 3)
                type = "wq";
            else if(i == 0 && j == 4)
                type = "wk";
            else if(i == 1)
                type = "wp";
            else if(i == 6)
                type = "bp";
            else if(i == 7 && j == 4)
                type = "bk";
            else if(i == 7 && j == 3)
                type = "bq";
            else if(i == 7 && (j == 2 || j == 5))
                type = "bb";
            else if(i == 7 && (j == 1 || j == 6))
                type = "bn";
            else if(i == 7 && (j == 0 || j == 7))
                type = "br";
            tile[i][j]->setType(type);
            scene->addItem(tile[i][j]);
        }
    }
}
