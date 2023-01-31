#ifndef VGRABBER_H
#define VGRABBER_H
#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QColor>


class VGrabber : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public :
    explicit VGrabber(qreal x, qreal y, QObject *parent = nullptr, QGraphicsItem *parentGraphic = nullptr);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void updatePosition(qreal x, qreal y);
    static qreal width();
    static qreal height();


signals:
    void sigMouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void sigMousePressEvent(QGraphicsSceneMouseEvent *event);
    void sigMouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
    QPen _pen;
    QBrush _brush;
    static qreal* _width;
    static qreal* _height;
};



#endif // VGRABBER_H
