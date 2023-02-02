#include "vgrabber.h"
#include <iostream>

qreal* VGrabber::_width = new qreal(6);
qreal* VGrabber::_height = new qreal(6);

VGrabber::VGrabber(qreal x, qreal y, QObject *parent, QGraphicsItem *parentGraphic) :
    QObject(parent),
    QGraphicsRectItem(parentGraphic)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    //setFlag(QGraphicsItem::ItemIsFocusable, true);
    setRect(QRectF(0,0,width(),height()));
    setPos(x,y);
    //parentGraphic->setSelected(true);
    _pen = QPen(Qt::black);
    _brush = QBrush(Qt::white);
    setPen(_pen);
    setBrush(_brush);
}



void VGrabber::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMouseMoveEvent(event);
}

void VGrabber::updatePosition(qreal in_x, qreal in_y)
{
    setPos(in_x, in_y);

}

qreal VGrabber::width()
{
    return *VGrabber::_width;
}

qreal VGrabber::height()
{
    return *VGrabber::_height;
}


void VGrabber::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMousePressEvent(event);
}


void VGrabber::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMouseMoveEvent(event);
}
