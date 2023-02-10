#include "rectangle.h"
#include <QPainter>
#include <QObject>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>
#include "vcolorpicker.h"
#include "vgrabber.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <exception>

/**
 * @brief VRectangle::VRectangle
 * @param parentGraphic
 * @param parent
 * @details Constructeur de la classe VRectangle
*/
VRectangle::VRectangle(QGraphicsItem *parentGraphic,QObject *parent):
    VShape(parent),
    VRectangle::QGraphicsRectItem(parentGraphic)
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

/**
 * @brief VRectangle::paint
 * @param painter
 * @param option
 * @param widget
 * @details Fonction de dessin de la classe VRectangle
 * @details Dessine un rectangle avec les paramètres de la classe
*/
void VRectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    setPen(QPen(strokeColor, thickness));
    setBrush(FillColor);

    if(thickness<=0.01){
        setPen(QPen(Qt::transparent));
    }

//    if(isSelected()){
//        QBrush grayBrush(Qt::lightGray);
//        setBrush(grayBrush);
//    }

//    QStyleOptionGraphicsItem myoption = (*option);
//    myoption.state &= !QStyle::State_Selected;

    QGraphicsRectItem::paint(painter, option, widget);
}

/**
 * @brief VRectangle::itemChange
 * @param change
 * @param value
 * @return
 * @details Fonction de changement d'état de la classe VRectangle
*/
QVariant VRectangle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // Keep the shape inside the scene rect
/*
    if (change == ItemPositionChange && scene()) {
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
*/
    // Toggle grabbers if selected or not
    if (change == QGraphicsItem::ItemSelectedHasChanged && scene() )
        {
            updateGrabbersVisibility();
        }

    //mise a jout position des grabbers ultra laggy ici
    if (scene()  && change == QGraphicsItem::ItemPositionHasChanged)
    {
        updateGrabbersPosition();
        updateGrabbersVisibility();
    }

    // Traitement de base
    return QGraphicsItem::itemChange(change, value);
}





