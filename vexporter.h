#ifndef VEXPORTER_H
#define VEXPORTER_H
#include "vscene.h"
#include <QObject>

class VExporter : public QObject
{
    Q_OBJECT


public:
    explicit VExporter(QObject *parent = nullptr);
    void exportSVG(QWidget *parent, VScene* scene);
    void exportPNG(QWidget *parent, VScene* scene);
    void exportJPG(QWidget *parent, VScene* scene);
    void exportBMP(QWidget *parent, VScene* scene);


signals:











};

#endif // VEXPORTER_H
