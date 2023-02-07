#ifndef VVIEW_H
#define VVIEW_H
#include <QGraphicsView>



class VView : public QGraphicsView
{

public:
    VView(QWidget *parent = nullptr);
    void drawBackground(QPainter *painter, const QRectF &rect) override;

public slots:
    void updateZoom(int inputZoom);
    void resetZoom();
    void zoomIn();
    void zoomOut();



};

#endif // VVIEW_H
