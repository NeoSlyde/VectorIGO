#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include "vgrabber.h"


class VRectangle;

class VRectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    VRectangle(QObject *parent = nullptr, QGraphicsItem *parentGraphic = nullptr);
    //~VRectangle();
    //VRectangle(qreal x, qreal y, qreal w, qreal h, QObject *parent = nullptr, QGraphicsItem *parentGraphic = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void updateGrabbersPosition();
    void updateGrabbersVisibility();


private:
    VGrabber* grabber1 = nullptr;
    VGrabber* grabber2 = nullptr;
    VGrabber* grabber3 = nullptr;
    VGrabber* grabber4 = nullptr;
    VGrabber* grabber5 = nullptr;
    VGrabber* grabber6 = nullptr;
    VGrabber* grabber7 = nullptr;
    VGrabber* grabber8 = nullptr;
    QPointF anchorGrabberDeformation;
    QPointF mousePressScenePoint;
    qreal distance(QPointF p1, QPointF p2);

public slots:
    void resize(QGraphicsSceneMouseEvent *event);

    void moveResizeFromTopLeft(QGraphicsSceneMouseEvent *event);
    void pressResizeFromTopLeft(QGraphicsSceneMouseEvent *event);

    void moveResizeFromTopRight(QGraphicsSceneMouseEvent *event);
    void pressResizeFromTopRight(QGraphicsSceneMouseEvent *event);

    void moveResizeFromBtmRight(QGraphicsSceneMouseEvent *event);
    void pressResizeFromBtmRight(QGraphicsSceneMouseEvent *event);

    void moveResizeFromBtmLeft(QGraphicsSceneMouseEvent *event);
    void pressResizeFromBtmLeft(QGraphicsSceneMouseEvent *event);

    void resizeFromTop(QGraphicsSceneMouseEvent *event);
    void resizeFromBtm(QGraphicsSceneMouseEvent *event);
    void resizeFromRight(QGraphicsSceneMouseEvent *event);
    void resizeFromLeft(QGraphicsSceneMouseEvent *event);
};

#endif // RECTANGLE_H
