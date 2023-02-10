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
#include "vdeserializer.h"

/**
 * @details Permet de gérer la scene sur laquelle les formes seront placées.
 */

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

/**
 * @brief VScene::getSelectedShape
 * @return VShape* 
 * @details Retourne le type de shape de l'item selectionné.
 */
VShape *VScene::getSelectedShape()
{
    QList<QGraphicsItem*> selectedItemslist = selectedItems();
    if(selectedItemslist.empty()) return NULL;

    VShape* selectedShape = dynamic_cast<VShape*>(selectedItemslist.at(0));
    return (selectedShape==nullptr)? NULL:selectedShape;
}


/**
 * @brief VScene::getSelectedShapes
 * @return QList<VShape *>* 
 * @details Retourne une liste des shapes selectionnées.
 */
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


/**
 * @brief VScene::getShapes
 * @return QList<QGraphicsItem*>*
 * @details Retourne une liste de QGraphicsItem correspondant aux items selectionnés.
 */
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


/**
 * @brief VScene::save
 * @param stream 
 * @details Permet de sauvegarder la scene.
 */
 void VScene::save(QTextStream &stream)
 {
    QList<QGraphicsItem*> itemsL = items(Qt::AscendingOrder);
    for (int i=0; i<itemsL.count(); ++i) {
        QGraphicsItem* item = itemsL.at(i);
        VShape* shape = dynamic_cast<VShape*>(item);
        if(shape==nullptr) continue;
        shape->Accept(&serializeVisitor);
        stream << serializeVisitor.getResult();
        if (i<items().count()-1) stream << '\n';
    }
    //    m_undoStack->setClean();
 }

/**
 * @brief VScene::load
 * @param stream 
 * @details Permet de charger la scene.
 */
 void VScene::load(QTextStream &stream)
 {
     while(!stream.atEnd())
     {
        QString line = stream.readLine();
        QStringList lineElements = line.split(' ');
        if (lineElements.isEmpty()) continue;
        QString shapeId = lineElements.at(0);

        QGraphicsItem* currentShape = nullptr;
        if(shapeId == "rectangle") VDeserializer::deSerializeRectangle(line, this);
        if(shapeId == "ellipse") VDeserializer::deSerializeEllipse(line, this);
        //if (currentShape==nullptr) continue;
     }
 }


/**
 * @brief VScene::isEmpty
 * @return true Si la scene est vide
 * @return false Si la scene n'est pas vide
 */
 bool VScene::isEmpty()
 {
    QList<QGraphicsItem*>* shapes = getShapes();
    bool val = shapes->isEmpty();
    delete shapes;
    return val;
 }

/**
 * @brief VScene::selectAll
 * @details Permet de sélectionner tous les QGraphicsItem de la scene.
 */
 void VScene::selectAll()
 {
    QList<QGraphicsItem *> itemsL =  items();
    for(QGraphicsItem* item : itemsL){
        item->setSelected(true);
    }
    emit sigSceneHasChanged();
 }

/**
 * @brief VScene::sceneHasChanged
 * @details Émet un signal si la scene a changé.
 */
 void VScene::sceneHasChanged()
 {
    emit sigSceneHasChanged();
 }

/**
 * @brief VScene::deselectAll
 * @details Permet de déselectionner tous les QGraphicsItem.
 */
void VScene::deselectAll()
{
    QList<QGraphicsItem *> selectedItemsL = selectedItems();

    for(QGraphicsItem* selectedItem : selectedItemsL){
        selectedItem->setSelected(false);
    }
    emit sigSceneHasChanged();
}

/**
 * @brief VScene::removeAllShapes
 * @details Permet de supprimer tous les QGraphicsItem de la scene.
 */
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

/**
 * @brief VScene::removeShapes
 * @details Permet de supprimer les formes sélectionnées.
 */
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

/**
 * @brief VScene::copy
 * @details Permet de copier le contenu de la scene.
 */
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

/**
 * @brief VScene::paste
 * @details Permet de coller des formes à partir de copiedShapes.
 */
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



