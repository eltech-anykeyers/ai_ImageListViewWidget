#ifndef IMAGE_LIST_ITEM_DELEGATE_HPP
#define IMAGE_LIST_ITEM_DELEGATE_HPP

#include <QStyledItemDelegate>

class ImageListItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ImageListItemDelegate( QWidget* parent = Q_NULLPTR );
    virtual ~ImageListItemDelegate() override = default;

protected:
    virtual void paint(
        QPainter* painter, const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;

    virtual QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;
};

#endif /// IMAGE_LIST_ITEM_DELEGATE_HPP
