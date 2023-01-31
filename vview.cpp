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
