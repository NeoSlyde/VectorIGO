#include "vserializevisitor.h"
#include "rectangle.h"
#include "ellipse.h"

VSerializeVisitor::VSerializeVisitor(QObject *parent): QObject{parent}
{
}


void VSerializeVisitor::visit( VRectangle *rectangle)
{
    QString posX = QString::number(rectangle->pos().x());
    QString posY = QString::number(rectangle->pos().y());
    QString rectX = QString::number(rectangle->rect().topLeft().x());
    QString rectY = QString::number(rectangle->rect().topLeft().y());
    QString rectW = QString::number(rectangle->rect().width());
    QString rectH = QString::number(rectangle->rect().height());
    QString rota = QString::number(rectangle->rotation());
    QString stroke = rectangle->getStrokeColor().name();
    QString fill = rectangle->getFillColor().name();
    QString thick = QString::number(rectangle->getThickness());

    QString description = rectangle->toString() +' '+posX+' '+posY+' '+rectX+' '+rectY+' '+rectW+' '+rectH+' '+rota+' '+stroke+' '+fill+' '+thick;
    _shapeString = description;
}

void VSerializeVisitor::visit( ellipse *ell)
{
    QString posX = QString::number(ell->pos().x());
    QString posY = QString::number(ell->pos().y());
    QString rectX = QString::number(ell->rect().topLeft().x());
    QString rectY = QString::number(ell->rect().topLeft().y());
    QString rectW = QString::number(ell->rect().width());
    QString rectH = QString::number(ell->rect().height());
    QString rota = QString::number(ell->rotation());
    QString stroke = ell->getStrokeColor().name();
    QString fill = ell->getFillColor().name();
    QString thick = QString::number(ell->getThickness());

    QString description = ell->toString() +' '+posX+' '+posY+' '+rectX+' '+rectY+' '+rectW+' '+rectH+' '+rota+' '+stroke+' '+fill+' '+thick;
    _shapeString = description;
}

QString VSerializeVisitor::getResult()
{
    return _shapeString;
}


