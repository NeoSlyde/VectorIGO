#include "mainwindow.h"
#include "qdialog.h"
#include <iostream>
#include <QSvgGenerator>
#include "toolmanager.h"


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
    scene = new VScene(this);
    _graphicsView->setScene(scene);

    ToolManager* toolManager = new ToolManager();


    connect(_fillChoose, &QPushButton::clicked, this, &MainWindow::openColorPickerFill);
    connect(_strokeChoose, &QPushButton::clicked, this, &MainWindow::openColorPickerStroke);
    connect(
            _mouseTool, &QAbstractButton::clicked,
            toolManager, &ToolManager::setMouseTool
        );

        connect(
            _rectangleTool, &QAbstractButton::clicked,
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


        connect(
            scene, &VScene::sigmouseReleaseEvent,
            this, &MainWindow::updatePanel
        );

        connect(
            scene, &VScene::sigmouseMoveEvent,
            this, &MainWindow::updatePanel
        );

        connect(
            scene, &VScene::sigRemoveItems,
            this, &MainWindow::updatePanel
        );
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

void MainWindow::openColorPickerFill() {
    colorPickerFill->show();
}

void MainWindow::openColorPickerStroke() {
    colorPickerStroke->show();
}




void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}


void MainWindow::updatePanel()
{
    clearLayout(_verticalLayout);

    if(scene->getSelectedShape()==NULL){
        std::cout << "pas de shape selected: " << std::endl;
        return;
    }else{
        QLayout* panel = scene->getSelectedShape()->getPanel();
        _verticalLayout->addLayout(panel);
    }
}

MainWindow::~MainWindow()
{
}

