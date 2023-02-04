#include "ellipse.h"
#include <QPainter>
#include <QObject>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>
#include "vgrabber.h"
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include "vcolorpicker.h"



ellipse::ellipse(QObject *parent, QGraphicsEllipseItem *parentGraphic):
    VShape(parent),
    ellipse::QGraphicsEllipseItem(parentGraphic)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    strokeColor = QColor(Qt::red);
    FillColor = QColor(Qt::blue);
    thickness = 3;


    grabber1 = new VGrabber(0-VGrabber::width(), 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber1, &VGrabber::sigMousePressEvent,this, &ellipse::pressResizeFromTopLeft);
    QObject::connect(grabber1, &VGrabber::sigMouseMoveEvent,this, &ellipse::moveResizeFromTopLeft);

    grabber2 = new VGrabber(boundingRect().width(), 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber2, &VGrabber::sigMousePressEvent, this, &ellipse::pressResizeFromTopRight);
    QObject::connect(grabber2, &VGrabber::sigMouseMoveEvent, this, &ellipse::moveResizeFromTopRight);

    grabber3 = new VGrabber(boundingRect().width() , boundingRect().height(), nullptr, this);
    QObject::connect(grabber3, &VGrabber::sigMousePressEvent,this, &ellipse::pressResizeFromBtmRight);
    QObject::connect(grabber3, &VGrabber::sigMouseMoveEvent,this, &ellipse::moveResizeFromBtmRight);

    grabber4 = new VGrabber(0-VGrabber::width(), boundingRect().height(), nullptr, this);
    QObject::connect(grabber4, &VGrabber::sigMousePressEvent,this, &ellipse::pressResizeFromBtmLeft);
    QObject::connect(grabber4, &VGrabber::sigMouseMoveEvent,this, &ellipse::moveResizeFromBtmLeft);

    grabber5 = new VGrabber(boundingRect().width()/2-VGrabber::width()/2, 0-VGrabber::height(), nullptr, this);
    QObject::connect(grabber5, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromTop);

    grabber6 = new VGrabber(boundingRect().width(), boundingRect().height()/2-VGrabber::height()/2, nullptr, this);
    QObject::connect(grabber6, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromRight);

    grabber7 = new VGrabber(boundingRect().width()/2-VGrabber::width()/2, boundingRect().height(), nullptr, this);
    QObject::connect(grabber7, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromBtm);

    grabber8 = new VGrabber(0-VGrabber::width(), boundingRect().height()/2-VGrabber::height()/2, nullptr, this);
    QObject::connect(grabber8, &VGrabber::sigMouseMoveEvent,this, &ellipse::resizeFromLeft);
    }

void ellipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    setPen(QPen(strokeColor, thickness));
        setBrush(FillColor);

        if(thickness<=0.01){
            setPen(QPen(Qt::transparent));
        }
    QGraphicsEllipseItem::paint(painter, option, widget);
}

QVariant ellipse::itemChange(GraphicsItemChange change, const QVariant &value)
{
   if (change == ItemPositionChange && scene()) {
    QPointF newPos = value.toPointF();
    QRectF rect = scene()->sceneRect();
    if (!rect.contains(newPos)) {
        newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
        newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        return newPos;
        }
    }

    if (change == QGraphicsEllipseItem::ItemSelectedHasChanged && scene() )
    {
        updateGrabbersVisibility();
    }
    if (scene()  && change == QGraphicsItem::ItemPositionHasChanged)
    {
        updateGrabbersPosition();
        updateGrabbersVisibility();
    }


    return QGraphicsItem::itemChange(change, value);
}

