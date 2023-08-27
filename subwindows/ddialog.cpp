#include "ddialog.h"

#include <QCloseEvent>

DDialog::DDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent,f)
{}

void DDialog::closeEvent(QCloseEvent *e)
{
    e->ignore();
}
