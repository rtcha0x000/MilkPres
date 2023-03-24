#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pix(":/new/pics/TeaPres.png");
    QSplashScreen *sp=new QSplashScreen(pix);
    sp->show();
    MainWindow w;
    w.show();
    sp->finish(&w);
    return a.exec();
}
