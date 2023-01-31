#ifndef VRECTANGLETOOL_H
#define VRECTANGLETOOL_H
#include "vtool.h"
#include "rectangle.h"


class VRectangleTool  : public VTool
{
public:
    VRectangleTool();
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)   override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)    override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager) override;

private:
    VRectangle* pBuildingRectangle;
};

#endif // VRECTANGLETOOL_H
