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
#include "rectangle.h"
#include "ellipse.h"


VScene::VScene(QObject *parent) :
    QGraphicsScene::QGraphicsScene(parent)
{

    copiedShapes = new QList<VShape*>();

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



QList<VShape *>* VScene::getSelectedShapes()
{
    QList<QGraphicsItem*> selectedItemslist = selectedItems();
    QList<VShape*>* selectedShapes = new QList<VShape*>();

    for (QGraphicsItem* selectedItem:  selectedItemslist) {
        VShape* selectedShape = dynamic_cast<VShape*>(selectedItem);
        if(selectedShape!=nullptr) selectedShapes->append(selectedShape);
    }

    return selectedShapes;
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

 void VScene::save(QTextStream &stream)
 {
    QList<QGraphicsItem*> itemsL = items(Qt::AscendingOrder);
    for (int i=0; i<itemsL.count(); ++i) {
        QGraphicsItem* item = itemsL.at(i);
        VShape* shape = dynamic_cast<VShape*>(item);
        if(shape==nullptr) continue;
        stream << shape->serialize();
        if (i<items().count()-1) stream << '\n';
    }
    //    m_undoStack->setClean();
 }

 void VScene::load(QTextStream &stream)
 {
     while(!stream.atEnd())
     {
        QString line = stream.readLine();
        QStringList lineElements = line.split(' ');
        if (lineElements.isEmpty()) continue;
        QString shapeId = lineElements.at(0);

        QGraphicsItem* currentShape = nullptr;
        if(shapeId == "rectangle") VRectangle::deSerialize(line, this);
        if(shapeId == "ellipse") ellipse::deSerialize(line, this);
        //if (currentShape==nullptr) continue;
     }
 }


 bool VScene::isEmpty()
 {
    QList<QGraphicsItem*>* shapes = getShapes();
    bool val = shapes->isEmpty();
    delete shapes;
    return val;
 }

 void VScene::selectAll()
 {
    QList<QGraphicsItem *> itemsL =  items();
    for(QGraphicsItem* item : itemsL){
        item->setSelected(true);
    }
    emit sigSceneHasChanged();
 }

 void VScene::sceneHasChanged()
 {
    emit sigSceneHasChanged();
 }

void VScene::deselectAll()
{
    QList<QGraphicsItem *> selectedItemsL = selectedItems();

    for(QGraphicsItem* selectedItem : selectedItemsL){
        selectedItem->setSelected(false);
    }
    emit sigSceneHasChanged();
}


void VScene::removeAllShapes()
{
    QList<QGraphicsItem*>* shapes = getShapes();
    for (QGraphicsItem* shape: *shapes) {
        removeItem(shape);
        delete shape;
    }
    delete shapes;
    emit sigSceneHasChanged();
}

void VScene::removeShapes()
{
    QList<QGraphicsItem*> selectedItemslist = selectedItems();

    foreach (QGraphicsItem* item, selectedItemslist) {
        removeItem(item);
        delete item;
    }
    emit sigRemoveItems();
    emit sigSceneHasChanged();
}

void VScene::copy()
{

    for(VShape* copiedShape : *copiedShapes){
        delete copiedShape;
    }
    copiedShapes->clear();

    delta = QPointF(5,5);
    QList<VShape *>* selectedShapes = getSelectedShapes();
    for(VShape* selectedShape : *selectedShapes){
        copiedShapes->append(selectedShape->clone());
        selectedShape->setSelected(false);
    }
    delete selectedShapes;
}

void VScene::paste()
{
    for(VShape* copiedShape : *copiedShapes){
        //copiedShape->setSelected(false);
        VShape* copy = copiedShape->clone();
        copy->MoveBy(delta);
        copy->setVisible(true);
        copy->setSelected(true);
        delta+=QPointF(5,5);
    }
    emit sigSceneHasChanged();
}






void VScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmousePressEvent(mouseEvent, this);
    emit sigSceneHasChanged();
}



void VScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmouseMoveEvent(mouseEvent, this);
    emit sigSceneHasChanged();
}



void VScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit sigmouseReleaseEvent(mouseEvent, this);
    emit sigSceneHasChanged();
}


void VScene::keyPressEvent(QKeyEvent *keyEvent)
{

//    if(keyEvent->key()==Qt::Key_Backspace || keyEvent->key()==Qt::Key_Delete){
//        removeShapes();
//    }

//    if(keyEvent->matches(QKeySequence::Copy)){
//        copy();
//    }

    QGraphicsScene::keyPressEvent(keyEvent);
    emit sigkeyPressEvent(keyEvent);
    emit sigSceneHasChanged();
}




void VScene::keyReleaseEvent(QKeyEvent *keyEvent)
{

//    if(keyEvent->matches(QKeySequence::Paste)){
//        paste();
//    }

    QGraphicsScene::keyReleaseEvent(keyEvent);
    emit sigkeyReleaseEvent(keyEvent);
    emit sigSceneHasChanged();
}



