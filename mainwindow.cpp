#include "mainwindow.h"
#include "rectangle.h"
#include <iostream>
#include <QSvgGenerator>
#include "toolmanager.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);
    scene = new VScene(this);
    scene->setSceneRect(0,0,800,800);
    graphicsView->setScene(scene);

    ToolManager* toolManager = new ToolManager();

    rect1 = new VRectangle;
    scene->addItem(rect1);
    rect1->setRect(0,0,60,90);
    rect1->setPos(100,100);
    rect1->updateGrabbersPosition();
    rect1->setTransformOriginPoint(rect1->rect().center());
    rect1->setRotation(30);

    connect(
        btn1, &QAbstractButton::clicked,
        toolManager, &ToolManager::setMouseTool
    );

    connect(
        btn2, &QAbstractButton::clicked,
        toolManager, &ToolManager::setRectangleTool
    );

    connect(
        scene, &VScene::sigmousePressEvent,
        toolManager, &ToolManager::slotMousePress
    );

    connect(
        scene, &VScene::sigmouseMoveEvent,
        toolManager, &ToolManager::slotMouseMove
    );

    connect(
        scene, &VScene::sigmouseReleaseEvent,
        toolManager, &ToolManager::slotMouseRelease
    );


//    connect(
//        btn1, &QAbstractButton::clicked,
//        this, &MainWindow::btn1Function
//    );

//    connect(
//        btn2, &QAbstractButton::clicked,
//        this, &MainWindow::btn2Function
//    );

//    connect(
//        btn3, &QAbstractButton::clicked,
//        this, &MainWindow::btn3Function
//    );


}






void MainWindow::btn1Function()
{
    //sceneToSvg();
    //rect1->setRect(0,0,250,300);
    //graphicsView->scale(1/1.5,1/1.5);
   // graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //graphicsView->resetTransform();

}

void MainWindow::btn2Function()
{
    //sceneToSvg();
    //rect1->setRect(0,0,30,30);
    //scene->setSceneRect(0,0,5000,5000);
    //graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //graphicsView->scale(2,2);
}


qreal a = 0;
void MainWindow::btn3Function()
{
    //sceneToSvg();
    //a+=5;
    //rect1->setTransformOriginPoint(rect1->rect().center());
    //rect1->setRotation(a);


}




void MainWindow::sceneToSvg()
{
    std::cout << "OUIIIIIIIII: " << std::endl;

    QSvgGenerator svgGen;
    svgGen.setFileName( "/Users/leopaul/Desktop/scene.svg" );
    svgGen.setSize(QSize(200, 200));
    svgGen.setViewBox(QRect(0, 0, 200, 200));
    svgGen.setTitle(tr("SVG Generator Example Drawing"));
    svgGen.setDescription(tr("description trop cool"));

    QPainter painter( &svgGen );

    scene->render( &painter );
}




MainWindow::~MainWindow()
{
}
