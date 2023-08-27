#ifndef DSTANDARTITEMMODEL_H
#define DSTANDARTITEMMODEL_H

#include <QObject>
#include <QStandardItemModel>

class DStandartItemModel: public QStandardItemModel
{
    Q_OBJECT
public:
    explicit DStandartItemModel(QObject *parent = Q_NULLPTR);
    virtual ~DStandartItemModel();

    void setHorizontalHeaderItem(int column, const QString &text);
};

#endif // DSTANDARTITEMMODEL_H
