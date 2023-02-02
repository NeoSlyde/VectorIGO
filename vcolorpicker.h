#ifndef VCOLORPICKER_H
#define VCOLORPICKER_H
#include <QPushButton>

#include <QColorDialog>
#include <QObject>
#include <QWidget>

class VColorPicker : public QPushButton
{
    Q_OBJECT

public:
    VColorPicker();
    void mouseReleaseEvent(QMouseEvent *event) override;
    void setColor(QColor col);


private:
    QColorDialog* colorDialog = nullptr;
    QColor currentColor;


signals:
    void sigColorChanged(QColor col);

};

#endif // VCOLORPICKER_H
