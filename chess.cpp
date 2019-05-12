#include "chess.h"
#include <QDebug>

Chess::Chess() {
    scene = new QGraphicsScene();
    scene->setSceneRect(-100, 0, 1140, 840);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1140, 840);
    setScene(scene);

    EditButton = new Button("Edit");
    PlayButton = new Button("Play");
    ExitButton = new Button("Exit");
    Giveup = new Button("Giveup");
    EditButton->setPos(520, 260);
    PlayButton->setPos(520, 380);
    ExitButton->setPos(520, 500);
    Giveup->setPos(830, 20);
    editchess = 0;
    startgame = 0;
    blackkingnum = 1;
    whitekingnum = 1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int color_code = (i + j) % 2;
            QString type;
            tile[i][j] = new Tile(color_code);
            tile[i][j]->setLoc(QPoint(i, j));
            tile[i][j]->setPressColor(false);
            tile[i][j]->setPos(20 + 100 * j, 20 + 100 * i);
            if(i == 0 && (j == 0 || j == 7))
                type = "br";
            else if(i == 0 && (j == 1 || j == 6))
                type = "bn";
            else if(i == 0 && (j == 2 || j == 5))
                type = "bb";
            else if(i == 0 && j == 3)
                type = "bq";
            else if(i == 0 && j == 4)
                type = "bk";
            else if(i == 1)
                type = "bp";
            else if(i == 6)
                type = "wp";
            else if(i == 7 && j == 4)
                type = "wk";
            else if(i == 7 && j == 3)
                type = "wq";
            else if(i == 7 && (j == 2 || j == 5))
                type = "wb";
            else if(i == 7 && (j == 1 || j == 6))
                type = "wn";
            else if(i == 7 && (j == 0 || j == 7))
                type = "wr";
            tile[i][j]->setType(type);
            scene->addItem(tile[i][j]);
            connect(tile[i][j], SIGNAL(clicked(QPoint)), this, SLOT(mousePress(QPoint)));
        }
    }
    for(int i = 0; i < 6; i++) {
        QString type;
        chesstile[0][i] = new Tile(0);
        chesstile[1][i] = new Tile(1);
        chesstile[0][i]->setLoc(QPoint(0, i));
        chesstile[1][i]->setLoc(QPoint(1, i));
        chesstile[0][i]->setPressColor(false);
        chesstile[1][i]->setPressColor(false);
        chesstile[0][i]->setPos(-100, 120 + 100 * i);
        chesstile[1][i]->setPos(840, 120 + 100 * i);
        scene->addItem(chesstile[0][i]);
        scene->addItem(chesstile[1][i]);
        if(i == 0)
            type = "bk";
        else if(i == 1)
            type = "bq";
        else if(i == 2)
            type = "bb";
        else if(i == 3)
            type = "bn";
        else if(i == 4)
            type = "br";
        else if(i == 5)
            type = "bp";
        chesstile[0][i]->setType(type);
        if(i == 0)
            type = "wk";
        else if(i == 1)
            type = "wq";
        else if(i == 2)
            type = "wb";
        else if(i == 3)
            type = "wn";
        else if(i == 4)
            type = "wr";
        else if(i == 5)
            type = "wp";
        chesstile[1][i]->setType(type);
        chesstile[0][i]->hide();
        chesstile[1][i]->hide();
        connect(chesstile[0][i], SIGNAL(clicked(QPoint)), this, SLOT(chessEdit(QPoint)));
        connect(chesstile[1][i], SIGNAL(clicked(QPoint)), this, SLOT(chessEdit(QPoint)));
    }

    lastpos = NONE;
    lastchess = NONE;
    number = 0;
    wrc = 1;
    wlc = 1;
    brc = 1;
    blc = 1;

    cover = new QGraphicsRectItem();
    cover->setRect(-100, 0, 1140, 840);
    cover->setBrush(Qt::white);
    cover->setOpacity(0.5);
    scene->addItem(cover);

    ChessGame = new QGraphicsTextItem();
    ChessGame->setFont(QFont("", 50));
    scene->addItem(ChessGame);

    whowin = new QGraphicsTextItem();
    whowin->setFont(QFont("", 50));
    scene->addItem(whowin);
    whowin->hide();

    scene->addItem(EditButton);
    scene->addItem(PlayButton);
    scene->addItem(ExitButton);
    scene->addItem(Giveup);
    Giveup->hide();
    connect(EditButton, SIGNAL(clicked()), this, SLOT(Edit()));
    connect(PlayButton, SIGNAL(clicked()), this, SLOT(Play()));
    connect(ExitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(Giveup, SIGNAL(clicked()), this, SLOT(giveup()));
}

