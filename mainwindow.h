#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void openColorPickerFill();
    void openColorPickerStroke();
private:
    std::unique_ptr<QDialog> colorPickerFill;
    std::unique_ptr<QDialog> colorPickerStroke;
};
#endif // MAINWINDOW_H
