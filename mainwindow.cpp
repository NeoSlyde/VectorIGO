#include <QFileDialog>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsView>
#include "mainwindow.h"
#include "qdialog.h"
#include <iostream>
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

        /* Export */

        connect(actionExport_as_SVG, &QAction::triggered,
                this, &MainWindow::exportSVG);

        connect(actionExport_as_PNG, &QAction::triggered,
                this, &MainWindow::exportPNG);

        connect(actionExport_as_JPG, &QAction::triggered,
                this, &MainWindow::exportJPG);

        connect(actionExport_as_BMP, &QAction::triggered,
                this, &MainWindow::exportBMP);
}


/* export scene to svg file */
void MainWindow::exportSVG(){

    /* export scene to svg file.
     * svg file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(this, tr("VectorIGO : Export as SVG file."), "filename",
       tr("SVG files (*.svg)"));

    int padding = 40; /* Top and right padding */
    QSvgGenerator generator;
    generator.setFileName(newPath);
    generator.setSize(QSize(scene->width(), scene->height()));
    generator.setViewBox(QRect(-padding, -padding, scene->width()+padding, scene->height()+padding));
    generator.setTitle(tr("VectorIGO SVG document"));

    QPainter painter;
    painter.begin(&generator);
    scene->render(&painter);
    painter.end();

    std::cout << "Exported as SVG file to : " << newPath.toStdString() << std::endl;

}

/* export scene to png file */
void MainWindow::exportPNG(){

    /* export scene to png file.
     * png file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(this, tr("VectorIGO : Export as PNG file."), "filename",
       tr("PNG files (*.png)"));

    QGraphicsView view(scene);
    QImage image(view.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(newPath, "PNG");

    std::cout << "Exported as PNG file to : " << newPath.toStdString() << std::endl;

}

/* export scene to jpg file */
void MainWindow::exportJPG(){

    /* export scene to jpg file.
     * jpg file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(this, tr("VectorIGO : Export as JPG file."), "filename",
       tr("JPG files (*.jpg)"));

    QGraphicsView view(scene);
    QImage image(view.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(newPath, "JPG");

    std::cout << "Exported as JPG file to : " << newPath.toStdString() << std::endl;
}

/* export scene to bmp file */
void MainWindow::exportBMP(){

    /* export scene to bmp file.
     * bmp file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(this, tr("VectorIGO : Export as BMP file."), "filename",
       tr("BMP files (*.bmp)"));

    QGraphicsView view(scene);
    QImage image(view.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(newPath, "BMP");

    std::cout << "Exported as BMP file to : " << newPath.toStdString() << std::endl;
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