void Chess::Edit() {
    editchess = 1;
    EditButton->hide();
    PlayButton->setPos(830, 20);
    ExitButton->setPos(830, 740);
    cover->hide();
    ChessGame->hide();

    // chess editor
    for(int i = 0; i < 6; i++) {
        chesstile[0][i]->show();
        chesstile[1][i]->show();
    }
}

void Chess::chessEdit(QPoint ipt) {
    if(lastchess == NONE) {
        chesstile[ipt.x()][ipt.y()]->setPressColor(true);
        lastchess = ipt;
    }
    else if(lastchess != ipt) {
        chesstile[ipt.x()][ipt.y()]->setPressColor(true);
        chesstile[lastchess.x()][lastchess.y()]->setPressColor(false);
        lastchess = ipt;
    }
    else {
        chesstile[ipt.x()][ipt.y()]->setPressColor(false);
        lastchess = NONE;
    }
}

void Chess::Play() {
    editchess = 0;
    startgame = 1;
    EditButton->hide();
    PlayButton->hide();
    ExitButton->setPos(830, 740);
    Giveup->show();
    cover->hide();
    ChessGame->hide();
    for(int i = 0; i < 6; i++) {
        chesstile[0][i]->hide();
        chesstile[1][i]->hide();
    }
}

void Chess::giveup() {
    if(number % 2 == 0)
        BlackWin();
    else {
        WhiteWin();
    }
}

