#ifndef VVERTICALLAYOUT_H
#define VVERTICALLAYOUT_H

#include "vpanelvisitor.h"
#include "vshape.h"
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

class VVerticalLayout : public QVBoxLayout
{
    Q_OBJECT

public:
    VVerticalLayout();
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void refresh(VShape* selectedShape, QWidget* panel);

private:
    VPanelVisitor panelVisitor;



};

#endif // VVERTICALLAYOUT_H
