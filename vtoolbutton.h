#ifndef VTOOLBUTTON_H
#define VTOOLBUTTON_H

#include <QString>
#include <QObject>
#include <QPushButton>
#include <string>

class VToolButton;

class VToolButton : public QPushButton
{
    Q_OBJECT

public:

    VToolButton(QString toolId, QIcon iconIn);
    VToolButton(QWidget *parent = nullptr);
    void set(QString toolId, QIcon iconIn);
    void notifyButton(QString toolId);
    QString buttonToolId;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;


};

#endif //VTOOLBUTTON_H