void ellipse::updateGrabbersVisibility()
{
    if(isSelected()){
        scene()->selectedItems().count();

        VShape* selectedShape = dynamic_cast<VShape*>(scene()->selectedItems().at(0));


        std::cout << "ELLIPSE SELECTED " << selectedShape->toString().toStdString() <<std::endl;


        grabber1->setVisible(true);
        grabber2->setVisible(true);
        grabber3->setVisible(true);
        grabber4->setVisible(true);
        grabber5->setVisible(true);
        grabber6->setVisible(true);
        grabber7->setVisible(true);
        grabber8->setVisible(true);
        if(rotation()!=0){
            grabber1->setVisible(false);
            grabber2->setVisible(false);
            grabber3->setVisible(false);
            grabber4->setVisible(false);
        }
    }
    else{
        std::cout << "ELLipse NOT SELECTED" << scene()->selectedItems().count() <<std::endl;
        grabber1->setVisible(false);
        grabber2->setVisible(false);
        grabber3->setVisible(false);
        grabber4->setVisible(false);
        grabber5->setVisible(false);
        grabber6->setVisible(false);
        grabber7->setVisible(false);
        grabber8->setVisible(false);
    }
}

void ellipse::updateGrabbersPosition()
{
    prepareGeometryChange();
    grabber1->updatePosition(0-VGrabber::width(), 0-VGrabber::height());
    grabber2->updatePosition(boundingRect().width(), 0-VGrabber::height());
    grabber3->updatePosition(boundingRect().width() , boundingRect().height());
    grabber4->updatePosition(0-VGrabber::width(),boundingRect().height());
    grabber5->updatePosition(boundingRect().width()/2-VGrabber::width()/2, 0-VGrabber::height());
    grabber6->updatePosition(boundingRect().width(), boundingRect().height()/2-VGrabber::height()/2);
    grabber7->updatePosition(boundingRect().width()/2-VGrabber::width()/2, boundingRect().height());
    grabber8->updatePosition(0-VGrabber::width(), boundingRect().height()/2-VGrabber::height()/2);
    update();

}

void ellipse::setWidth(qreal inputWidth)
{
    QRectF rec = rect();
    rec.setWidth(inputWidth);
    setRect(rec);
    updateGrabbersPosition();
}

void ellipse::setHeight(qreal inputHeight)
{
    QRectF rec = rect();
    rec.setHeight(inputHeight);
    setRect(rec);
    updateGrabbersPosition();

}

