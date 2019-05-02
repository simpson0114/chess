#include <QApplication>
#include "chess.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   Chess *chess = new Chess();
   chess->show();

   return a.exec();
}
