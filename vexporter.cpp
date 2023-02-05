#include "vexporter.h"
#include "vscene.h"
#include <QFileDialog>
#include <QPainter>
#include <QSvgGenerator>
#include <iostream>

VExporter::VExporter(QObject *parent) : QObject{parent}
{
}



void VExporter::exportSVG(QWidget *parent, VScene* scene){

    /* export scene to svg file.
     * svg file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(parent, tr("VectorIGO : Export as SVG file."), "filename", tr("SVG files (*.svg)"));

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


void VExporter::exportPNG(QWidget *parent, VScene* scene){

    /* export scene to png file.
     * png file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(parent, tr("VectorIGO : Export as PNG file."), "filename",
       tr("PNG files (*.png)"));

    //QGraphicsView view(scene);
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(newPath, "PNG");

    std::cout << "Exported as PNG file to : " << newPath.toStdString() << std::endl;

}


void VExporter::exportJPG(QWidget *parent, VScene* scene){

    /* export scene to jpg file.
     * jpg file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(parent, tr("VectorIGO : Export as JPG file."), "filename",
       tr("JPG files (*.jpg)"));

    //QGraphicsView view(scene);
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(newPath, "JPG");

    std::cout << "Exported as JPG file to : " << newPath.toStdString() << std::endl;
}


void VExporter::exportBMP(QWidget *parent, VScene* scene){

    /* export scene to bmp file.
     * bmp file size = scene size.
     */

    QString newPath = QFileDialog::getSaveFileName(parent, tr("VectorIGO : Export as BMP file."), "filename",
       tr("BMP files (*.bmp)"));

    //QGraphicsView view(scene);
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(newPath, "BMP");

    std::cout << "Exported as BMP file to : " << newPath.toStdString() << std::endl;
}


