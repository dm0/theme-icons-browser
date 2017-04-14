#include <QDebug>

#include "icondelegate.h"

IconDelegate::IconDelegate(QObject *parent, QSize size_hint):
    QStyledItemDelegate(parent),
    item_size_hint(std::move(size_hint))
{
}

QSize IconDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
    return item_size_hint;
}
