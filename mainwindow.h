#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QKeyEvent>

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

private slots:
    void nextPic();
    void prevPic();

private:
    Ui::MainWindow *ui;

    // to use graphicsview, you'll need a scene.
    QGraphicsScene *scene;
    // QList is pretty much a vector
    QList<QPixmap> pics;
    int picIndex = 0;
};

#endif // MAINWINDOW_H
