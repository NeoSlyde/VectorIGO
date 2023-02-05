#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "rectangle.h"
#include "ellipse.h"
#include "vtoolbutton.h"
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
    void sceneToSvg();

public slots:
    void zoomIn();
    void zoomOut();
    void clear();
    void loadDoc();
    void saveDoc();
    void saveDocAs();
    void newProject();
    void updatePanel();
    void updateZoom(int inputZoom);
    void resetZoom();
    void exportSVG();
    void exportPNG();
    void exportJPG();
    void exportBMP();
    void about();
    void aboutQt();
    void quit();


private:
    QString filePath;
    std::unique_ptr<QDialog> colorPickerFill;
    std::unique_ptr<QDialog> colorPickerStroke;
    VToolButton* _rectangleTool = nullptr;
    VToolButton* _ellipseTool = nullptr;
    VToolButton* _mouseTool = nullptr;
};

#endif // MAINWINDOW_H
