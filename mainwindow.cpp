#include <QFileDialog>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsView>
#include "mainwindow.h"
#include "toolmanager.h"
#include "vtoolbutton.h"
#include "vrectangletool.h"
#include <iostream>
#include "ellipse.h"
#include <QSvgGenerator>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    /*setup visuel*/
    setupUi(this);
    _panel->setVisible(false);
    setWindowTitle(QString("VectorIGO"));

    _rectangleTool = new VToolButton(VRectangleTool::getID());
    _rectangleTool->setIcon(QIcon(":/ressources/form_square.png"));
    _tools->addWidget(_rectangleTool);

    _ellipseTool = new VToolButton(ellipseTool::getID());
    _ellipseTool->setIcon(QIcon(":/ressources/ellipse.png"));
    _tools->addWidget(_ellipseTool);

    _mouseTool = new VToolButton(VMouseTool::getID());
    _mouseTool->setIcon(QIcon(":/ressources/pencil.png"));
    _tools->addWidget(_mouseTool);

    _undo->setIcon(QIcon(":/ressources/undo.png"));
    _redo->setIcon(QIcon(":/ressources/redo.png"));

    //_groupBox_2->setStyleSheet("QGroupBox {border: 1px solid #CECECE;border-radius: 5px;margin-top: 0.5em;background-color: #FFFFFF;}QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;padding: 0 3px;}");

    /*objets importants*/
    scene = new VScene(this);
    _graphicsView->setScene(scene);
    ToolManager* toolManager = new ToolManager();

    /*connect des actions*/
    connect(actionExport_as_SVG, &QAction::triggered,  this,         &MainWindow::exportSVG);
    connect(actionExport_as_PNG, &QAction::triggered,  this,         &MainWindow::exportPNG);
    connect(actionExport_as_JPG, &QAction::triggered,  this,         &MainWindow::exportJPG);
    connect(actionExport_as_BMP, &QAction::triggered,  this,         &MainWindow::exportBMP);
    connect(actionSave,          &QAction::triggered,  this,         &MainWindow::saveDoc);
    connect(actionSave_as,       &QAction::triggered,  this,         &MainWindow::saveDocAs);
    connect(actionNew,           &QAction::triggered,  this,         &MainWindow::newProject);
    connect(actionOpen_Project,  &QAction::triggered,  this,         &MainWindow::loadDoc);
    connect(actionAbout,         &QAction::triggered,  this,         &MainWindow::about);
    connect(actionAbout_Qt,      &QAction::triggered,  this,         &MainWindow::aboutQt);
    connect(actionClear,         &QAction::triggered,  this,         &MainWindow::clear);
    connect(actionZoom_In,       &QAction::triggered,  this,         &MainWindow::zoomIn);
    connect(actionZoom_Out,      &QAction::triggered,  this,         &MainWindow::zoomOut);
    connect(actionReset_Zoom,    &QAction::triggered,  this,         &MainWindow::resetZoom);
    connect(actionExit,          &QAction::triggered,  this,         &MainWindow::quit);
    connect(actionDelete,        &QAction::triggered,  scene,        &VScene::removeShapes);
    connect(actionPaste,         &QAction::triggered,  scene,        &VScene::paste);
    connect(actionCopy,          &QAction::triggered,  scene,        &VScene::copy);
    connect(actionSelect_All,    &QAction::triggered,  scene,        &VScene::selectAll);
    connect(actionRectangle,     &QAction::triggered,  toolManager,  &ToolManager::setRectangleTool);
    connect(actionEllispe,       &QAction::triggered,  toolManager,  &ToolManager::setEllipseTool);
    connect(actionMouse,         &QAction::triggered,  toolManager,  &ToolManager::setMouseTool);


    /*connect des boutons zoom*/
    connect(  _zoom,             &QSlider::valueChanged, this,       &MainWindow::updateZoom  );
    connect(  _reset,            &QPushButton::clicked,  this,       &MainWindow::resetZoom  );

    /*connect SIGS btn --> toolManager*/
    connect(_rectangleTool,       &VToolButton::clicked,     toolManager, &ToolManager::setRectangleTool);
    connect(_ellipseTool,         &VToolButton::clicked,     toolManager, &ToolManager::setEllipseTool);
    connect(_mouseTool,           &VToolButton::clicked,     toolManager, &ToolManager::setMouseTool);

    /*connect de boutons*/
    connect(_clear,             &QAbstractButton::clicked, this,       &MainWindow::clear);
    connect(_save,              &QAbstractButton::clicked, this,       &MainWindow::saveDoc);

    /*connect SIGS scene --> toolManager*/
    connect(scene,              &VScene::sigmousePressEvent,    toolManager,  &ToolManager::slotMousePress);
    connect(scene,              &VScene::sigmouseMoveEvent,     toolManager,  &ToolManager::slotMouseMove);
    connect(scene,              &VScene::sigmouseReleaseEvent,  toolManager,  &ToolManager::slotMouseRelease);

    /*connect scene-->updatePanel*/
    connect(scene,             &VScene::sigSceneHasChanged,  this,    &MainWindow::updatePanel);

    /*connect toolManager-->toolBar*/
    connect(toolManager,             &ToolManager::sigToolChanged,  _rectangleTool,    &VToolButton::notifyButton);
    connect(toolManager,             &ToolManager::sigToolChanged,  _ellipseTool,    &VToolButton::notifyButton);
    connect(toolManager,             &ToolManager::sigToolChanged,  _mouseTool,    &VToolButton::notifyButton);

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

    //QGraphicsView view(scene);
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
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

    //QGraphicsView view(scene);
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);
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

    //QGraphicsView view(scene);
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(newPath, "BMP");

    std::cout << "Exported as BMP file to : " << newPath.toStdString() << std::endl;
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About VectorIGO"), tr("VectorIGO is a vector drawing software.\nIt is carried out as part of the M1 IHM 2023 course at Aix-Marseille University (AMU).\n\nContributors:\n\tMUSARDO Léo-Paul\n\tMSAYIF Bassem\n\tNICHOLAS Elijah\n\tOUARAB Juba\n\tPAPAZIAN Maxime"));
}