/**
 * @brief VRectangle::updateGrabbersPosition
 * @details Fonction de mise a jour de la position des grabbers
*/
void VRectangle::updateGrabbersPosition()
{
    prepareGeometryChange();
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

/**
 * @brief VRectangle::updateGrabbersVisibility
 * @details Fonction de mise a jour de la visibilité des grabbers
*/
void VRectangle::updateGrabbersVisibility()
{
    if(isSelected()){
        scene()->selectedItems().count();
        VShape* selectedShape = dynamic_cast<VShape*>(scene()->selectedItems().at(0));


        std::cout << "RECT SELECTED" << selectedShape->toString().toStdString() <<std::endl;

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
        std::cout << "RECT NOT SELECTED" << scene()->selectedItems().count() <<std::endl;
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

/**
 * @brief VRectangle::toString
 * @return
 * @details Retourne le nom de la classe
*/
QString VRectangle::toString()
{
    return QString("rectangle");
}

/**
 * @brief VRectangle::clone
 * @return
 * @details Fonction de clonage de la classe VRectangle
 * @details Retourne un pointeur vers une copie de l'objet
 * @details La copie est ajoutée à la scène
*/
VShape* VRectangle::clone()
{
    VRectangle* newRect = new VRectangle();
    scene()->addItem(newRect);
    newRect->setPos(pos());
    newRect->setRect(rect());
    newRect->setRotation(rotation());
    newRect->updateStrokeColor(strokeColor);
    newRect->updateFillColor(FillColor);
    newRect->updateThickness(thickness);
    newRect->setVisible(false);
    return newRect;
}

/**
 * @brief VRectangle::setVisible
 * @param value
 * @details Fonction de mise a jour de la visibilité de la classe VRectangle
*/
void VRectangle::setVisible(bool value)
{
    QGraphicsItem::setVisible(value);
    updateGrabbersPosition();
    updateGrabbersVisibility();
}

/**
 * @brief VRectangle::setSelected
 * @param value
 * @details Fonction de mise a jour de la selection de la classe VRectangle
*/
void VRectangle::setSelected(bool value)
{
    QGraphicsItem::setSelected(value);
}

/**
 * @brief VRectangle::MoveBy
 * @param delta
 * @details Fonction de déplacement de la classe VRectangle
 * @details Déplace l'objet de delta en x et delta en y
*/
void VRectangle::MoveBy(QPointF delta)
{
    QGraphicsItem::moveBy(delta.x(),delta.y());
}

/**
 * @brief VRectangle::Accept
 * @param visitor
 * @details Fonction d'acceptation de la classe VRectangle
 * 
*/
void VRectangle::Accept(VShapeVisitor* visitor)
{
    return visitor->visit(this);
}


/**
 * @brief VRectangle::distance
 * @param p1
 * @param p2
 * @return
 * @details Fonction de calcul de la distance entre deux points
 * @details Retourne la distance entre les deux points
*/
qreal VRectangle::distance(QPointF p1, QPointF p2)
{
    return sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2) * 1.0);
}

/**
 * @brief VRectangle::resize
 * @param moveDest
 * @details Fonction de redimensionnement de la classe VRectangle
 * @details Redimensionne l'objet en fonction de la position du grabber
*/
void VRectangle::resize(QPointF moveDest )
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

void VRectangle::setWidth(qreal inputWidth)
{
    QRectF rec = rect();
    rec.setWidth(inputWidth);
    setRect(rec);
    updateGrabbersPosition();
}

void VRectangle::setHeight(qreal inputHeight)
{
    QRectF rec = rect();
    rec.setHeight(inputHeight);
    setRect(rec);
    updateGrabbersPosition();

}

void VRectangle::updateStrokeColor(QColor col)
{
    strokeColor = col;
    update();
}

void VRectangle::updateFillColor(QColor col)
{
    FillColor = col;
    update();
}

void VRectangle::updateThickness(qreal thickness)
{
    this->thickness = thickness;
    update();
}

/**
 * @brief VRectangle::doRotation
 * @param rota
 * @details Fonction de rotation de la classe VRectangle
 * @details Effectue une rotation de l'objet de rota degrés
*/
void VRectangle::doRotation(int rota)
{
    std::cout << rect().topLeft().x()<<" "<< rect().topLeft().y()<< std::endl;
    std::cout << pos().x()<<" "<< pos().y()<< std::endl;
    std::cout << mapToScene(rect().topLeft()).x()<<" "<< mapToScene(rect().topLeft()).y()<< std::endl;
    setTransformOriginPoint(rect().center());
    setRotation(rota);
    updateGrabbersVisibility();
    std::cout << rect().topLeft().x()<<" "<< rect().topLeft().y()<< std::endl;
    std::cout << pos().x()<<" "<< pos().y()<< std::endl;
    std::cout << mapToScene(rect().topLeft()).x()<<" "<< mapToScene(rect().topLeft()).y()<< std::endl;


}

QColor VRectangle::getStrokeColor()
{
    return strokeColor;
}

QColor VRectangle::getFillColor()
{
    return FillColor;
}

qreal VRectangle::getThickness()
{
    return thickness;
}


//-----------------------MOUSE INPUTS---------------------

void VRectangle::moveResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    resize( event->scenePos() );
}

void VRectangle::pressResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(rect().bottomRight());
}


void VRectangle::moveResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    resize( event->scenePos() );

}

void VRectangle::pressResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(rect().bottomLeft());
}


void VRectangle::moveResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    resize( event->scenePos() );

}

void VRectangle::pressResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(rect().topLeft());
}


void VRectangle::moveResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    resize( event->scenePos() );

}

void VRectangle::pressResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(rect().topRight());
}



void VRectangle::resizeFromTop(QGraphicsSceneMouseEvent *event)
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


//    QPointF c(rect().topLeft());
//    rect().translate(-rect().x(),-rect().y());
//    setRect(rect());
//    moveBy(c.x(),c.y());

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


//---------------------PANEL INPUTS-------------------------



void VRectangle::slotRotate(int rota)
{
    doRotation(rota);
}

void VRectangle::updateZvalue(int z)
{
    setZValue(z);
}


