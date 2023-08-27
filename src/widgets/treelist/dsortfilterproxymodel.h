#ifndef DSORTFILTERPROXYMODEL_H
#define DSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class DSortFilterProxyModel:public QSortFilterProxyModel
{
    Q_OBJECT

    enum searchFlags
    {
        case_sensitive,
        whole_word
    };

public:
    explicit DSortFilterProxyModel(QObject *parent = Q_NULLPTR);
    void setSearchString(QString &searchString) { m_searchString=searchString; }

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

private:
    QString m_searchString;
    int m_searchFlag;
};

#endif // DSORTFILTERPROXYMODEL_H
