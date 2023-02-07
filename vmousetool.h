#ifndef VMOUSETOOL_H
#define VMOUSETOOL_H
#include "vtool.h"
#include "rectangle.h"


class VMouseTool : public VTool
{
public:
    VMouseTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)   override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)    override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager) override;
    static QString getID();

private:




};

#endif // VMOUSETOOL_H
