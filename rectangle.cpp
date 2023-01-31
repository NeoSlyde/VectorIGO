#include "rectangle.h"
#include <QPainter>
#include <QObject>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>
#include "vgrabber.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>


VRectangle::VRectangle(QObject *parent, QGraphicsItem *parentGraphic):
    QObject(parent),
    VRectangle::QGraphicsRectItem(parentGraphic)
{    
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    grabber1 = new VGrabber(0-VGrabber::width(), 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber1, &VGrabber::sigMousePressEvent,this, &VRectangle::pressResizeFromTopLeft);
    QObject::connect(grabber1, &VGrabber::sigMouseMoveEvent,this, &VRectangle::moveResizeFromTopLeft);

    grabber2 = new VGrabber(rect().width(), 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber2, &VGrabber::sigMousePressEvent, this, &VRectangle::pressResizeFromTopRight);
    QObject::connect(grabber2, &VGrabber::sigMouseMoveEvent, this, &VRectangle::moveResizeFromTopRight);

    grabber3 = new VGrabber(rect().width() , rect().height(), nullptr, this);
    QObject::connect(grabber3, &VGrabber::sigMousePressEvent,this, &VRectangle::pressResizeFromBtmRight);
    QObject::connect(grabber3, &VGrabber::sigMouseMoveEvent,this, &VRectangle::moveResizeFromBtmRight);

    grabber4 = new VGrabber(0-VGrabber::width(), rect().height(), nullptr, this);
    QObject::connect(grabber4, &VGrabber::sigMousePressEvent,this, &VRectangle::pressResizeFromBtmLeft);
    QObject::connect(grabber4, &VGrabber::sigMouseMoveEvent,this, &VRectangle::moveResizeFromBtmLeft);

    grabber5 = new VGrabber(rect().width()/2-VGrabber::width()/2, 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber5, &VGrabber::sigMouseMoveEvent,this, &VRectangle::resizeFromTop);

    grabber6 = new VGrabber(rect().width(), rect().height()/2-VGrabber::height()/2, nullptr, this);
    QObject::connect(grabber6, &VGrabber::sigMouseMoveEvent,this, &VRectangle::resizeFromRight);

    grabber7 = new VGrabber(rect().width()/2-VGrabber::width()/2, rect().height(), nullptr, this);
    QObject::connect(grabber7, &VGrabber::sigMouseMoveEvent,this, &VRectangle::resizeFromBtm);

    grabber8 = new VGrabber(0-VGrabber::width(), rect().height()/2-VGrabber::height()/2, nullptr, this);
    QObject::connect(grabber8, &VGrabber::sigMouseMoveEvent,this, &VRectangle::resizeFromLeft);
}


//VRectangle::VRectangle(qreal x, qreal y, qreal w, qreal h, QObject *parent, QGraphicsItem *parentGraphic)
//{
//    VRectangle::QGraphicsRectItem(x, y, w, h, parentGraphic);
//    VRectangle(parent, parentGraphic);
//}




void VRectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QStyleOptionGraphicsItem myoption = (*option);
    myoption.state &= !QStyle::State_Selected;

    QColor redColor(Qt::red);
    QPen redPen(redColor);
    redPen.setWidth(0);
    setPen(redPen);

    if(isSelected()){
        QBrush grayBrush(Qt::lightGray);
        setBrush(grayBrush);
    }else{
        QBrush blueBrush(Qt::blue);
        setBrush(blueBrush);
    }

    QGraphicsRectItem::paint(painter, &myoption, widget);
}



QVariant VRectangle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // Keep the shape inside the scene rect
/**/    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }
/**/
    // Toggle grabbers if selected or not
    if (change == QGraphicsItem::ItemSelectedChange && scene() )
        {
        updateGrabbersVisibility();
        }

    //mise a jout position des grabbers ultra laggy ici
//    if (scene()  && change == QGraphicsItem::ItemSelectedChange)
//    {
//        updateGrabbers();
//    }

    // Traitement de base
    return QGraphicsItem::itemChange(change, value);
}





//--------------------------GRABBERS--------------------------

void VRectangle::updateGrabbersPosition()
{
    prepareGeometryChange();
    //update position
    grabber1->updatePosition(0-VGrabber::width(), 0-VGrabber::height());
    grabber2->updatePosition(rect().width(), 0-VGrabber::height());
    grabber3->updatePosition(rect().width() , rect().height());
    grabber4->updatePosition(0-VGrabber::width(), rect().height());
    grabber5->updatePosition(rect().width()/2-VGrabber::width()/2, 0-VGrabber::height());
    grabber6->updatePosition(rect().width(), rect().height()/2-VGrabber::height()/2);
    grabber7->updatePosition(rect().width()/2-VGrabber::width()/2, rect().height());
    grabber8->updatePosition(0-VGrabber::width(), rect().height()/2-VGrabber::height()/2);
    update();


}

