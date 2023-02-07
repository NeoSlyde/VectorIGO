#ifndef VDESERIALIZER_H
#define VDESERIALIZER_H

#include <QGraphicsItem>
#include <QObject>

class VDeserializer : public QObject
{
    Q_OBJECT

public:
    explicit VDeserializer(QObject *parent = nullptr);
    static QGraphicsItem* deSerializeRectangle(QString input, QGraphicsScene* scene);
    static QGraphicsItem *deSerializeEllipse(QString input, QGraphicsScene* scene);




};

#endif // VDESERIALIZER_H
