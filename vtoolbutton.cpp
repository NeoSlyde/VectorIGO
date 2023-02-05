#include "vtoolbutton.h"
#include <iostream>
#include <QString>
#include <string.h>

VToolButton::VToolButton(QString toolId) : QPushButton()
{
    setCheckable(true);
    buttonToolId = toolId;
    setFixedHeight(33);
    setFixedWidth(53);
    setContentsMargins(0,0,0,0);
}

void VToolButton::notifyButton(QString toolId)
{
    if(buttonToolId == toolId)
        setChecked(true);
    else
        setChecked(false);
}

void VToolButton::enterEvent(QEnterEvent *event)
{
    setFixedHeight(35);
    setFixedWidth(53);
}

void VToolButton::leaveEvent(QEvent *eventt)
{
    setFixedHeight(33);
    setFixedWidth(53);
}
