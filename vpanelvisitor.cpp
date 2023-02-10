#include "vpanelvisitor.h"
#include "vcolorpicker.h"
#include "rectangle.h"
#include "ellipse.h"
#include <QPointF>
#include <QRectF>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <iostream>
#include <QString>


/**
 * @details Classe suivant le patron de conception Visitor et qui permet de visiter chaque shape pour en
 * extraire leurs caractéristiques propres notamment pour les afficher sur le panneau à droite.
 * @param parent 
 */

VPanelVisitor::VPanelVisitor(QObject *parent): QObject{parent}
{
}



/**
 * @brief VPanelVisitor::visit
 * @param rectangle 
 * @details Visite un rectangle.
 */
void VPanelVisitor::visit( VRectangle *rectangle)
{
    std::cout << "GET PANEL" << std::endl;
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
//

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
    lineEditTLX->setText( QString::number( rectangle->mapToScene(rectangle->rect().topLeft()).x() ) );
    lineEditTLX->setReadOnly(true);
    lineEditTLX->setAlignment(Qt::AlignCenter);
    //lineEditTPX->setMaximumWidth(38);
    layoutCoordTL->addWidget(lineEditTLX);

    QLabel* labelTLY = new QLabel();
    labelTLY->setText(QString("Y:"));
    layoutCoordTL->addWidget(labelTLY);

    QLineEdit* lineEditTLY = new QLineEdit();
    lineEditTLY->setText( QString::number(rectangle->mapToScene(rectangle->rect().topLeft()).y()) );
    lineEditTLY->setReadOnly(true);
    lineEditTLY->setAlignment(Qt::AlignCenter);
    //lineEditTPY->setMaximumWidth(38);
    layoutCoordTL->addWidget(lineEditTLY);

//

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
    lineEditTRX->setText( QString::number(rectangle->mapToScene(rectangle->rect().topRight()).x()) );
    lineEditTRX->setReadOnly(true);
    lineEditTRX->setAlignment(Qt::AlignCenter);
    //lineEditTRX->setMaximumWidth(38);
    layoutCoordTR->addWidget(lineEditTRX);

    QLabel* labelTRY = new QLabel();
    labelTRY->setText(QString("Y:"));
    layoutCoordTR->addWidget(labelTRY);

    QLineEdit* lineEditTRY = new QLineEdit();
    lineEditTRY->setText( QString::number(rectangle->mapToScene(rectangle->rect().topRight()).y()) );
    lineEditTRY->setReadOnly(true);
    lineEditTRY->setAlignment(Qt::AlignCenter);
    //lineEditTRY->setMaximumWidth(38);
    layoutCoordTR->addWidget(lineEditTRY);
//
//

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
    lineEditBRX->setText( QString::number(rectangle->mapToScene(rectangle->rect().bottomRight()).x()) );
    lineEditBRX->setReadOnly(true);
    lineEditBRX->setAlignment(Qt::AlignCenter);
    //lineEditTPX->setMaximumWidth(38);
    layoutCoordBR->addWidget(lineEditBRX);

    QLabel* labelBRY = new QLabel();
    labelBRY->setText(QString("Y:"));
    layoutCoordBR->addWidget(labelBRY);

    QLineEdit* lineEditBRY = new QLineEdit();
    lineEditBRY->setText( QString::number(rectangle->mapToScene(rectangle->rect().bottomRight()).y()) );
    lineEditBRY->setReadOnly(true);
    lineEditBRY->setAlignment(Qt::AlignCenter);
    //lineEditTPY->setMaximumWidth(38);
    layoutCoordBR->addWidget(lineEditBRY);

//
//

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
    lineEditBLX->setText( QString::number(rectangle->mapToScene(rectangle->rect().bottomLeft()).x()) );
    lineEditBLX->setReadOnly(true);
    lineEditBLX->setAlignment(Qt::AlignCenter);
    //lineEditTPX->setMaximumWidth(38);
    layoutCoordBL->addWidget(lineEditBLX);

    QLabel* labelBLY = new QLabel();
    labelBLY->setText(QString("Y:"));
    layoutCoordBL->addWidget(labelBLY);

    QLineEdit* lineEditBLY = new QLineEdit();
    lineEditBLY->setText( QString::number(rectangle->mapToScene(rectangle->rect().bottomLeft()).y()) );
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
    spinBoxWidth->setValue(rectangle->rect().width());
    spinBoxWidth->setAlignment(Qt::AlignCenter);
    connect(  spinBoxWidth, &QSpinBox::valueChanged,  rectangle, &VRectangle::setWidth );
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
    spinBoxHeight->setValue(rectangle->rect().height());
    spinBoxHeight->setAlignment(Qt::AlignCenter);
    connect(  spinBoxHeight, &QSpinBox::valueChanged,  rectangle, &VRectangle::setHeight );
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
    spinBoxRota->setValue(rectangle->rotation());
    spinBoxRota->setAlignment(Qt::AlignCenter);
    connect(  spinBoxRota, &QSpinBox::valueChanged,  rectangle, &VRectangle::slotRotate );
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
    spinBoxThickness->setValue(rectangle->getThickness());
    spinBoxThickness->setAlignment(Qt::AlignCenter);
    connect(  spinBoxThickness, &QDoubleSpinBox::valueChanged,  rectangle, &VRectangle::updateThickness );
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
    colorPickerStroke->setColor(rectangle->getStrokeColor());
    connect(  colorPickerStroke, &VColorPicker::sigColorChanged,  rectangle, &VRectangle::updateStrokeColor );
    layoutColor->addWidget(colorPickerStroke);

    QLabel* labelFC = new QLabel();
    labelFC->setAlignment(Qt::AlignCenter);
    labelFC->setText(QString("Fill"));
    layoutColor->addWidget(labelFC);

    VColorPicker* colorPickerFill = new VColorPicker();
    colorPickerFill->setColor(rectangle->getFillColor());
    connect(  colorPickerFill, &VColorPicker::sigColorChanged,  rectangle, &VRectangle::updateFillColor );
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
    spinBoxZvalue->setValue(rectangle->zValue());
    spinBoxZvalue->setAlignment(Qt::AlignCenter);
    connect(  spinBoxZvalue, &QSpinBox::valueChanged,  rectangle, &VRectangle::updateZvalue );
    layoutZvalue->addWidget(spinBoxZvalue);

    _panel = panel;
}
















