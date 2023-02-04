#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "rectangle.h"

#include "vscene.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>



class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    VScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    void sceneToSvg();

public slots:
    void saveDoc();
    void loadDoc();
    void updatePanel();
    void updateZoom(int inputZoom);
    void resetZoom();
    void btn1Function();
    void btn2Function();
    void btn3Function();

private:
    std::unique_ptr<QDialog> colorPickerFill;
    std::unique_ptr<QDialog> colorPickerStroke;
};

#endif // MAINWINDOW_H
