#include "vview.h"
#include "QGraphicsView"


/**
 * @details Classe qui permet de gérer tout ce qui touche à la vue correspondant au "plan de travail".
 */

VView::VView(QWidget *parent) : QGraphicsView(parent)
{
    //scene()->setlim
}


/**
 * @brief VView::drawBackground
 * @param painter
 * @param rect
 * @details Permet de tracer les limites du plan de travail, notamment la ligne grise qui le délimite.
 */
void VView::drawBackground(QPainter *painter, const QRectF &rect)
{
    setCacheMode(CacheNone);
    painter->save();
    painter->setPen( QPen(Qt::darkGray,1) );
    painter->drawRect(scene()->sceneRect());
    painter->restore();
}


/**
 * @brief VView::drawBackground
 * @param painter
 * @param rect
 * @details Permet de mettre à jour le zoom en fonction de l'entier passé en paramètres.
 */
void VView::updateZoom(int inputZoom)
{
    resetTransform();
    //graphicsView->setTransformationAnchor(QGraphicsView::Anchor);
    qreal zoom = inputZoom/100.0;
    scale(zoom,zoom);
}

