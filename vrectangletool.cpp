#include "vrectangletool.h"
#include "vtool.h"
#include <iostream>
#include <toolmanager.h>

VRectangleTool::VRectangleTool()
{

}


void VRectangleTool::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
//    QPointF originePoint = mouseEvent->buttonDownScenePos(Qt::RightButton);
    pBuildingRectangle = new VRectangle();
    pBuildingRectangle->setRect(0, 0, 6, 6);
    //pBuildingRectangle->setSelected(true);
    scene->addItem(pBuildingRectangle);
    pBuildingRectangle->setPos( mouseEvent->scenePos().x(), mouseEvent->scenePos().y() );

}


void VRectangleTool::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    QPointF originePoint = mouseEvent->buttonDownScenePos(Qt::LeftButton);
    int x_top_left = std::min(originePoint.x(), mouseEvent->scenePos().x());
    int y_top_left = std::min(originePoint.y(), mouseEvent->scenePos().y());

    int width = std::abs(mouseEvent->scenePos().x()-originePoint.x());
    int height = std::abs(mouseEvent->scenePos().y()-originePoint.y());

    std::cout << "[LP-DEBUG] width " << originePoint.x()<< std::endl;
    std::cout << "[LP-DEBUG] height " << originePoint.y()<< std::endl;

    pBuildingRectangle->setPos(x_top_left,y_top_left);
    pBuildingRectangle->setRect(0, 0, width, height);
    //pBuildingRectangle->setSelected(true);
    pBuildingRectangle->updateGrabbersPosition();
}


void VRectangleTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    toolmanager->setMouseTool();
}

QString VRectangleTool::getID()
{
    return QString("rectangleTool");
}
