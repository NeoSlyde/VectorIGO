#ifndef VSHAPE_H
#define VSHAPE_H
#include <QLayout>

#include <QObject>

class VShape : public QObject
{
    Q_OBJECT

public:
    explicit VShape(QObject *parent = nullptr);
    virtual QLayout* getPanel() =0;
    virtual QString toString() =0;
    virtual void updateZvalue(int z) =0;




};

#endif // VSHAPE_H