void Chess::mousePress(QPoint ipt) {
    QString chess_type;
    chess_type = tile[ipt.x()][ipt.y()]->getType();
    if (startgame == 1 && lastpos == NONE && ((number % 2 == 0 && chess_type[0] == "w") || (number % 2 == 1 && chess_type[0] == "b"))) {
        if(number % 2 == 0) {
            if(chess_type == "wp") {
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
                    if(tile[ipt.x()-1][ipt.y()-1]->getType()[0] == "b") {
                        tile[ipt.x()-1][ipt.y()-1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()-1,ipt.y()-1));
                    }
                }
                if((ipt.x()-1) >= 0 && (ipt.y()+1) < 8){
                    if(tile[ipt.x()-1][ipt.y()+1]->getType()[0] == "b") {
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
                    if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "w")
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
                    if(tile[ipt.x()-i][ipt.y()+i]->getType()[0] == "w")
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
            else if(chess_type == "wk") {
                if(ipt.x()-1 >= 0) {
                    if(tile[ipt.x()-1][ipt.y()]->getType()[0] != "w") {
                        tile[ipt.x()-1][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()-1,ipt.y()));
                    }
                }
                if(ipt.x()+1 < 8) {
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
                if(ipt.x()-1 >= 0 && ipt.y()-1 >= 0) {
                    if(tile[ipt.x()-1][ipt.y()-1]->getType()[0] != "w") {
                        tile[ipt.x()-1][ipt.y()-1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()-1,ipt.y()-1));
                    }
                }
                if(ipt.x()-1 >= 0 && ipt.y()+1 < 8) {
                    if(tile[ipt.x()-1][ipt.y()+1]->getType()[0] != "w") {
                        tile[ipt.x()-1][ipt.y()+1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()-1,ipt.y()+1));
                    }
                }
                if(ipt.x()+1 < 8 && ipt.y()-1 >= 0) {
                    if(tile[ipt.x()+1][ipt.y()-1]->getType()[0] != "w") {
                        tile[ipt.x()+1][ipt.y()-1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()+1,ipt.y()-1));
                    }
                }
                if(ipt.x()+1 < 8 && ipt.y()+1 < 8 ) {
                    if(tile[ipt.x()+1][ipt.y()+1]->getType()[0] != "w") {
                        tile[ipt.x()+1][ipt.y()+1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()+1,ipt.y()+1));
                    }
                }
                if(wrc == 1) {
                    for(int i = 1; ipt.y()+i < 8; i++) {
                        if(tile[ipt.x()][ipt.y()+i]->getType() == "wr") {
                            tile[ipt.x()][ipt.y()+i]->setPressColor(true);
                            Valid.push_back(QPoint(ipt.x(),ipt.y()+i));
                        }
                        else if(tile[ipt.x()][ipt.y()+i]->getType() != nullptr) {
                               break;
                        }
                    }
                }
                if(wlc == 1) {
                    for(int i = 1; ipt.y()-i >= 0; i++) {
                        if(tile[ipt.x()][ipt.y()-i]->getType() == "wr") {
                            tile[ipt.x()][ipt.y()-i]->setPressColor(true);
                            Valid.push_back(QPoint(ipt.x(),ipt.y()-i));
                        }
                        else if(tile[ipt.x()][ipt.y()-i]->getType() != nullptr) {
                               break;
                        }
                    }
                }
            }
        }
        else {
            if(chess_type == "bp") {
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
                    if(tile[ipt.x()+1][ipt.y()-1]->getType()[0] == "w"){
                        tile[ipt.x()+1][ipt.y()-1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()+1,ipt.y()-1));
                    }
                }
                if((ipt.x()+1) < 8 && (ipt.y()+1) < 8) {
                    if(tile[ipt.x()+1][ipt.y()+1]->getType()[0] == "w") {
                        tile[ipt.x()+1][ipt.y()+1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()+1,ipt.y()+1));
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
                    if(tile[ipt.x()-i][ipt.y()-i]->getType()[0] == "b")
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

            else if(chess_type == "bk") {
                if(ipt.x()-1 >= 0){
                    if(tile[ipt.x()-1][ipt.y()]->getType()[0] != "b") {
                        tile[ipt.x()-1][ipt.y()]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()-1,ipt.y()));
                    }
                }
                if(ipt.x()+1 < 8){
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
                if(ipt.x()-1 >= 0 && ipt.y()-1 >= 0) {
                    if(tile[ipt.x()-1][ipt.y()-1]->getType()[0] != "b") {
                        tile[ipt.x()-1][ipt.y()-1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()-1,ipt.y()-1));
                    }
                }
                if(ipt.x()-1 >= 0 && ipt.y()+1 < 8) {
                    if(tile[ipt.x()-1][ipt.y()+1]->getType()[0] != "b") {
                        tile[ipt.x()-1][ipt.y()+1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()-1,ipt.y()+1));
                    }
                }
                if(ipt.x()+1 < 8 && ipt.y()-1 >= 0) {
                    if(tile[ipt.x()+1][ipt.y()-1]->getType()[0] != "b") {
                        tile[ipt.x()+1][ipt.y()-1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()+1,ipt.y()-1));
                    }
                }
                if(ipt.x()+1 < 8 && ipt.y()+1 < 8) {
                    if(tile[ipt.x()+1][ipt.y()+1]->getType()[0] != "b") {
                        tile[ipt.x()+1][ipt.y()+1]->setPressColor(true);
                        Valid.push_back(QPoint(ipt.x()+1,ipt.y()+1));
                    }
                }
                if(brc == 1) {
                    for(int i = 1; ipt.y()+i < 8; i++) {
                        if(tile[ipt.x()][ipt.y()+i]->getType() == "br") {
                            tile[ipt.x()][ipt.y()+i]->setPressColor(true);
                            Valid.push_back(QPoint(ipt.x(),ipt.y()+i));
                        }
                        else if(tile[ipt.x()][ipt.y()+i]->getType() != nullptr) {
                               break;
                        }
                    }
                }
                if(blc == 1) {
                    for(int i = 1; ipt.y()-i >= 0; i++) {
                        if(tile[ipt.x()][ipt.y()-i]->getType() == "br") {
                            tile[ipt.x()][ipt.y()-i]->setPressColor(true);
                            Valid.push_back(QPoint(ipt.x(),ipt.y()-i));
                        }
                        else if(tile[ipt.x()][ipt.y()-i]->getType() != nullptr) {
                               break;
                        }
                    }
                }
            }
        }

        lastpos = ipt;
    }
    else if(editchess == 1) {
        if(lastchess == NONE) {}
        else if(chesstile[lastchess.x()][lastchess.y()]->getType() != chess_type) {
            if(tile[ipt.x()][ipt.y()]->getType() == "bk")
                blackkingnum--;
            else if(tile[ipt.x()][ipt.y()]->getType() == "wk")
                whitekingnum--;
            tile[ipt.x()][ipt.y()]->setType(chesstile[lastchess.x()][lastchess.y()]->getType());
            tile[ipt.x()][ipt.y()]->showPic();
            if(chesstile[lastchess.x()][lastchess.y()]->getType() == "bk")
                blackkingnum++;
            else if(chesstile[lastchess.x()][lastchess.y()]->getType() == "wk")
                whitekingnum++;
            if(blackkingnum == 1 && whitekingnum == 1)
                PlayButton->show();
            else
                PlayButton->hide();
        }
        else {
            if(chesstile[lastchess.x()][lastchess.y()]->getType() == "bk")
                blackkingnum--;
            else if(chesstile[lastchess.x()][lastchess.y()]->getType() == "wk")
                whitekingnum--;
            tile[ipt.x()][ipt.y()]->setType(nullptr);
            tile[ipt.x()][ipt.y()]->hidePic();
            if(blackkingnum == 1 && whitekingnum == 1)
                PlayButton->show();
            else
                PlayButton->hide();
        }
    }
    else {
        bool flag = false;
        foreach(QPoint i, Valid) {
            if(i == QPoint(ipt.x(), ipt.y())) {
                if((tile[lastpos.x()][lastpos.y()]->getType() == "bp" && i.x() == 7) || (tile[lastpos.x()][lastpos.y()]->getType() == "wp" && i.x() == 0)) {
                    tile[lastpos.x()][lastpos.y()]->hidePic();
                    if(tile[lastpos.x()][lastpos.y()]->getType()[0] == "b")
                        tile[ipt.x()][ipt.y()]->setType("bq");
                    else
                        tile[ipt.x()][ipt.y()]->setType("wq");
                    tile[ipt.x()][ipt.y()]->showPic();
                    if(tile[lastpos.x()][lastpos.y()]->getType() == "wk") {
                        WhiteWin();
                    }
                    else if(tile[lastpos.x()][lastpos.y()]->getType() == "bk") {
                        BlackWin();
                    }
                    tile[lastpos.x()][lastpos.y()]->setType(nullptr);
                    lastpos = NONE;
                    number = number + 1;
                    break;
                }
                else if(tile[lastpos.x()][lastpos.y()]->getType()[1] == "k" && tile[ipt.x()][ipt.y()]->getType()[1] == "r" && tile[lastpos.x()][lastpos.y()]->getType()[0] == tile[ipt.x()][ipt.y()]->getType()[0]) {
                    if(tile[ipt.x()][ipt.y()]->getType()[0] == "w") {
                        wrc = false;
                        wlc = false;
                    }
                    else if(tile[ipt.x()][ipt.y()]->getType()[0] == "b") {
                        brc = false;
                        blc = false;
                    }
                    if(ipt.y() == 0) {
                        tile[lastpos.x()][lastpos.y()]->hidePic();
                        tile[ipt.x()][ipt.y()]->hidePic();
                        tile[ipt.x()][2]->setType(tile[lastpos.x()][lastpos.y()]->getType());
                        tile[ipt.x()][3]->setType(tile[ipt.x()][ipt.y()]->getType());
                        tile[ipt.x()][2]->showPic();
                        tile[ipt.x()][3]->showPic();
                        tile[lastpos.x()][lastpos.y()]->setType(nullptr);
                        tile[ipt.x()][ipt.y()]->setType(nullptr);
                        lastpos = NONE;
                        number = number + 1;
                        break;
                    }
                    else if(ipt.y() == 7) {
                        tile[lastpos.x()][lastpos.y()]->hidePic();
                        tile[ipt.x()][ipt.y()]->hidePic();
                        tile[ipt.x()][6]->setType(tile[lastpos.x()][lastpos.y()]->getType());
                        tile[ipt.x()][5]->setType(tile[ipt.x()][ipt.y()]->getType());
                        tile[ipt.x()][6]->showPic();
                        tile[ipt.x()][5]->showPic();
                        tile[lastpos.x()][lastpos.y()]->setType(nullptr);
                        tile[ipt.x()][ipt.y()]->setType(nullptr);
                        lastpos = NONE;
                        number = number + 1;
                        break;
                    }
                }
                else {
                    if(tile[lastpos.x()][lastpos.y()]->getType() == "wk") {
                        wrc = false;
                        wlc = false;
                    }
                    else if(tile[lastpos.x()][lastpos.y()]->getType() == "wr") {
                        if(lastpos.y() == 0)
                            wlc = false;
                        else if(lastpos.y() == 7)
                            wrc = false;
                    }
                    else if(tile[lastpos.x()][lastpos.y()]->getType() == "bk") {
                        brc = false;
                        blc = false;
                    }
                    else if(tile[lastpos.x()][lastpos.y()]->getType() == "br") {
                        if(lastpos.y() == 0)
                            blc = false;
                        else if(lastpos.y() == 7)
                            brc = false;
                    }
                    tile[lastpos.x()][lastpos.y()]->hidePic();
                    if(tile[ipt.x()][ipt.y()]->getType() == "wk") {
                        BlackWin();
                    }
                    else if(tile[ipt.x()][ipt.y()]->getType() == "bk") {
                        WhiteWin();
                    }
                    tile[ipt.x()][ipt.y()]->setType(tile[lastpos.x()][lastpos.y()]->getType());
                    tile[ipt.x()][ipt.y()]->showPic();
                    tile[lastpos.x()][lastpos.y()]->setType(nullptr);
                    lastpos = NONE;
                    number = number + 1;
                    break;
                }
            }
        }
        foreach(QPoint i, Valid) {
            tile[i.x()][i.y()]->setPressColor(false);
        }
        if (!flag) {
            lastpos = NONE;
        }
        Valid.clear();
    }
    qDebug() << lastpos << ipt;
}

void Chess::BlackWin() {
    whowin->setPlainText("Black is win.");
    whowin->setPos(scene->width() / 2 - whowin->boundingRect().width() / 2 - 150, scene->height() / 2 - whowin->boundingRect().height() / 2);
    whowin->show();
    cover->show();
    startgame = 0;
}

void Chess::WhiteWin() {
    whowin->setPlainText("White is win.");
    whowin->setPos(scene->width() / 2 - whowin->boundingRect().width() / 2 - 150, scene->height() / 2 - whowin->boundingRect().height() / 2);
    whowin->show();
    cover->show();
    startgame = 0;
}

void Chess::Menu() {
    ChessGame->setPlainText("Chess Game");
    ChessGame->setPos(80, scene->height() / 2 - whowin->boundingRect().height() / 2);
    ChessGame->show();
}