/**
 * @brief VPanelVisitor::visit
 * @param ell 
 * @details Visite une ellipse.
 */
void VPanelVisitor::visit( ellipse* ell)
{
    ell->updateGrabbersVisibility();
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
    lineEditTLX->setText( QString::number(ell->mapToScene(ell->boundingRect().topLeft()).x()) );
    lineEditTLX->setReadOnly(true);
    lineEditTLX->setAlignment(Qt::AlignCenter);
    //lineEditTPX->setMaximumWidth(38);
    layoutCoordTL->addWidget(lineEditTLX);

    QLabel* labelTLY = new QLabel();
    labelTLY->setText(QString("Y:"));
    layoutCoordTL->addWidget(labelTLY);

    QLineEdit* lineEditTLY = new QLineEdit();
    lineEditTLY->setText( QString::number(ell->mapToScene(ell->boundingRect().topLeft()).y()) );
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
    lineEditTRX->setText( QString::number(ell->mapToScene(ell->boundingRect().topRight()).x()) );
    lineEditTRX->setReadOnly(true);
    lineEditTRX->setAlignment(Qt::AlignCenter);
    layoutCoordTR->addWidget(lineEditTRX);

    QLabel* labelTRY = new QLabel();
    labelTRY->setText(QString("Y:"));
    layoutCoordTR->addWidget(labelTRY);

    QLineEdit* lineEditTRY = new QLineEdit();
    lineEditTRY->setText( QString::number(ell->mapToScene(ell->boundingRect().topRight()).y()) );
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
    lineEditBRX->setText( QString::number(ell->mapToScene(ell->boundingRect().bottomRight()).x()) );
    lineEditBRX->setReadOnly(true);
    lineEditBRX->setAlignment(Qt::AlignCenter);
    //lineEditTPX->setMaximumWidth(38);
    layoutCoordBR->addWidget(lineEditBRX);

    QLabel* labelBRY = new QLabel();
    labelBRY->setText(QString("Y:"));
    layoutCoordBR->addWidget(labelBRY);

    QLineEdit* lineEditBRY = new QLineEdit();
    lineEditBRY->setText( QString::number(ell->mapToScene(ell->boundingRect().bottomRight()).y()) );
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
    lineEditBLX->setText( QString::number(ell->mapToScene(ell->boundingRect().bottomLeft()).x()) );
    lineEditBLX->setReadOnly(true);
    lineEditBLX->setAlignment(Qt::AlignCenter);
    layoutCoordBL->addWidget(lineEditBLX);

    QLabel* labelBLY = new QLabel();
    labelBLY->setText(QString("Y:"));
    layoutCoordBL->addWidget(labelBLY);

    QLineEdit* lineEditBLY = new QLineEdit();
    lineEditBLY->setText( QString::number(ell->mapToScene(ell->boundingRect().bottomLeft()).y()) );
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
    spinBoxWidth->setValue(ell->boundingRect().width());
    spinBoxWidth->setAlignment(Qt::AlignCenter);
    connect(  spinBoxWidth, &QSpinBox::valueChanged,  ell, &ellipse::setWidth );
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
    spinBoxHeight->setValue(ell->boundingRect().height());
    spinBoxHeight->setAlignment(Qt::AlignCenter);
    connect(  spinBoxHeight, &QSpinBox::valueChanged,  ell, &ellipse::setHeight );
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
    spinBoxRota->setValue(ell->rotation());
    spinBoxRota->setAlignment(Qt::AlignCenter);
    connect(  spinBoxRota, &QSpinBox::valueChanged,  ell, &ellipse::slotRotate );
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
    spinBoxThickness->setValue(ell->getThickness());
    spinBoxThickness->setAlignment(Qt::AlignCenter);
    connect(  spinBoxThickness, &QDoubleSpinBox::valueChanged,  ell, &ellipse::updateThickness );
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
    colorPickerStroke->setColor(ell->getStrokeColor());
    connect(  colorPickerStroke, &VColorPicker::sigColorChanged,  ell, &ellipse::updateStrokeColor );
    layoutColor->addWidget(colorPickerStroke);

    QLabel* labelFC = new QLabel();
    labelFC->setAlignment(Qt::AlignCenter);
    labelFC->setText(QString("Fill"));
    layoutColor->addWidget(labelFC);

    VColorPicker* colorPickerFill = new VColorPicker();
    colorPickerFill->setColor(ell->getFillColor());
    connect(  colorPickerFill, &VColorPicker::sigColorChanged,  ell, &ellipse::updateFillColor );
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
    spinBoxZvalue->setValue(ell->zValue());
    spinBoxZvalue->setAlignment(Qt::AlignCenter);
    connect(  spinBoxZvalue, &QSpinBox::valueChanged,  ell, &ellipse::updateZvalue );
    layoutZvalue->addWidget(spinBoxZvalue);

    _panel = panel;
}



QLayout *VPanelVisitor::getResult()
{
    return _panel;
}