QLayout* ellipse::getPanel()
{
    updateGrabbersVisibility();
    std::cout << "GET ELLIPSE PANEL" << std::endl;
    QVBoxLayout* panel = new QVBoxLayout();

    QLabel* labelSettings = new QLabel();
    labelSettings->setAlignment(Qt::AlignCenter);
    labelSettings->setText(QString("Settings"));
    panel->addWidget(labelSettings);
    labelSettings->setStyleSheet("QLabel { padding-bottom: 10px; }");
    QFont font = labelSettings->font();
    font.setBold(true);
    font.setPointSize(14);
    labelSettings->setFont(font);
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    panel->addWidget(line);


    QLabel* lableTL = new QLabel();
    lableTL->setAlignment(Qt::AlignCenter);
    lableTL->setText(QString("Top Left Coordinates"));
    panel->addWidget(lableTL);

    QHBoxLayout* layoutCoordTL = new QHBoxLayout();
    panel->addItem(layoutCoordTL);

    QLabel* labelTLX = new QLabel();
    labelTLX->setText(QString("X:"));
    layoutCoordTL->addWidget(labelTLX);

    QLineEdit* lineEditTLX = new QLineEdit();
    lineEditTLX->setText( QString::number(mapToScene(boundingRect().topLeft()).x()) );
    lineEditTLX->setReadOnly(true);
    lineEditTLX->setAlignment(Qt::AlignCenter);
    //lineEditTPX->setMaximumWidth(38);
    layoutCoordTL->addWidget(lineEditTLX);

    QLabel* labelTLY = new QLabel();
    labelTLY->setText(QString("Y:"));
    layoutCoordTL->addWidget(labelTLY);

    QLineEdit* lineEditTLY = new QLineEdit();
    lineEditTLY->setText( QString::number(mapToScene(boundingRect().topLeft()).y()) );
    lineEditTLY->setReadOnly(true);
    lineEditTLY->setAlignment(Qt::AlignCenter);
    layoutCoordTL->addWidget(lineEditTLY);



    QLabel* lableTR = new QLabel();
    lableTR->setAlignment(Qt::AlignCenter);
    lableTR->setText(QString("Top Right Coordinates"));
    panel->addWidget(lableTR);

    QHBoxLayout* layoutCoordTR = new QHBoxLayout();
    panel->addItem(layoutCoordTR);

    QLabel* labelTRX = new QLabel();
    labelTRX->setText(QString("X:"));
    layoutCoordTR->addWidget(labelTRX);

    QLineEdit* lineEditTRX = new QLineEdit();
    lineEditTRX->setText( QString::number(mapToScene(boundingRect().topRight()).x()) );
    lineEditTRX->setReadOnly(true);
    lineEditTRX->setAlignment(Qt::AlignCenter);
    layoutCoordTR->addWidget(lineEditTRX);

    QLabel* labelTRY = new QLabel();
    labelTRY->setText(QString("Y:"));
    layoutCoordTR->addWidget(labelTRY);

    QLineEdit* lineEditTRY = new QLineEdit();
    lineEditTRY->setText( QString::number(mapToScene(boundingRect().topRight()).y()) );
    lineEditTRY->setReadOnly(true);
    lineEditTRY->setAlignment(Qt::AlignCenter);
    layoutCoordTR->addWidget(lineEditTRY);


    QLabel* lableBR = new QLabel();
    lableBR->setAlignment(Qt::AlignCenter);
    lableBR->setText(QString("Bottom Right Coordinates"));
    panel->addWidget(lableBR);

    QHBoxLayout* layoutCoordBR = new QHBoxLayout();
    panel->addItem(layoutCoordBR);

    QLabel* labelBRX = new QLabel();
    labelBRX->setText(QString("X:"));
    layoutCoordBR->addWidget(labelBRX);

    QLineEdit* lineEditBRX = new QLineEdit();
    lineEditBRX->setText( QString::number(mapToScene(boundingRect().bottomRight()).x()) );
    lineEditBRX->setReadOnly(true);
    lineEditBRX->setAlignment(Qt::AlignCenter);
    //lineEditTPX->setMaximumWidth(38);
    layoutCoordBR->addWidget(lineEditBRX);

    QLabel* labelBRY = new QLabel();
    labelBRY->setText(QString("Y:"));
    layoutCoordBR->addWidget(labelBRY);

    QLineEdit* lineEditBRY = new QLineEdit();
    lineEditBRY->setText( QString::number(mapToScene(boundingRect().bottomRight()).y()) );
    lineEditBRY->setReadOnly(true);
    lineEditBRY->setAlignment(Qt::AlignCenter);
    layoutCoordBR->addWidget(lineEditBRY);



    QLabel* lableBL = new QLabel();
    lableBL->setAlignment(Qt::AlignCenter);
    lableBL->setText(QString("Bottom Left Coordinates"));
    panel->addWidget(lableBL);

    QHBoxLayout* layoutCoordBL = new QHBoxLayout();
    panel->addItem(layoutCoordBL);

    QLabel* labelBLX = new QLabel();
    labelBLX->setText(QString("X:"));
    layoutCoordBL->addWidget(labelBLX);

    QLineEdit* lineEditBLX = new QLineEdit();
    lineEditBLX->setText( QString::number(mapToScene(boundingRect().bottomLeft()).x()) );
    lineEditBLX->setReadOnly(true);
    lineEditBLX->setAlignment(Qt::AlignCenter);
    layoutCoordBL->addWidget(lineEditBLX);

    QLabel* labelBLY = new QLabel();
    labelBLY->setText(QString("Y:"));
    layoutCoordBL->addWidget(labelBLY);

    QLineEdit* lineEditBLY = new QLineEdit();
    lineEditBLY->setText( QString::number(mapToScene(boundingRect().bottomLeft()).y()) );
    lineEditBLY->setReadOnly(true);
    lineEditBLY->setAlignment(Qt::AlignCenter);
    //lineEditTPY->setMaximumWidth(38);
    layoutCoordBL->addWidget(lineEditBLY);

//
//
    QHBoxLayout* layoutWidth = new QHBoxLayout();
    layoutWidth->setAlignment(Qt::AlignLeft);
    panel->addItem(layoutWidth);

    QLabel* labelWidth = new QLabel();
    labelWidth->setAlignment(Qt::AlignCenter);
    labelWidth->setText(QString("Width "));
    layoutWidth->addWidget(labelWidth);

    QSpinBox* spinBoxWidth = new QSpinBox();
    spinBoxWidth->setRange(4, INT_MAX);
    spinBoxWidth->setValue(boundingRect().width());
    spinBoxWidth->setAlignment(Qt::AlignCenter);
    connect(  spinBoxWidth, &QSpinBox::valueChanged,  this, &ellipse::setWidth );
    layoutWidth->addWidget(spinBoxWidth);

//
//
    QHBoxLayout* layoutHeight = new QHBoxLayout();
    panel->addItem(layoutHeight);
    layoutHeight->setAlignment(Qt::AlignLeft);

    QLabel* labelHeight = new QLabel();
    labelHeight->setAlignment(Qt::AlignCenter);
    labelHeight->setText(QString("Height"));
    layoutHeight->addWidget(labelHeight);

    QSpinBox* spinBoxHeight = new QSpinBox();
    spinBoxHeight->setRange(4, INT_MAX);
    spinBoxHeight->setValue(boundingRect().height());
    spinBoxHeight->setAlignment(Qt::AlignCenter);
    connect(  spinBoxHeight, &QSpinBox::valueChanged,  this, &ellipse::setHeight );
    layoutHeight->addWidget(spinBoxHeight);

//
//
    QHBoxLayout* layoutRoata = new QHBoxLayout();
    panel->addItem(layoutRoata);
    layoutRoata->setAlignment(Qt::AlignLeft);

    QLabel* labelRota = new QLabel();
    labelRota->setAlignment(Qt::AlignCenter);
    labelRota->setText(QString("Rotation"));
    layoutRoata->addWidget(labelRota);

    QSpinBox* spinBoxRota = new QSpinBox();
    spinBoxRota->setRange(0, 360);
    spinBoxRota->setValue(rotation());
    spinBoxRota->setAlignment(Qt::AlignCenter);
    connect(  spinBoxRota, &QSpinBox::valueChanged,  this, &ellipse::slotRotate );
    layoutRoata->addWidget(spinBoxRota);

//
    QHBoxLayout* layoutThickness = new QHBoxLayout();
    panel->addItem(layoutThickness);
    layoutThickness->setAlignment(Qt::AlignLeft);

    QLabel* labelThickness = new QLabel();
    labelThickness->setAlignment(Qt::AlignCenter);
    labelThickness->setText(QString("Thickness"));
    layoutThickness->addWidget(labelThickness);

    QDoubleSpinBox* spinBoxThickness = new QDoubleSpinBox();
    spinBoxThickness->setRange(0, 40);
    spinBoxThickness->setValue(thickness);
    spinBoxThickness->setAlignment(Qt::AlignCenter);
    connect(  spinBoxThickness, &QDoubleSpinBox::valueChanged,  this, &ellipse::updateThickness );
    layoutThickness->addWidget(spinBoxThickness);
//
    QLabel* labelColor = new QLabel();
    labelColor->setAlignment(Qt::AlignCenter);
    labelColor->setText(QString("Color"));
    panel->addWidget(labelColor);

    QHBoxLayout* layoutColor = new QHBoxLayout();
    panel->addItem(layoutColor);

    QLabel* labelSC = new QLabel();
    labelSC->setAlignment(Qt::AlignCenter);
    labelSC->setText(QString("Stroke"));
    layoutColor->addWidget(labelSC);

    VColorPicker* colorPickerStroke = new VColorPicker();
    colorPickerStroke->setColor(strokeColor);
    connect(  colorPickerStroke, &VColorPicker::sigColorChanged,  this, &ellipse::updateStrokeColor );
    layoutColor->addWidget(colorPickerStroke);

    QLabel* labelFC = new QLabel();
    labelFC->setAlignment(Qt::AlignCenter);
    labelFC->setText(QString("Fill"));
    layoutColor->addWidget(labelFC);

    VColorPicker* colorPickerFill = new VColorPicker();
    colorPickerFill->setColor(FillColor);
    connect(  colorPickerFill, &VColorPicker::sigColorChanged,  this, &ellipse::updateFillColor );
    layoutColor->addWidget(colorPickerFill);

    QHBoxLayout* layoutZvalue = new QHBoxLayout();
    panel->addItem(layoutZvalue);
    layoutZvalue->setAlignment(Qt::AlignLeft);

    QLabel* labelZvalue = new QLabel();
    labelZvalue->setAlignment(Qt::AlignCenter);
    labelZvalue->setText(QString("Layer / Z-Axis"));
    layoutZvalue->addWidget(labelZvalue);

    QSpinBox* spinBoxZvalue = new QSpinBox();
    spinBoxZvalue->setRange(0, 100);
    spinBoxZvalue->setValue(zValue());
    spinBoxZvalue->setAlignment(Qt::AlignCenter);
    connect(  spinBoxZvalue, &QSpinBox::valueChanged,  this, &ellipse::updateZvalue );
    layoutZvalue->addWidget(spinBoxZvalue);


    return panel;
}

