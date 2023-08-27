#include "dstandartitemmodel.h"
#include <QDebug>

DStandartItemModel::DStandartItemModel(QObject *parent) : QStandardItemModel(parent)
{

}

DStandartItemModel::~DStandartItemModel()
{

}

void DStandartItemModel::setHorizontalHeaderItem(int column, const QString &text)
{
    QStandardItemModel::setHorizontalHeaderItem(column, new QStandardItem(text));
}
