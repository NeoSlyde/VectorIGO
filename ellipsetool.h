#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H
#include "vtool.h"
#include "ellipse.h"

class ellipseTool:public VTool
{
public:
    ellipseTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)   override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)    override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager) override;
    static QString getID();


private:
    ellipse* pBuildingEllipse;
};

#endif // ELLIPSETOOL_H







