#include "vview.h"
#include "QGraphicsView"


VView::VView(QWidget *parent) : QGraphicsView(parent)
{
    //scene()->setlim
}


void VView::drawBackground(QPainter *painter, const QRectF &rect)
{
    setCacheMode(CacheNone);
    painter->save();
    painter->setPen( QPen(Qt::darkGray,1) );
    painter->drawRect(scene()->sceneRect());
    painter->restore();
}


void VView::updateZoom(int inputZoom)
{
    resetTransform();
    //graphicsView->setTransformationAnchor(QGraphicsView::Anchor);
    qreal zoom = inputZoom/100.0;
    scale(zoom,zoom);
}

