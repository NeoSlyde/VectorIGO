#include "ellipse.h"
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
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include "vcolorpicker.h"



ellipse::ellipse(QObject *parent, QGraphicsEllipseItem *parentGraphic):
    VShape(parent),
    ellipse::QGraphicsEllipseItem(parentGraphic)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    strokeColor = QColor(Qt::red);
    FillColor = QColor(Qt::blue);
    thickness = 3;


    grabber1 = new VGrabber(0-VGrabber::width(), 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber1, &VGrabber::sigMousePressEvent,this, &ellipse::pressResizeFromTopLeft);
    QObject::connect(grabber1, &VGrabber::sigMouseMoveEvent,this, &ellipse::moveResizeFromTopLeft);

    grabber2 = new VGrabber(boundingRect().width(), 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber2, &VGrabber::sigMousePressEvent, this, &ellipse::pressResizeFromTopRight);
    QObject::connect(grabber2, &VGrabber::sigMouseMoveEvent, this, &ellipse::moveResizeFromTopRight);

    grabber3 = new VGrabber(boundingRect().width() , boundingRect().height(), nullptr, this);
    QObject::connect(grabber3, &VGrabber::sigMousePressEvent,this, &ellipse::pressResizeFromBtmRight);
    QObject::connect(grabber3, &VGrabber::sigMouseMoveEvent,this, &ellipse::moveResizeFromBtmRight);

    grabber4 = new VGrabber(0-VGrabber::width(), boundingRect().height(), nullptr, this);
    QObject::connect(grabber4, &VGrabber::sigMousePressEvent,this, &ellipse::pressResizeFromBtmLeft);
    QObject::connect(grabber4, &VGrabber::sigMouseMoveEvent,this, &ellipse::moveResizeFromBtmLeft);

    grabber5 = new VGrabber(boundingRect().width()/2-VGrabber::width()/2, 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber5, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromTop);

    grabber6 = new VGrabber(boundingRect().width(), boundingRect().height()/2-VGrabber::height()/2, nullptr, this);
    QObject::connect(grabber6, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromRight);

    grabber7 = new VGrabber(boundingRect().width()/2-VGrabber::width()/2, boundingRect().height(), nullptr, this);
    QObject::connect(grabber7, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromBtm);

    grabber8 = new VGrabber(0-VGrabber::width(), boundingRect().height()/2-VGrabber::height()/2, nullptr, this);
    QObject::connect(grabber8, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromLeft);
    }

void ellipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    setPen(QPen(strokeColor, thickness));
        setBrush(FillColor);

        if(thickness<=0.01){
            setPen(QPen(Qt::transparent));
        }
    QGraphicsEllipseItem::paint(painter, option, widget);
}

QVariant ellipse::itemChange(GraphicsItemChange change, const QVariant &value)
{
   /*
    if (change == ItemPositionChange && scene()) {
    QPointF newPos = value.toPointF();
    QRectF rect = scene()->sceneRect();
    if (!rect.contains(newPos)) {
        newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
        newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        return newPos;
        }
    }
    */

    if (change == QGraphicsEllipseItem::ItemSelectedHasChanged && scene() )
    {
        updateGrabbersVisibility();
    }
    if (scene()  && change == QGraphicsItem::ItemPositionHasChanged)
    {
        updateGrabbersPosition();
        updateGrabbersVisibility();
    }


    return QGraphicsItem::itemChange(change, value);
}

