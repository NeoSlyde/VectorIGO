#ifndef VDOCUMENT_H
#define VDOCUMENT_H
#include "vscene.h"


#include <QLabel>
#include <QObject>

class VDocument : public QObject
{
    Q_OBJECT

public:
    explicit VDocument(QObject *parent = nullptr);
    void loadDoc(QWidget *parent, VScene* scene, QLabel* titre);
    void saveDoc(QWidget *parent, VScene* scene, QLabel* titre);
    void saveDocAs(QWidget *parent, VScene* scene);
    void newProject(QWidget *parent, VScene* scene, QLabel* titre);


private:
    QString filePath;

signals:






};

#endif // VDOCUMENT_H
