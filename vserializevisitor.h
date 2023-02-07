#ifndef VSERIALIZEVISITOR_H
#define VSERIALIZEVISITOR_H

#include "vshapevisitor.h"
#include <QObject>

class VSerializeVisitor : public QObject, public VShapeVisitor
{
    Q_OBJECT

public:
    explicit VSerializeVisitor(QObject *parent = nullptr);
    virtual void visit( VRectangle* rectangle)  override;
    virtual void visit( ellipse* rectangle)  override;
    QString getResult();

signals:

private:
    QString _shapeString;

};

#endif // VSERIALIZEVISITOR_H
