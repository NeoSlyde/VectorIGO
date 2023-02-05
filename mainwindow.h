#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "rectangle.h"
#include "ellipse.h"
#include "vtoolbutton.h"
#include "vscene.h"
#include "toolmanager.h"
#include "vexporter.h"
#include "vdocument.h"
#include "vverticallayout.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>



class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    VScene *_scene;
    ToolManager* _toolManager;
    VExporter* _exporter;
    VDocument* _document;
    VVerticalLayout* shapeSettingsSection;

public slots:
    void clearAllShapes();
    void quit();
};

#endif // MAINWINDOW_H
