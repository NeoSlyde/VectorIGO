#include "mainwindow.h"
#include "qdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), colorPickerFill(new QDialog([&](int h, int s, int l) {
    qDebug() << "TEST";
    auto str = std::string("background-color: hsl(") + std::to_string(h) + "," + std::to_string(s) + "," + std::to_string(l)+ ");";
    _fillChoose->setStyleSheet(QString(str.c_str()));
    colorPickerFill->close();
})),
      colorPickerStroke(new QDialog([&](int h, int s, int l) {
          qDebug() << "TEST";
          auto str = std::string("background-color: hsl(") + std::to_string(h) + "," + std::to_string(s) + "," + std::to_string(l)+ ");";
          _strokeChoose->setStyleSheet(QString(str.c_str()));
          colorPickerStroke->close();
      }))
{
    setupUi(this);

    connect(_fillChoose, &QPushButton::clicked, this, &MainWindow::openColorPickerFill);
    connect(_strokeChoose, &QPushButton::clicked, this, &MainWindow::openColorPickerStroke);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openColorPickerFill() {
    colorPickerFill->show();
}

void MainWindow::openColorPickerStroke() {
    colorPickerStroke->show();
}
