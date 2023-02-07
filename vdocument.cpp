#include "vdocument.h"
#include "vscene.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QLabel>
#include <iostream>
#include <QStandardPaths>

VDocument::VDocument(QObject *parent) : QObject{parent}
{
}


void VDocument::loadDoc(QWidget* parent, VScene *scene, QLabel* titre)
{
    QString fileName = QFileDialog::getOpenFileName(parent, "Open VectorIGO project", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), "IGO PROJECTS (*.igo)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(parent, tr("File error"),tr("Failed to open\n%1").arg(fileName));
        return;
    }

    QMessageBox::StandardButton userChoice = QMessageBox::warning(parent,"Warning", "Change current project ?", QMessageBox::Yes | QMessageBox::No );
    if(userChoice!=QMessageBox::Yes){
        return;
    }

    QMessageBox msgBoxSave;
    msgBoxSave.setText("Save previous project ?");
    msgBoxSave.setInformativeText("Save the modifications of your previous project?");
    msgBoxSave.setStandardButtons(QMessageBox::Save | QMessageBox::No);
    msgBoxSave.setDefaultButton(QMessageBox::Save);
    int ret = msgBoxSave.exec();
    if(ret!=QMessageBox::No){
        saveDoc(parent, scene, titre);
    }

    scene->removeAllShapes();
    QTextStream stream(&file);
    scene->load(stream);
    filePath = fileName;
    titre->setText(filePath.split(QDir::separator()).last());
}


void VDocument::saveDoc(QWidget *parent, VScene *scene, QLabel* titre)
{
    for (;;) {
        QString fileName = filePath;

        if (fileName.isEmpty())
            fileName = QFileDialog::getSaveFileName(parent, "Save File As", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) +QDir::separator()+"file.igo") ;
        if (fileName.isEmpty())
            break;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(parent, tr("File error"),tr("Failed to open\n%1").arg(fileName));
        } else {
            QTextStream stream(&file);
            scene->save(stream);
            filePath = fileName;
            titre->setText(filePath.split(QDir::separator()).last());
            break;
        }
    }
}


void VDocument::saveDocAs(QWidget *parent, VScene *scene)
{
    for (;;) {
        QString fileName = QFileDialog::getSaveFileName(parent, "Save File As", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) +QDir::separator()+"copy.igo") ;
        if (fileName.isEmpty())
            break;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning( parent,  tr("File error"),  tr("Failed to open\n%1").arg(fileName) );
        } else {
            QTextStream stream(&file);
            scene->save(stream);
            break;
        }
    }
}


void VDocument::newProject(QWidget *parent, VScene *scene, QLabel* titre)
{
    QMessageBox::StandardButton userChoice = QMessageBox::warning(parent,"Warning", "Change current project ?", QMessageBox::Yes | QMessageBox::No );
    if(userChoice!=QMessageBox::Yes){
        return;
    }

    QMessageBox msgBoxSave;
    msgBoxSave.setText("Save previous project ?");
    msgBoxSave.setInformativeText("Save the modifications of your previous project?");
    msgBoxSave.setStandardButtons(QMessageBox::Save | QMessageBox::No);
    msgBoxSave.setDefaultButton(QMessageBox::Save);
    int ret = msgBoxSave.exec();
    if(ret!=QMessageBox::No){
        saveDoc(parent, scene, titre);
    }

    filePath = QString();
    titre->setText("sans_titre.igo");
    scene->removeAllShapes();
}


