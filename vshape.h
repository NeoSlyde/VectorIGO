#ifndef VSHAPE_H
#define VSHAPE_H

#include "vshapevisitor.h"
#include <QLayout>
#include <QObject>

class VShape : public QObject
{
    Q_OBJECT

public:
    explicit VShape(QObject *parent = nullptr);
    virtual QString toString() =0;
    virtual void updateZvalue(int z) =0;
    virtual VShape* clone() =0;
    virtual void setVisible(bool value) =0;
    virtual void setSelected(bool value) =0;
    virtual void MoveBy(QPointF delta) =0;
    virtual void Accept(VShapeVisitor* visitor) = 0;
};

#endif // VSHAPE_H
