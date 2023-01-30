#include "vscene.h"
#include "rectangle.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QtMath>
#include <algorithm>
#include <iostream>
#include "vgrabber.h"


VScene::VScene(QObject *parent) :
    QGraphicsScene::QGraphicsScene(parent)
{
}

void VScene::mousePressEventDefault(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void VScene::mouseMoveEventDefault(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void VScene::mouseReleaseEventDefault(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}





void VScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmousePressEvent(mouseEvent, this);
}



void VScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmouseMoveEvent(mouseEvent, this);
}



void VScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmouseReleaseEvent(mouseEvent, this);
}



