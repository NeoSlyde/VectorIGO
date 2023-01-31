#ifndef VVIEW_H
#define VVIEW_H
#include <QGraphicsView>



class VView : public QGraphicsView
{

public:
    VView(QWidget *parent = nullptr);
    void drawBackground(QPainter *painter, const QRectF &rect) override;









};

#endif // VVIEW_H
