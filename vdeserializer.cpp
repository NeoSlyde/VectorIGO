#include "ellipse.h"
#include "rectangle.h"
#include "vdeserializer.h"
#include <QGraphicsScene>
#include <iostream>

VDeserializer::VDeserializer(QObject *parent)
    : QObject{parent}
{
}

QGraphicsItem *VDeserializer::deSerializeRectangle(QString input, QGraphicsScene *scene)
{
    QStringList elements = input.split(' ');
    if (elements.count()!=11) return nullptr;

    qreal posX, posY, rectX, rectY, rectW, rectH, rota, thick;
    QColor stroke, fill;

    try {
        posX = elements.at(1).toDouble();
        posY = elements.at(2).toDouble();
        rectX = elements.at(3).toDouble();
        rectY = elements.at(4).toDouble();
        rectW = elements.at(5).toDouble();
        rectH = elements.at(6).toDouble();
        rota = elements.at(7).toDouble();
        stroke = QColor(elements.at(8));
        fill = QColor(elements.at(9));
        thick = elements.at(10).toDouble();
    } catch(...) {
        return nullptr;
    }

    VRectangle* newRect = new VRectangle();
    scene->addItem(newRect);
    newRect->setPos(posX,posY);
    newRect->setRect(QRectF(rectX,rectY, rectW, rectH));
    newRect->setRotation(rota);
    newRect->updateStrokeColor(stroke);
    newRect->updateFillColor(fill);
    newRect->updateThickness(thick);
    newRect->updateGrabbersPosition();

    std::cout << "RECTANGLE DESERIALIZED" << std::endl;
    return newRect;
}




QGraphicsItem *VDeserializer::deSerializeEllipse(QString input, QGraphicsScene *scene)
{
    QStringList elements = input.split(' ');
    if (elements.count()!=11) return nullptr;

    qreal posX, posY, rectX, rectY, rectW, rectH, rota, thick;
    QColor stroke, fill;

    try {
        posX = elements.at(1).toDouble();
        posY = elements.at(2).toDouble();
        rectX = elements.at(3).toDouble();
        rectY = elements.at(4).toDouble();
        rectW = elements.at(5).toDouble();
        rectH = elements.at(6).toDouble();
        rota = elements.at(7).toDouble();
        stroke = QColor(elements.at(8));
        fill = QColor(elements.at(9));
        thick = elements.at(10).toDouble();
    } catch(...) {
        return nullptr;
    }

    ellipse* newEllipse = new ellipse();
    scene->addItem(newEllipse);
    newEllipse->setPos(posX,posY);
    newEllipse->setRect(QRectF(rectX,rectY, rectW, rectH));
    newEllipse->setRotation(rota);
    newEllipse->updateStrokeColor(stroke);
    newEllipse->updateFillColor(fill);
    newEllipse->updateThickness(thick);
    newEllipse->updateGrabbersPosition();

    std::cout << "ELLIPSE DESERIALIZED" << std::endl;
    return newEllipse;
}



