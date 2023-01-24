#include "mainwindow.h"
#include "qdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), colorPicker(new QDialog([&](int h, int s, int v) {
    qDebug() << "TEST";
    auto str = std::string("background-color: hsl(") + std::to_string(h) + "," + std::to_string(s) + "," + std::to_string(v)+ ");";
    _fillChoose->setStyleSheet(QString(str.c_str()));
    colorPicker->close();
}))
{
    setupUi(this);

    connect(_fillChoose, &QPushButton::clicked, this, &MainWindow::openColorPicker);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openColorPicker() {
    colorPicker->show();
}
