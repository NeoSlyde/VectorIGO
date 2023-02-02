#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include "vgrabber.h"
#include "vshape.h"


class VRectangle;

class VRectangle : public VShape, public QGraphicsRectItem
{


public:
    VRectangle(QObject *parent = nullptr, QGraphicsItem *parentGraphic = nullptr);
    QLayout* getPanel() override;
    void updateZvalue(int z) override;
    //~VRectangle();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void updateGrabbersPosition();
    void updateGrabbersVisibility();
    QString toString() override;

private:
    VGrabber* grabber1 = nullptr;
    VGrabber* grabber2 = nullptr;
    VGrabber* grabber3 = nullptr;
    VGrabber* grabber4 = nullptr;
    VGrabber* grabber5 = nullptr;
    VGrabber* grabber6 = nullptr;
    VGrabber* grabber7 = nullptr;
    VGrabber* grabber8 = nullptr;
    qreal distance(QPointF p1, QPointF p2);
    void resize(QPointF moveDest );
    void doRotation(int rota);
    QPointF anchorGrabberDeformation;
    QColor strokeColor;
    QColor FillColor;
    qreal thickness;

public slots:
    //mouse inputs
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

    //panel inputs
    void slotRotate(int rota);
    void slotResizeFromTopLeftX(int x);
    void slotResizeFromTopLeftY(int y);
    void setWidth(qreal inputWidth);
    void setHeight(qreal inputHeight);
    void updateStrokeColor(QColor col);
    void updateFillColor(QColor col);
    void updateThickness(qreal thickness);

};

#endif // RECTANGLE_H
