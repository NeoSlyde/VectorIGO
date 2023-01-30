#ifndef VSCENE_H
#define VSCENE_H
#include <QObject>
#include <QGraphicsScene>

class VScene;

class VScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit VScene(QObject *parent = nullptr);
    void mousePressEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    //void setTool(VTool* tool);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;


signals:
    void sigmousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigmouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigmouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);

};

#endif // VSCENE_H
