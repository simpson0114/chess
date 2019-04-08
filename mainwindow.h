#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent*);

signals:
    void keyQPressed();
    void keyZPressed();

private slots:
    void nextPic();
    void prevPic();
    void moveUpPic();
    void moveDownPic();

private:
    Ui::MainWindow *ui;

    // to use graphicsview, you'll need a scene.
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;
    // QList is pretty much a vector
    QList<QPixmap> pics;
    int picIndex = 0;
};

#endif // MAINWINDOW_H
