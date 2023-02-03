#include "mainwindow.h"
#include "qdialog.h"
#include <iostream>
#include "ellipse.h"
#include <QSvgGenerator>
#include "toolmanager.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    _panel->setVisible(false);
    setWindowTitle(QString("VectorIGO"));
    _rectangleTool->setIcon(QIcon(":/ressources/form_square.png"));
    _mouseTool->setIcon(QIcon(":/ressources/pencil.png"));
    _textTool->setIcon(QIcon(":/ressources/text.png"));
    _courbeTool->setIcon(QIcon(":/ressources/pen.png"));
    _undo->setIcon(QIcon(":/ressources/undo.png"));
    _redo->setIcon(QIcon(":/ressources/redo.png"));
    _ellipseTool->setIcon(QIcon(":/ressources/ellipse.png"));



    _groupBox_2->setStyleSheet("QGroupBox {border: 1px solid #CECECE;border-radius: 5px;margin-top: 0.5em;background-color: #FFFFFF;}QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;padding: 0 3px;}");


    scene = new VScene(this);
    _graphicsView->setScene(scene);

    ToolManager* toolManager = new ToolManager();

    connect(  _zoom, &QSlider::valueChanged,  this, &MainWindow::updateZoom  );
    connect(  _reset, &QPushButton::clicked,  this, &MainWindow::resetZoom  );
    connect(
            _mouseTool, &QAbstractButton::clicked,
            toolManager, &ToolManager::setMouseTool
        );

        connect(
            _rectangleTool, &QAbstractButton::clicked,
            toolManager, &ToolManager::setRectangleTool
        );
        connect(
            _ellipseTool, &QAbstractButton::clicked,
            toolManager, &ToolManager::setEllipseTool
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

        connect(
            _clear, &QAbstractButton::clicked,
            scene, &VScene::removeAllShapes
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
        _panel->setVisible(false);
        return;
    }else{
        QLayout* panel = scene->getSelectedShape()->getPanel();
        _verticalLayout->addLayout(panel);
        _panel->setVisible(true);
    }
}

void MainWindow::updateZoom(int inputZoom)
{
    _graphicsView->resetTransform();
    //graphicsView->setTransformationAnchor(QGraphicsView::Anchor);
    qreal zoom = inputZoom/100.0;
    _graphicsView->scale(zoom,zoom);
}

void MainWindow::resetZoom()
{
    _zoom->setValue(100);
}

MainWindow::~MainWindow()
{
}

