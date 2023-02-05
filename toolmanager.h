#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H
#include <QGraphicsSceneMouseEvent>
#include "vscene.h"
#include "vtool.h"
#include "vrectangletool.h"
#include "vmousetool.h"
#include "ellipsetool.h"

#include <QObject>

class ToolManager : public QObject
{
    Q_OBJECT

public:
    explicit ToolManager(QObject *parent = nullptr);


public slots:
    void setMouseTool();
    void setRectangleTool();
    void setEllipseTool();
    void slotMousePress(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void slotMouseMove(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void slotMouseRelease(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);


private:
    VRectangleTool* rectangleTool = new VRectangleTool();
    VMouseTool* mouseTool = new VMouseTool();
    VTool* CurrentTool = mouseTool;
    ellipseTool* ellipsetool=new ellipseTool();


signals:
    void sigToolChanged(QString toolId);

};



#endif // TOOLMANAGER_H