qreal ellipse::distance(QPointF p1, QPointF p2)
{
    return sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2) * 1.0);
}

void ellipse::resize(QPointF moveDest )
{
    std::cout << "GRABBER SIG RECEIVE" << std::endl;
    int x_top_left = std::min(anchorGrabberDeformation.x(), moveDest.x());
    int y_top_left = std::min(anchorGrabberDeformation.y(), moveDest.y());

    int width = std::abs(moveDest.x()-anchorGrabberDeformation.x());
    int height = std::abs(moveDest.y()-anchorGrabberDeformation.y());

    setPos(x_top_left,y_top_left);
    setRect(0, 0, width, height);
    updateGrabbersPosition();
}



void ellipse::updateStrokeColor(QColor col)
{
    strokeColor = col;
    update();
}

void ellipse::updateFillColor(QColor col)
{
    FillColor = col;
    update();
}
void ellipse::updateThickness(qreal thickness)
{
    this->thickness = thickness;
    update();
}
void ellipse::doRotation(int rota)
{
    setTransformOriginPoint(boundingRect().center());
    setRotation(rota);
    updateGrabbersVisibility();
}


void ellipse::moveResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromTopLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().bottomRight());
}

void ellipse::moveResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromTopRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().bottomLeft());
}

void ellipse::moveResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromBtmRight(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().topLeft());
}

