#include "dverticalheaderitemdelegate.h"

#include <QPainter>

DVerticalHeaderItemDelegate::DVerticalHeaderItemDelegate( QObject *parent, QSize &iconSize ) : QItemDelegate(parent),
    m_iconSize(iconSize)
{ }

void DVerticalHeaderItemDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    if (!option.rect.isValid()) return;

    painter->save();
    QItemDelegate::paint( painter, option, index );
    painter->restore();

    QIcon icon = qvariant_cast<QIcon>(index.data(Qt::UserRole+1001));
    if (!icon.isNull())
    {
        QRect iconRect(
              2,
              option.rect.top()+0.5*(option.rect.height()-m_iconSize.height()),
              m_iconSize.width(),
              m_iconSize.height()
        );
        painter->drawPixmap(iconRect, icon.pixmap(m_iconSize));
    }
}

