#ifndef VSCENE_H
#define VSCENE_H
#include <QObject>
#include <QGraphicsScene>
#include <QUndoStack>
#include <vshape.h>

class VScene;

class VScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit VScene(QObject *parent = nullptr, QUndoStack *undoStack = nullptr);
    void mousePressEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    VShape* getSelectedShape();
    QList<QGraphicsItem*>* getShapes();
    QList<QGraphicsEllipseItem*>* getEllipseShapes();
    void addShape(VShape *shape);
    void removeShape(VShape *shape);

public slots:
    void removeAllShapes();

private:
    QUndoStack *_undoStack;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void keyPressEvent(QKeyEvent* keyEvent) override;

signals:
    void sigmousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigmouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigmouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigRemoveItems();
};



#endif // VSCENE_H