void ellipse::moveResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    resize(event->scenePos());
}
void ellipse::pressResizeFromBtmLeft(QGraphicsSceneMouseEvent *event)
{
    anchorGrabberDeformation = mapToScene(boundingRect().topRight());
}

void ellipse::resizeFromTop(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);

    QRectF rec = rect();
    rec.setHeight(  (contains(mapFromParent(p2)))? rec.height()-dist:rec.height()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;
    if(contains(mapFromParent(p2)))
        moveBy(+dist*cos(rotation()*M_PI/180.0 + M_PI/2), +dist*sin(rotation()*M_PI/180.0 + M_PI/2 ));
    else
        moveBy(-dist*cos(rotation()*M_PI/180.0 + M_PI/2), -dist*sin(rotation()*M_PI/180.0 + M_PI/2 ));

    setRect(rec);
    updateGrabbersPosition();

}
void ellipse::resizeFromBtm(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);
    QRectF rec = rect();
    rec.setHeight(  (contains(mapFromParent(p2)))? rec.height()-dist:rec.height()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;

    setRect(rec);
    updateGrabbersPosition();

}
void ellipse::resizeFromRight(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
        QPointF p1 = event->lastScenePos();
        QPointF p2 = event->scenePos();
        qreal dist = distance(p1,p2);

        QRectF rec = rect();
        rec.setWidth(  (contains(mapFromParent(p2)))? rec.width()-dist:rec.width()+dist );
        if(rec.width()<=4 || rec.height()<=4) return;

        setRect(rec);
        updateGrabbersPosition();

}
void ellipse::resizeFromLeft(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    QPointF p1 = event->lastScenePos();
    QPointF p2 = event->scenePos();
    qreal dist = distance(p1,p2);

    QRectF rec = rect();
    rec.setWidth(  (contains(mapFromParent(p2)))? rec.width()-dist:rec.width()+dist );
    if(rec.width()<=4 || rec.height()<=4) return;
    if(contains(mapFromParent(p2)))
        moveBy(+dist*cos(rotation()*M_PI/180.0), +dist*sin(rotation()*M_PI/180.0));
    else
        moveBy(-dist*cos(rotation()*M_PI/180.0), -dist*sin(rotation()*M_PI/180.0));

    setRect(rec);
    updateGrabbersPosition();


}

