#ifndef VTOOL_H
#define VTOOL_H

#include <QGraphicsSceneMouseEvent>
#include "vscene.h"

class ToolManager;
class VTool
{

public:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene * scene, ToolManager* toolmanager)   = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)    = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager) = 0;

signals:




};

#endif // VTOOL_H
