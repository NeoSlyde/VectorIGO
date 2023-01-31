#ifndef QDIALOG_H
#define QDIALOG_H

#include "ui_qdialog.h"

#include <QMainWindow>

using OnValidateFn = std::function<void(int, int, int)>;

class QDialog : public QMainWindow, private Ui::QDialog
{
    Q_OBJECT

public:
    QDialog(OnValidateFn onValidate, QWidget *parent = nullptr);
    ~QDialog();
protected slots:
    void colorChanged();
private:
    OnValidateFn onValidate;
};
#endif // QDIALOG_H