void ellipse::slotResizeFromTopLeftX(int x)
{
    resize( QPointF(x, mapToParent(rect().topLeft()).y())  );
    anchorGrabberDeformation = mapToParent(rect().bottomRight());

}
void ellipse::slotResizeFromTopLeftY(int y)
{
    resize( QPointF(mapToParent(rect().topLeft()).x(), y) );
    anchorGrabberDeformation = mapToParent(rect().bottomRight());

}


void ellipse::slotRotate(int rota)
{
    doRotation(rota);
}
void ellipse::updateZvalue(int z)
{
    setZValue(z);
}

VShape* ellipse::clone()
{
    ellipse* newEllipse = new ellipse();
    scene()->addItem(newEllipse);
    newEllipse->setPos(pos());
    newEllipse->setRect(rect());
    newEllipse->setRotation(rotation());
    newEllipse->updateStrokeColor(strokeColor);
    newEllipse->updateFillColor(FillColor);
    newEllipse->updateThickness(thickness);
    newEllipse->setVisible(false);
    return newEllipse;
}

void ellipse::setVisible(bool value)
{
    QGraphicsItem::setVisible(value);
    updateGrabbersPosition();
    updateGrabbersVisibility();
}

void ellipse::setSelected(bool value)
{
    QGraphicsItem::setSelected(value);
}

void ellipse::MoveBy(QPointF delta)
{
    QGraphicsItem::moveBy(delta.x(),delta.y());
}

QString ellipse::serialize()
{
    QString posX = QString::number(pos().x());
    QString posY = QString::number(pos().y());
    QString rectX = QString::number(rect().topLeft().x());
    QString rectY = QString::number(rect().topLeft().y());
    QString rectW = QString::number(rect().width());
    QString rectH = QString::number(rect().height());
    QString rota = QString::number(rotation());
    QString stroke = strokeColor.name();
    QString fill = FillColor.name();
    QString thick = QString::number(thickness);

    QString description = toString() +' '+posX+' '+posY+' '+rectX+' '+rectY+' '+rectW+' '+rectH+' '+rota+' '+stroke+' '+fill+' '+thick;
    return description;
}

QGraphicsItem* ellipse::deSerialize(QString input, QGraphicsScene* parentScene)
{
    QStringList elements = input.split(' ');
    if (elements.count()!=11) return nullptr;

    qreal posX, posY, rectX, rectY, rectW, rectH, rota, thick;
    QColor stroke, fill;

    try {
        posX = elements.at(1).toDouble();
        posY = elements.at(2).toDouble();
        rectX = elements.at(3).toDouble();
        rectY = elements.at(4).toDouble();
        rectW = elements.at(5).toDouble();
        rectH = elements.at(6).toDouble();
        rota = elements.at(7).toDouble();
        stroke = QColor(elements.at(8));
        fill = QColor(elements.at(9));
        thick = elements.at(10).toDouble();
    } catch(...) {
        return nullptr;
    }

    ellipse* newEllipse = new ellipse();
    parentScene->addItem(newEllipse);
    newEllipse->setPos(posX,posY);
    newEllipse->setRect(QRectF(rectX,rectY, rectW, rectH));
    newEllipse->setRotation(rota);
    newEllipse->updateStrokeColor(stroke);
    newEllipse->updateFillColor(fill);
    newEllipse->updateThickness(thick);
    newEllipse->updateGrabbersPosition();

    std::cout << "ELLIPSE DESERIALIZED" << std::endl;


    return newEllipse;
}



QString ellipse::toString()
{
    return QString("ellipse");
}

