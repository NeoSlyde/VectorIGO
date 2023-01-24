#include "qdialog.h"
#include <QDebug>
#include <QColor>
#include <QPalette>

QDialog::QDialog(OnValidateFn onValidate, QWidget *parent)
    : QMainWindow(parent), onValidate(onValidate)
{
    setupUi(this);

    colorChanged();

    connect(_sliderHue, &QSlider::valueChanged, this, &QDialog::colorChanged);
    connect(_sliderSaturation, &QSlider::valueChanged, this, &QDialog::colorChanged);
    connect(_sliderValue, &QSlider::valueChanged, this, &QDialog::colorChanged);
    connect(_buttonCancel, &QPushButton::clicked, this, &QDialog::close);
    connect(_buttonChoose, &QPushButton::clicked, this,
            [&](){this->onValidate(_sliderHue->value(), _sliderSaturation->value(), _sliderValue->value());});
}

void QDialog::colorChanged()
{
    qDebug() << __FUNCTION__ << "The event sender is" << sender();

    QColor color;
    color.setHsl(_sliderHue->value(), _sliderSaturation->value(), _sliderValue->value());
    qDebug() << "The color is" << color;
    QPalette pal;
    pal.setColor(QPalette::Window, color);
    _colorFrame->setPalette(pal);
}

QDialog::~QDialog()
{
}

