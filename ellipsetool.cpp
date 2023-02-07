#include "ellipsetool.h"
#include "vtool.h"
#include <iostream>
#include <toolmanager.h>

ellipseTool::ellipseTool()
{

}


void ellipseTool::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
//    QPointF originePoint = mouseEvent->buttonDownScenePos(Qt::RightButton);
    pBuildingEllipse = new ellipse();
    pBuildingEllipse->setRect(0, 0, 6, 6);
//    pBuildingEllipse->setSelected(true);
    scene->addItem(pBuildingEllipse);
    pBuildingEllipse->setPos( mouseEvent->scenePos().x(), mouseEvent->scenePos().y() );
}


void ellipseTool::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    QPointF originePoint = mouseEvent->buttonDownScenePos(Qt::LeftButton);
    int x_top_left = std::min(originePoint.x(), mouseEvent->scenePos().x());
    int y_top_left = std::min(originePoint.y(), mouseEvent->scenePos().y());

    int width = std::abs(mouseEvent->scenePos().x()-originePoint.x());
    int height = std::abs(mouseEvent->scenePos().y()-originePoint.y());

    std::cout << "[LP-DEBUG] width " << originePoint.x()<< std::endl;
    std::cout << "[LP-DEBUG] height " << originePoint.y()<< std::endl;

    pBuildingEllipse->setPos(x_top_left,y_top_left);
    pBuildingEllipse->setRect(0, 0, width, height);
//    pBuildingEllipse->setSelected(true);
    pBuildingEllipse->updateGrabbersPosition();
}


void ellipseTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    toolmanager->setMouseTool();
}

QString ellipseTool::getID()
{
    return QString("ellipseTool");
}

