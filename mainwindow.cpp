#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set our scene size to fit graphicsView
    this->scene = new QGraphicsScene(0, 0, 750, 480);
    // set graphicsview to show our scene
    ui->graphicsView->setScene(this->scene);

    // add all the images to list pics
    pics.push_back(QPixmap(":/img/src/imageSet/1.png"));
    pics.push_back(QPixmap(":/img/src/imageSet/2.png"));
    pics.push_back(QPixmap(":/img/src/imageSet/3.png"));
    pics.push_back(QPixmap(":/img/src/imageSet/4.png"));
    pics.push_back(QPixmap(":/img/src/imageSet/5.png"));
    pics.push_back(QPixmap(":/img/src/imageSet/6.png"));

    // set default image of our scene
    // addPixmap returns a QGraphicsPixmapItem
    this->item = this->scene->addPixmap(pics[0]);

    // connect button's signal to our slots
    connect(ui->pushButton_next, SIGNAL(clicked()), this, SLOT(nextPic()));
    connect(ui->pushButton_prev, SIGNAL(clicked()), this, SLOT(prevPic()));
    // connect keyPressedSignal to our slots
    connect(this, SIGNAL(keyQPressed()), this, SLOT(moveUpPic()));
    connect(this, SIGNAL(keyZPressed()), this, SLOT(moveDownPic()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Q){
        // moveUpPic();
        emit keyQPressed();
    }else if(event->key() == Qt::Key::Key_Z){
        // moveDownPic();
        emit keyZPressed();
    }
}

void MainWindow::nextPic(){
    // reset scene
    scene->clear();
    // if index is out of range, start from 0
    picIndex = picIndex >= pics.size() - 1 ? 0 : picIndex + 1;
    item = scene->addPixmap(pics[picIndex]);
}

void MainWindow::prevPic(){
    // reset scene
    scene->clear();
    // if index is out of range, start form last of pics
    picIndex = picIndex <= 0 ? pics.size() - 1 : picIndex - 1;
    item = scene->addPixmap(pics[picIndex]);
}

void MainWindow::moveUpPic(){
    // you can directly manipulate QGraphicsPixmapItem
    // in scene, your item will automatically refresh
    item->setPos(item->x(), item->y() - 1);
}

void MainWindow::moveDownPic(){
    // in computer, mostly, positive Y-axis is pointed downward
    item->setPos(item->x(), item->y() + 1);
}
