#include "mainwindow.h"
#include <QApplication>
#include "colorview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorView w(QColor(200,200,200));
    w.show();

    return a.exec();
}
