#include "image_list_item_delegate.hpp"

#include <QPainter>

ImageListItemDelegate::ImageListItemDelegate( QWidget* parent )
    : QStyledItemDelegate( parent )
{}

void ImageListItemDelegate::paint(
    QPainter* painter, const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if( !index.data().canConvert< QImage >() )
    {
        QStyledItemDelegate::paint( painter, option, index );
        return;
    }

    QImage image = qvariant_cast< QImage >( index.data() );
    painter->drawImage( QPoint( option.rect.left(), option.rect.top() ),
                        image.scaled( 100, 100 ) );

    /// Draw border.
    painter->setPen( Qt::GlobalColor::black );
    painter->setBrush( Qt::GlobalColor::transparent );
    painter->drawRect( option.rect );
}

QSize ImageListItemDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if( !index.data().canConvert< QImage >() )
    {
        return QStyledItemDelegate::sizeHint( option, index );
    }

    /*
    QImage image = qvariant_cast< QImage >( index.data() );
    return image.size();
    */
    return QSize( 100, 100 );
}
