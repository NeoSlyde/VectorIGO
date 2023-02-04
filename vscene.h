#ifndef VSCENE_H
#define VSCENE_H
#include <QObject>
#include <QGraphicsScene>
#include <vshape.h>
#include <QKeyEvent>

class VScene;

class VScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit VScene(QObject *parent = nullptr);
    void mousePressEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEventDefault(QGraphicsSceneMouseEvent *mouseEvent);
    VShape* getSelectedShape();
    QList<VShape*>* getSelectedShapes();
    QList<QGraphicsItem*>* getShapes();
    void save(QTextStream &stream);
    void load(QTextStream &stream);
    bool isEmpty();
    void selectAll();
    void sceneHasChanged();
    void deselectAll();

public slots:
    void removeAllShapes();
    void removeShapes();
    void copy();
    void paste();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    QList<VShape*>* copiedShapes= nullptr;
    QPointF delta = QPointF(5,5);


signals:
    void sigmousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigmouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigmouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene);
    void sigkeyPressEvent(QKeyEvent* e);
    void sigkeyReleaseEvent(QKeyEvent *e);
    void sigSceneHasChanged();
    void sigRemoveItems();



};

#endif // VSCENE_H
