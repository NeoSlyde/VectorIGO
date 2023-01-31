#include "vmousetool.h"
#include "vscene.h"

VMouseTool::VMouseTool()
{


}


void VMouseTool::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    scene->mousePressEventDefault(mouseEvent);
}


void VMouseTool::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    scene->mouseMoveEventDefault(mouseEvent);
}


void VMouseTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    scene->mouseReleaseEventDefault(mouseEvent);

}
