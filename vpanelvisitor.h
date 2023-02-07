#ifndef VPANELVISITOR_H
#define VPANELVISITOR_H

#include <QObject>
#include "vshapevisitor.h"
#include <QLayout>
#include <QObject>


class VPanelVisitor : public QObject, public VShapeVisitor
{
    Q_OBJECT

public:
    explicit VPanelVisitor(QObject *parent = nullptr);
    virtual void visit( VRectangle* rectangle)  override;
    virtual void visit( ellipse* ell)  override;
    QLayout* getResult();


private:
    QLayout* _panel = nullptr;

signals:



};

#endif // VPANELVISITOR_H