void VRectangle::updateGrabbersVisibility()
{
    if(isSelected()){
        grabber1->setVisible(false);
        grabber2->setVisible(false);
        grabber3->setVisible(false);
        grabber4->setVisible(false);
        grabber5->setVisible(false);
        grabber6->setVisible(false);
        grabber7->setVisible(false);
        grabber8->setVisible(false);
    }
    else{
        grabber1->setVisible(true);
        grabber2->setVisible(true);
        grabber3->setVisible(true);
        grabber4->setVisible(true);
        grabber5->setVisible(true);
        grabber6->setVisible(true);
        grabber7->setVisible(true);
        grabber8->setVisible(true);
        if(rotation()!=0){
            grabber1->setVisible(false);
            grabber2->setVisible(false);
            grabber3->setVisible(false);
            grabber4->setVisible(false);
        }
    }
}

qreal VRectangle::distance(QPointF p1, QPointF p2)
{
    return sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2) * 1.0);
}

void VRectangle::resize(QGraphicsSceneMouseEvent *event)
{
    std::cout << "GRABBER SIG RECEIVE" << std::endl;
    int x_top_left = std::min(anchorGrabberDeformation.x(), event->scenePos().x());
    int y_top_left = std::min(anchorGrabberDeformation.y(), event->scenePos().y());

    int width = std::abs(event->scenePos().x()-anchorGrabberDeformation.x());
    int height = std::abs(event->scenePos().y()-anchorGrabberDeformation.y());

    setPos(x_top_left,y_top_left);
    setRect(0, 0, width, height);
    updateGrabbersPosition();
}

//--------------------------
void VRectangle::moveResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    resize(event);
}

void VRectangle::pressResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = QPointF(  pos() + rect().bottomRight()  );
    mousePressScenePoint = QPointF(event->scenePos());
}
//--------------------------

void VRectangle::moveResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    resize(event);
}

void VRectangle::pressResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = QPointF(rect().bottomLeft().x()+pos().x(), rect().bottomLeft().y()+pos().y());
}


void VRectangle::moveResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    resize(event);
}

void VRectangle::pressResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = QPointF(rect().topLeft().x()+pos().x(), rect().topLeft().y()+pos().y());
}


void VRectangle::moveResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    resize(event);
}

void VRectangle::pressResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = QPointF(rect().topRight().x()+pos().x(), rect().topRight().y()+pos().y());
}



void VRectangle::resizeFromTop(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);
    //qreal dist_prev_centre = distance(p1,mapToParent(rect().center()));
    //qreal dist_cur_centre  = distance(p2,mapToParent(rect().center()));

    QRectF rec = rect();
    rec.setHeight(  (contains(mapFromParent(p2)))? rec.height()-dist:rec.height()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;
    if(contains(mapFromParent(p2)))
        moveBy(+dist*cos(rotation()*M_PI/180.0 + M_PI/2), +dist*sin(rotation()*M_PI/180.0 + M_PI/2 ));
    else
        moveBy(-dist*cos(rotation()*M_PI/180.0 + M_PI/2), -dist*sin(rotation()*M_PI/180.0 + M_PI/2 ));

    setRect(rec);
    updateGrabbersPosition();
}



void VRectangle::resizeFromBtm(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);
    QRectF rec = rect();
    rec.setHeight(  (contains(mapFromParent(p2)))? rec.height()-dist:rec.height()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;

//    if(contains(mapFromParent(p2)))
//        moveBy(-dist*cos(rotation()*M_PI/180.0 +3*M_PI/2), -dist*sin(rotation()*M_PI/180.0 +3*M_PI/2));
//    else
//        moveBy(-dist*cos(rotation()*M_PI/180.0 +3*M_PI/2), -dist*sin(rotation()*M_PI/180.0 +3*M_PI/2));

    setRect(rec);
    updateGrabbersPosition();
}

void VRectangle::resizeFromRight(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);

    QRectF rec = rect();
    rec.setWidth(  (contains(mapFromParent(p2)))? rec.width()-dist:rec.width()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;

    setRect(rec);
    updateGrabbersPosition();
}

void VRectangle::resizeFromLeft(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);

    QRectF rec = rect();
    rec.setWidth(  (contains(mapFromParent(p2)))? rec.width()-dist:rec.width()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;
    if(contains(mapFromParent(p2)))
        moveBy(+dist*cos(rotation()*M_PI/180.0), +dist*sin(rotation()*M_PI/180.0));
    else
        moveBy(-dist*cos(rotation()*M_PI/180.0), -dist*sin(rotation()*M_PI/180.0));

    setRect(rec);
    updateGrabbersPosition();

}





