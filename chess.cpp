#include "chess.h"
#include <QDebug>

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
            tile[i][j]->setLoc(QPoint(i, j));
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
            connect(tile[i][j], SIGNAL(clicked(QPoint)), this, SLOT(mousePress(QPoint)));
        }
    }
    lastpos = NONE;
}

void Chess::mousePress(QPoint ipt) {
    QString chess_type;
    if (lastpos == NONE) {
        chess_type = tile[ipt.x()][ipt.y()]->getType();
        if(chess_type == "wp") {
            if((ipt.x()+1) < 8) {
                if(ipt.x() == 1) {
                    if(tile[2][ipt.y()]->getType() == nullptr && tile[3][ipt.y()]->getType() == nullptr) {
                        tile[2][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(2,ipt.y()));
                        tile[3][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(3,ipt.y()));
                    }
                    else if(tile[3][ipt.y()]->getType() == nullptr) {
                        tile[3][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(3,ipt.y()));
                    }
                }
                else if(tile[ipt.x()+1][ipt.y()]->getType() == nullptr){
                    tile[ipt.x()+1][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1,ipt.y()));
                }
            }
            if((ipt.x()+1) < 8 && (ipt.y()-1) >= 0) {
                if(tile[ipt.x()+1][ipt.y()-1]->getType()[0] == "b"){
                    tile[ipt.x()+1][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1,ipt.y()-1));
                }
            }
            if((ipt.x()+1) < 8 && (ipt.y()+1) < 8) {
                if(tile[ipt.x()+1][ipt.y()+1]->getType()[0] == "b") {
                    tile[ipt.x()+1][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1,ipt.y()+1));
                }
            }
        }
        else if(chess_type == "bp") {
            if((ipt.x()-1) >= 0) {
                if(ipt.x() == 6) {
                    if(tile[4][ipt.y()]->getType() == nullptr && tile[5][ipt.y()]->getType() == nullptr) {
                        tile[4][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(4,ipt.y()));
                        tile[5][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(5,ipt.y()));
                    }
                    else if(tile[5][ipt.y()]->getType() == nullptr){
                        tile[5][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(5,ipt.y()));
                    }
                }
                else if(tile[ipt.x()-1][ipt.y()]->getType() == nullptr){
                    tile[ipt.x()-1][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1,ipt.y()));
                }
            }
            if((ipt.x()-1) >= 0 && (ipt.y()-1) >=0){
                if(tile[ipt.x()-1][ipt.y()-1]->getType()[0] == "w") {
                    tile[ipt.x()-1][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1,ipt.y()-1));
                }
            }
            if((ipt.x()-1) >= 0 && (ipt.y()+1) < 8){
                if(tile[ipt.x()-1][ipt.y()+1]->getType()[0] == "w") {
                    tile[ipt.x()-1][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1,ipt.y()+1));
                }
            }
        }
        else if(chess_type == "wr") {
            for(int i = 1; (ipt.x()-i) >= 0; i++) {
                if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i,ipt.y()));
                    if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; (ipt.x()+i) < 8; i++) {
                if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i,ipt.y()));
                    if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; (ipt.y()-i) >= 0; i++) {
                if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()-i));
                    if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; (ipt.y()+i) < 8; i++) {
                if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()+i));
                    if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "b")
                        break;
                }
            }
        }
        else if(chess_type == "br") {
            for(int i = 1; (ipt.x()-i) >= 0; i++) {
                if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i,ipt.y()));
                    if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; (ipt.x()+i) < 8; i++) {
                if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i,ipt.y()));
                    if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; (ipt.y()-i) >= 0; i++) {
                if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()-i));
                    if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; (ipt.y()+i) < 8; i++) {
                if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()+i));
                    if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "w")
                        break;
                }
            }
        }
        else if(chess_type == "wn") {
            if(ipt.x()-1 >= 0 && ipt.y()-2 >= 0) {
                if(tile[ipt.x()-1][ipt.y()-2]->getType()[0] != "w") {
                    tile[ipt.x()-1][ipt.y()-2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1, ipt.y()-2));
                }
            }
            if(ipt.x()-2 >= 0 && ipt.y()-1 >= 0) {
                if(tile[ipt.x()-2][ipt.y()-1]->getType()[0] != "w") {
                    tile[ipt.x()-2][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-2, ipt.y()-1));
                }
            }
            if(ipt.x()+1 < 8 && ipt.y()-2 >= 0) {
                if(tile[ipt.x()+1][ipt.y()-2]->getType()[0] != "w") {
                    tile[ipt.x()+1][ipt.y()-2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1, ipt.y()-2));
                }
            }
            if(ipt.x()-2 >= 0 && ipt.y()+1 < 8) {
                if(tile[ipt.x()-2][ipt.y()+1]->getType()[0] != "w") {
                    tile[ipt.x()-2][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-2, ipt.y()+1));
                }
            }
            if(ipt.x()+2 < 8 && ipt.y()-1 >= 0) {
                if(tile[ipt.x()+2][ipt.y()-1]->getType()[0] != "w") {
                    tile[ipt.x()+2][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+2, ipt.y()-1));
                }
            }
            if(ipt.x()-1 >= 0 && ipt.y()+2 < 8) {
                if(tile[ipt.x()-1][ipt.y()+2]->getType()[0] != "w") {
                    tile[ipt.x()-1][ipt.y()+2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1, ipt.y()+2));
                }
            }
            if(ipt.x()+1 < 8 && ipt.y()+2 < 8) {
                if(tile[ipt.x()+1][ipt.y()+2]->getType()[0] != "w") {
                    tile[ipt.x()+1][ipt.y()+2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1, ipt.y()+2));
                }
            }
            if(ipt.x()+2 < 8 && ipt.y()+1 < 8) {
                if(tile[ipt.x()+2][ipt.y()+1]->getType()[0] != "w") {
                    tile[ipt.x()+2][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+2, ipt.y()+1));
                }
            }
        }
        else if(chess_type == "bn") {
            if(ipt.x()-1 >= 0 && ipt.y()-2 >= 0) {
                if(tile[ipt.x()-1][ipt.y()-2]->getType()[0] != "b") {
                    tile[ipt.x()-1][ipt.y()-2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1, ipt.y()-2));
                }
            }
            if(ipt.x()-2 >= 0 && ipt.y()-1 >= 0) {
                if(tile[ipt.x()-2][ipt.y()-1]->getType()[0] != "b") {
                    tile[ipt.x()-2][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-2, ipt.y()-1));
                }
            }
            if(ipt.x()+1 < 8 && ipt.y()-2 >= 0) {
                if(tile[ipt.x()+1][ipt.y()-2]->getType()[0] != "b") {
                    tile[ipt.x()+1][ipt.y()-2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1, ipt.y()-2));
                }
            }
            if(ipt.x()-2 >= 0 && ipt.y()+1 < 8) {
                if(tile[ipt.x()-2][ipt.y()+1]->getType()[0] != "b") {
                    tile[ipt.x()-2][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-2, ipt.y()+1));
                }
            }
            if(ipt.x()+2 < 8 && ipt.y()-1 >= 0) {
                if(tile[ipt.x()+2][ipt.y()-1]->getType()[0] != "b") {
                    tile[ipt.x()+2][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+2, ipt.y()-1));
                }
            }
            if(ipt.x()-1 >= 0 && ipt.y()+2 < 8) {
                if(tile[ipt.x()-1][ipt.y()+2]->getType()[0] != "b") {
                    tile[ipt.x()-1][ipt.y()+2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1, ipt.y()+2));
                }
            }
            if(ipt.x()+1 < 8 && ipt.y()+2 < 8) {
                if(tile[ipt.x()+1][ipt.y()+2]->getType()[0] != "b") {
                    tile[ipt.x()+1][ipt.y()+2]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1, ipt.y()+2));
                }
            }
            if(ipt.x()+2 < 8 && ipt.y()+1 < 8) {
                if(tile[ipt.x()+2][ipt.y()+1]->getType()[0] != "b") {
                    tile[ipt.x()+2][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+2, ipt.y()+1));
                }
            }
        }
        else if(chess_type == "wb") {
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()-i));
                    if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()+i));
                    if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()-i));
                    if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()+i));
                    if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "b")
                        break;
                }
            }
        }
        else if(chess_type == "bb") {
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()-i));
                    if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()+i));
                    if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()-i));
                    if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()+i));
                    if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "w")
                        break;
                }
            }
        }
        else if(chess_type == "wq") {
            for(int i = 1; (ipt.x()-i) >= 0; i++) {
                if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i,ipt.y()));
                    if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; (ipt.x()+i) < 8; i++) {
                if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i,ipt.y()));
                    if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; (ipt.y()-i) >= 0; i++) {
                if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()-i));
                    if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; (ipt.y()+i) < 8; i++) {
                if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()+i));
                    if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()-i));
                    if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()+i));
                    if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()-i));
                    if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "b")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "w")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()+i));
                    if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "b")
                        break;
                }
            }
        }
        else if(chess_type == "bq") {
            for(int i = 1; (ipt.x()-i) >= 0; i++) {
                if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i,ipt.y()));
                    if(tile[ipt.x()-i][ipt.y()]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; (ipt.x()+i) < 8; i++) {
                if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i,ipt.y()));
                    if(tile[ipt.x()+i][ipt.y()]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; (ipt.y()-i) >= 0; i++) {
                if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()-i));
                    if(tile[ipt.x()][ipt.y()-i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; (ipt.y()+i) < 8; i++) {
                if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()+i));
                    if(tile[ipt.x()][ipt.y()+i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()-i));
                    if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() - i) >= 0) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()-i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-i, ipt.y()+i));
                    if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() - i) >= 0); i++) {
                if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()-i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()-i));
                    if(tile[ipt.x()+i][ipt.y()-i]->getType()[0] == "w")
                        break;
                }
            }
            for(int i = 1; ((ipt.x() + i) < 8) && ((ipt.y() + i) < 8); i++) {
                if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "b")
                    break;
                else {
                    tile[ipt.x()+i][ipt.y()+i]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+i, ipt.y()+i));
                    if(tile[ipt.x()+i][ipt.y()+i]->getType()[0] == "w")
                        break;
                }
            }
        }
        else if(chess_type == "wk") {
            if(ipt.x()-1 >= 0){
                if(tile[ipt.x()-1][ipt.y()]->getType()[0] != "w") {
                    tile[ipt.x()-1][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1,ipt.y()));
                }
            }
            if(ipt.x()+1 < 8){
                if(tile[ipt.x()+1][ipt.y()]->getType()[0] != "w") {
                    tile[ipt.x()+1][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1,ipt.y()));
                }
            }
            if(ipt.y()-1 >= 0){
                if(tile[ipt.x()][ipt.y()-1]->getType()[0] != "w") {
                    tile[ipt.x()][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()-1));
                }
            }
            if(ipt.y()+1 < 8){
                if(tile[ipt.x()][ipt.y()+1]->getType()[0] != "w") {
                    tile[ipt.x()][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()+1));
                }
            }
        }
        else if(chess_type == "bk") {
            if(ipt.x()-1 >= 0) {
                if(tile[ipt.x()-1][ipt.y()]->getType()[0] != "b") {
                    tile[ipt.x()-1][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()-1,ipt.y()));
                }
            }
            if(ipt.x()+1 < 8) {
                if(tile[ipt.x()+1][ipt.y()]->getType()[0] != "b") {
                    tile[ipt.x()+1][ipt.y()]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x()+1,ipt.y()));
                }
            }
            if(ipt.y()-1 >= 0){
                if(tile[ipt.x()][ipt.y()-1]->getType()[0] != "b") {
                    tile[ipt.x()][ipt.y()-1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()-1));
                }
            }
            if(ipt.y()+1 < 8){
                if(tile[ipt.x()][ipt.y()+1]->getType()[0] != "b") {
                    tile[ipt.x()][ipt.y()+1]->setPressColor(true);
                    Valid.push_back(QPoint(ipt.x(),ipt.y()+1));
                }
            }
        }
        lastpos = ipt;
    }
    else {
        bool flag = false;
        foreach(QPoint i, Valid) {
            if(i == QPoint(ipt.x(), ipt.y())) {
                tile[lastpos.x()][lastpos.y()]->hidePic();
                tile[ipt.x()][ipt.y()]->setType(tile[lastpos.x()][lastpos.y()]->getType());
                tile[ipt.x()][ipt.y()]->showPic();
                tile[lastpos.x()][lastpos.y()]->setType(nullptr);
                lastpos = NONE;
                break;
            }
        }
        if (!flag) {
            lastpos = NONE;
        }
        Valid.clear();
    }
    qDebug() << lastpos << ipt;

        



}
