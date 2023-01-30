#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "rectangle.h"

#include "vscene.h"
#include <QMainWindow>



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
    VRectangle* rect1;
    VRectangle* rect2;
    
public slots:
    void btn1Function();
    void btn2Function();
    void btn3Function();



};

#endif // MAINWINDOW_H