void ellipse::updateGrabbersVisibility()
{
    if(isSelected()){
        scene()->selectedItems().count();

        VShape* selectedShape = dynamic_cast<VShape*>(scene()->selectedItems().at(0));


        std::cout << "ELLIPSE SELECTED " << selectedShape->toString().toStdString() <<std::endl;


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
    else{
        std::cout << "ELLipse NOT SELECTED" << scene()->selectedItems().count() <<std::endl;
        grabber1->setVisible(false);
        grabber2->setVisible(false);
        grabber3->setVisible(false);
        grabber4->setVisible(false);
        grabber5->setVisible(false);
        grabber6->setVisible(false);
        grabber7->setVisible(false);
        grabber8->setVisible(false);
    }
}

void ellipse::updateGrabbersPosition()
{
    prepareGeometryChange();
    grabber1->updatePosition(0-VGrabber::width(), 0-VGrabber::height());
    grabber2->updatePosition(boundingRect().width(), 0-VGrabber::height());
    grabber3->updatePosition(boundingRect().width() , boundingRect().height());
    grabber4->updatePosition(0-VGrabber::width(),boundingRect().height());
    grabber5->updatePosition(boundingRect().width()/2-VGrabber::width()/2, 0-VGrabber::height());
    grabber6->updatePosition(boundingRect().width(), boundingRect().height()/2-VGrabber::height()/2);
    grabber7->updatePosition(boundingRect().width()/2-VGrabber::width()/2, boundingRect().height());
    grabber8->updatePosition(0-VGrabber::width(), boundingRect().height()/2-VGrabber::height()/2);
    update();

}

void ellipse::setWidth(qreal inputWidth)
{
    QRectF rec = rect();
    rec.setWidth(inputWidth);
    setRect(rec);
    updateGrabbersPosition();
}

void ellipse::setHeight(qreal inputHeight)
{
    QRectF rec = rect();
    rec.setHeight(inputHeight);
    setRect(rec);
    updateGrabbersPosition();

}


qreal ellipse::distance(QPointF p1, QPointF p2)
{
    return sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2) * 1.0);
}

void ellipse::resize(QPointF moveDest )
{
    std::cout << "GRABBER SIG RECEIVE" << std::endl;
    int x_top_left = std::min(anchorGrabberDeformation.x(), moveDest.x());
    int y_top_left = std::min(anchorGrabberDeformation.y(), moveDest.y());

    int width = std::abs(moveDest.x()-anchorGrabberDeformation.x());
    int height = std::abs(moveDest.y()-anchorGrabberDeformation.y());

    setPos(x_top_left,y_top_left);
    setRect(0, 0, width, height);
    updateGrabbersPosition();
}



void ellipse::updateStrokeColor(QColor col)
{
    strokeColor = col;
    update();
}

void ellipse::updateFillColor(QColor col)
{
    FillColor = col;
    update();
}
void ellipse::updateThickness(qreal thickness)
{
    this->thickness = thickness;
    update();
}
void ellipse::doRotation(int rota)
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rota);
    updateGrabbersVisibility();
}

QColor ellipse::getStrokeColor()
{
    return strokeColor;
}

QColor ellipse::getFillColor()
{
    return FillColor;
}

qreal ellipse::getThickness()
{
    return thickness;
}


void ellipse::moveResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().bottomRight());
}

void ellipse::moveResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().bottomLeft());
}

void ellipse::moveResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().topLeft());
}

void ellipse::moveResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().topRight());
}

void ellipse::resizeFromTop(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);

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
void ellipse::resizeFromBtm(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);
    QRectF rec = rect();
    rec.setHeight(  (contains(mapFromParent(p2)))? rec.height()-dist:rec.height()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;

    setRect(rec);
    updateGrabbersPosition();

}
void ellipse::resizeFromRight(QGraphicsSceneMouseEvent *event)
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
void ellipse::resizeFromLeft(QGraphicsSceneMouseEvent *event)
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


void ellipse::slotRotate(int rota)
{
    doRotation(rota);
}

void ellipse::updateZvalue(int z)
{
    setZValue(z);
}

VShape* ellipse::clone()
{
    ellipse* newEllipse = new ellipse();
    scene()->addItem(newEllipse);
    newEllipse->setPos(pos());
    newEllipse->setRect(rect());
    newEllipse->setRotation(rotation());
    newEllipse->updateStrokeColor(strokeColor);
    newEllipse->updateFillColor(FillColor);
    newEllipse->updateThickness(thickness);
    newEllipse->setVisible(false);
    return newEllipse;
}

void ellipse::setVisible(bool value)
{
    QGraphicsItem::setVisible(value);
    updateGrabbersPosition();
    updateGrabbersVisibility();
}

void ellipse::setSelected(bool value)
{
    QGraphicsItem::setSelected(value);
}

void ellipse::MoveBy(QPointF delta)
{
    QGraphicsItem::moveBy(delta.x(),delta.y());
}



void ellipse::Accept(VShapeVisitor *visitor)
{
    visitor->visit(this);
}



QString ellipse::toString()
{
    return QString("ellipse");
}

