#include "mainwindow.h"
#include "toolmanager.h"
#include "vtoolbutton.h"
#include "vrectangletool.h"
#include "ellipse.h"
#include "vexporter.h"
#include "vverticallayout.h"
#include <iostream>
#include <QFileDialog>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsView>
#include <QSvgGenerator>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>


/**
 * @brief MainWindow::MainWindow
 * @param parent
 * @details
 * Constructor of the class MainWindow
 * Setup the visual part of the application
 * Create the main objects of the application
 * Connect actions
*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    /* setup visuel */
    setupUi(this);
    _panel->setVisible(false);
    _rectangleToolBtn->set(VRectangleTool::getID(), QIcon(":/ressources/form_square.png"));
    _ellipseToolBtn->set(ellipseTool::getID(), QIcon(":/ressources/ellipse.png"));
    _mouseToolBtn->set(VMouseTool::getID(), QIcon(":/ressources/pencil.png"));
    shapeSettingsSection = new VVerticalLayout();
    _settings->insertLayout(0,shapeSettingsSection);
    //_groupBox_2->setStyleSheet("QGroupBox {border: 1px solid #CECECE;border-radius: 5px;margin-top: 0.5em;background-color: #FFFFFF;}QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top center;padding: 0 3px;}");

    /* objets importants */
    _scene = new VScene(this);
    _graphicsView->setScene(_scene);
    _toolManager = new ToolManager();
    _exporter = new VExporter();
    _document = new VDocument();

    /* connect actions */
    connect(actionExport_as_SVG, &QAction::triggered,  this,         [this]{_exporter->exportSVG(this,_scene);});
    connect(actionExport_as_PNG, &QAction::triggered,  this,         [this]{_exporter->exportPNG(this,_scene);});
    connect(actionExport_as_JPG, &QAction::triggered,  this,         [this]{_exporter->exportJPG(this,_scene);});
    connect(actionExport_as_BMP, &QAction::triggered,  this,         [this]{_exporter->exportBMP(this,_scene);});
    connect(actionSave,          &QAction::triggered,  this,         [this]{_document->saveDoc(this,_scene, _file);});
    connect(actionSave_as,       &QAction::triggered,  this,         [this]{_document->saveDocAs(this,_scene);});
    connect(actionNew,           &QAction::triggered,  this,         [this]{_document->newProject(this,_scene, _file);});
    connect(actionOpen_Project,  &QAction::triggered,  this,         [this]{_document->loadDoc(this,_scene, _file);});
    connect(actionClear,         &QAction::triggered,  this,         &MainWindow::clearAllShapes);
    connect(actionZoom_In,       &QAction::triggered,  this,         [this]{_zoom->setValue(_zoom->value()+10);});
    connect(actionZoom_Out,      &QAction::triggered,  this,         [this]{_zoom->setValue(_zoom->value()-10);});
    connect(actionReset_Zoom,    &QAction::triggered,  this,         [this]{_zoom->setValue(100);});
    connect(actionExit,          &QAction::triggered,  this,         &MainWindow::quit);
    connect(actionDelete,        &QAction::triggered,  _scene,        &VScene::removeShapes);
    connect(actionPaste,         &QAction::triggered,  _scene,        &VScene::paste);
    connect(actionCopy,          &QAction::triggered,  _scene,        &VScene::copy);
    connect(actionSelect_All,    &QAction::triggered,  _scene,        &VScene::selectAll);
    connect(actionRectangle,     &QAction::triggered,  _toolManager,  &ToolManager::setRectangleTool);
    connect(actionEllispe,       &QAction::triggered,  _toolManager,  &ToolManager::setEllipseTool);
    connect(actionMouse,         &QAction::triggered,  _toolManager,  &ToolManager::setMouseTool);
    connect(actionAbout_Qt,      &QAction::triggered,  this,         [this]{QMessageBox::aboutQt(this, tr("About Qt"));} );
    connect(actionAbout,         &QAction::triggered,  this,         [this]{QMessageBox::about(this, tr("About VectorIGO"), tr("VectorIGO is a vector drawing software.\nIt is carried out as part of the M1 IHM 2023 course at Aix-Marseille University (AMU).\n\nContributors:\n\tMUSARDO Léo-Paul\n\tMSAYIF Bassem\n\tNICHOLAS Elijah\n\tOUARAB Juba\n\tPAPAZIAN Maxime"));} );

    /* connect "tools btn"<--> toolManager  */
    connect(_toolManager,            &ToolManager::sigToolChanged,   _rectangleToolBtn,    &VToolButton::notifyButton);
    connect(_toolManager,            &ToolManager::sigToolChanged,   _ellipseToolBtn,      &VToolButton::notifyButton);
    connect(_toolManager,            &ToolManager::sigToolChanged,   _mouseToolBtn,        &VToolButton::notifyButton);
    connect(_rectangleToolBtn,       &VToolButton::clicked,          actionRectangle,      &QAction::trigger);
    connect(_ellipseToolBtn,         &VToolButton::clicked,          actionEllispe,        &QAction::trigger);
    connect(_mouseToolBtn,           &VToolButton::clicked,          actionMouse,          &QAction::trigger);

    /* connect buttons */
    connect(_clear,             &QAbstractButton::clicked,   this,        &MainWindow::clearAllShapes);
    connect(_save,              &QAbstractButton::clicked,   actionSave,  &QAction::trigger);

    /* connect */
    connect(_zoom,               &QSlider::valueChanged,         _graphicsView,       &VView::updateZoom );
    connect(_reset,              &QPushButton::clicked,          actionReset_Zoom,    &QAction::trigger  );
    connect(_scene,              &VScene::sigmousePressEvent,    _toolManager,        &ToolManager::slotMousePress);
    connect(_scene,              &VScene::sigmouseMoveEvent,     _toolManager,        &ToolManager::slotMouseMove);
    connect(_scene,              &VScene::sigmouseReleaseEvent,  _toolManager,        &ToolManager::slotMouseRelease);
    connect(_scene,              &VScene::sigSceneHasChanged,    this,                [this]{shapeSettingsSection->refresh(_scene->getSelectedShape(), _panel);} );
}

/**
 * @brief MainWindow::quit
 * @details quit the application
 * @return void
 * @details ask the user if he wants to save his project before quitting
 * @details if the user wants to save his project, call the saveDoc method
 * @details if the user doesn't want to save his project, quit the application
 * @details if the user doesn't want to quit the application, do nothing
*/
void MainWindow::quit()
{
    QMessageBox::StandardButton quitChoice = QMessageBox::warning(this, "Quit the Application?","Quit the Application?",QMessageBox::Yes | QMessageBox::No );
    if(quitChoice!=QMessageBox::Yes) return;

    QMessageBox::StandardButton saveChoice = QMessageBox::warning(this, "Save your Project?","Save your Project?", QMessageBox::Save | QMessageBox::No );
    if(saveChoice==QMessageBox::Save) _document->saveDoc(this,_scene, _file);
    qApp->exit();
}

/**
 * @brief MainWindow::clearAllShapes
 * @details clear all shapes in the scene
 * @return void
*/
void MainWindow::clearAllShapes()
{
    QMessageBox::StandardButton userChoice = QMessageBox::warning(this, "Delete all Shapes ?" ,"Delete all Shapes ?",QMessageBox::Yes | QMessageBox::No );
    if(userChoice!=QMessageBox::Yes){
        return;
    }
    _scene->removeAllShapes();
}


MainWindow::~MainWindow()
{
}

