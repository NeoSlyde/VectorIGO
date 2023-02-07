#include "vscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QtMath>
#include <algorithm>
#include <iostream>
#include "vgrabber.h"
#include <QKeyEvent>
#include "commands.h"


VScene::VScene(QObject *parent, QUndoStack *undoStack) :
    QGraphicsScene::QGraphicsScene(parent), _undoStack(undoStack)
{
    int width_ = 800;
    int height_ = 600;
    setSceneRect(0,0,width_,height_);
}

void VScene::mousePressEventDefault(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void VScene::mouseMoveEventDefault(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void VScene::mouseReleaseEventDefault(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

VShape *VScene::getSelectedShape()
{
    QList<QGraphicsItem*> selectedItemslist = selectedItems();
    if(selectedItemslist.empty()) return NULL;

    VShape* selectedShape = dynamic_cast<VShape*>(selectedItemslist.at(0));
    return (selectedShape==nullptr)? NULL:selectedShape;
}


 QList<QGraphicsItem*>* VScene::getShapes()
{
    QList<QGraphicsItem*> itemsL = items();
    QList<QGraphicsItem*>* shapes = new QList<QGraphicsItem*>();
    foreach (QGraphicsItem* item, itemsL) {
        VShape* shape = dynamic_cast<VShape*>(item);
        if(shape!=nullptr){
            shapes->append(item);
        }
    }
    return shapes;
}


void VScene::removeAllShapes()
{
    QList<QGraphicsItem*>* shapes = getShapes();
    for (QGraphicsItem* shape: *shapes) {
        removeItem(shape);
        delete shape;
    }
}


void VScene::addShape(VShape *shape) {
    addItem(static_cast<QGraphicsItem>(shape));
    QUndoCommand *addCommand = new AddCommand(this, shape);
    _undoStack->push(addCommand);
}

void VScene::removeShape(VShape *shape) {
    removeItem(shape);
    QUndoCommand *removeCommand = new RemoveCommand(this, shape);
    _undoStack->push(removeCommand);
}




void VScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmousePressEvent(mouseEvent, this);
}



void VScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmouseMoveEvent(mouseEvent, this);
}



void VScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmouseReleaseEvent(mouseEvent, this);
}


void VScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->key()==Qt::Key_Delete){
        QList<QGraphicsItem*> selectedItemslist = selectedItems();

        foreach (QGraphicsItem* item, selectedItemslist) {
            removeItem(item);
            delete item;
        }
        emit sigRemoveItems();
        return;
    }

    QGraphicsScene::keyPressEvent(keyEvent);
}