void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::quit()
{
    qApp->exit();
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

void MainWindow::zoomIn()
{
    _zoom->setValue(_zoom->value()+10);
}

void MainWindow::zoomOut()
{
    _zoom->setValue(_zoom->value()-10);
}




void MainWindow::saveDoc()
{

    for (;;) {
        QString fileName = filePath;

        if (fileName.isEmpty())
            fileName = QFileDialog::getSaveFileName(this, "Save File As", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) +QDir::separator()+"file.igo") ;
        if (fileName.isEmpty())
            break;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, tr("File error"),tr("Failed to open\n%1").arg(fileName));
        } else {
            QTextStream stream(&file);
            scene->save(stream);
            filePath = fileName;
            _file->setText(filePath.split(QDir::separator()).last());
            break;
        }
    }
}

void MainWindow::saveDocAs()
{
    for (;;) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save File As", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) +QDir::separator()+"copy.igo") ;
        if (fileName.isEmpty())
            break;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning( this,  tr("File error"),  tr("Failed to open\n%1").arg(fileName) );
        } else {
            QTextStream stream(&file);
            scene->save(stream);
            break;
        }
    }
}

void MainWindow::newProject()
{

    QMessageBox::StandardButton userChoice = QMessageBox::warning(this,"Warning", "Change current project ?", QMessageBox::Yes | QMessageBox::No );
    if(userChoice!=QMessageBox::Yes){
        return;
    }

    QMessageBox msgBoxSave;
    msgBoxSave.setText("Save previous project ?");
    msgBoxSave.setInformativeText("Save the modifications of your previous project?");
    msgBoxSave.setStandardButtons(QMessageBox::Save | QMessageBox::No);
    msgBoxSave.setDefaultButton(QMessageBox::Save);
    int ret = msgBoxSave.exec();
    if(ret!=QMessageBox::No){
        saveDoc();
    }

    filePath = QString();
    _file->setText("sans_titre.igo");
    scene->removeAllShapes();
}

void MainWindow::loadDoc()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open VectorIGO project", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "IGO PROJECTS (*.igo)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("File error"),tr("Failed to open\n%1").arg(fileName));
        return;
    }

    QMessageBox::StandardButton userChoice = QMessageBox::warning(this,"Warning", "Change current project ?", QMessageBox::Yes | QMessageBox::No );
    if(userChoice!=QMessageBox::Yes){
        return;
    }

    QMessageBox msgBoxSave;
    msgBoxSave.setText("Save previous project ?");
    msgBoxSave.setInformativeText("Save the modifications of your previous project?");
    msgBoxSave.setStandardButtons(QMessageBox::Save | QMessageBox::No);
    msgBoxSave.setDefaultButton(QMessageBox::Save);
    int ret = msgBoxSave.exec();
    if(ret!=QMessageBox::No){
        saveDoc();
    }

    scene->removeAllShapes();
    QTextStream stream(&file);
    scene->load(stream);
    filePath = fileName;
    _file->setText(filePath.split(QDir::separator()).last());
}


MainWindow::~MainWindow()
{
}

void MainWindow::clear()
{
    scene->removeAllShapes();
}

