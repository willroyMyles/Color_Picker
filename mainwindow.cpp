#include "colorview.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto view = new ColorView();
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{

}
