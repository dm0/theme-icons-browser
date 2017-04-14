#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief Simple delegate that sets only aspect rate of items
 */
class IconDelegate: public QStyledItemDelegate {
public:
    IconDelegate(QObject *parent=nullptr, QSize size_hint=QSize(64, 64));
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    /**
     * @brief Set item size hint
     * @param hint New size hint
     */
    void set_size_hint(QSize hint) { item_size_hint = hint; }
protected:
    QSize item_size_hint; /**< current size hint */
};

#endif // ICONDELEGATE_H
