#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set our scene to size (750, 480)
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
    this->scene->addPixmap(pics[0]);

    // connect our slots to button's signal
    connect(ui->pushButton_next, SIGNAL(clicked()), this, SLOT(nextPic()));
    connect(ui->pushButton_prev, SIGNAL(clicked()), this, SLOT(prevPic()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_J){
        prevPic();
    }else if(event->key() == Qt::Key::Key_L){
        nextPic();
    }
}

void MainWindow::nextPic(){
    // reset scene
    scene->clear();
    // if index is out of range, start from 0
    picIndex = picIndex >= pics.size() - 1 ? 0 : picIndex + 1;
    scene->addPixmap(pics[picIndex]);
}

void MainWindow::prevPic(){
    // reset scene
    scene->clear();
    // if index is out of range, start form last
    picIndex = picIndex <= 0 ? pics.size() - 1 : picIndex - 1;
    scene->addPixmap(pics[picIndex]);
}
