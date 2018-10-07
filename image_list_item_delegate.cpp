#include "image_list_item_delegate.hpp"

#include <QPainter>
#include <QtMath>

ImageListItemDelegate::ImageListItemDelegate( QWidget* parent )
    : QStyledItemDelegate( parent )
{
    alignment = Qt::AlignCenter;
    aspectRatioMode = Qt::KeepAspectRatio;
    roundingSize = QSize( 10, 10 );
    margins = QMargins( 0, 0, 0, 0 );
    font = QFont( "Times", 12 );
    imageHeight = 100;
    borderWidth = 1;

    backgroundColor = QPalette().color( QPalette::Window );
    fontColor = Qt::GlobalColor::black;
    borderColor = QPalette().dark().color();
    markBackgroundColor = Qt::GlobalColor::white;
}

Qt::Alignment ImageListItemDelegate::getAlignment() const
{
    return alignment;
}

Qt::AspectRatioMode ImageListItemDelegate::getAspectRatioMode() const
{
    return aspectRatioMode;
}

QPair< int, int > ImageListItemDelegate::getRounding() const
{
    return qMakePair( roundingSize.width(), roundingSize.height() );
}

QMargins ImageListItemDelegate::getMargins() const
{
    return margins;
}

QFont ImageListItemDelegate::getFont() const
{
    return font;
}

int ImageListItemDelegate::getImagePreferredHeight() const
{
    return imageHeight;
}

QColor ImageListItemDelegate::getBackgroundColor() const
{
    return backgroundColor;
}

QColor ImageListItemDelegate::getFontColor() const
{
    return fontColor;
}

QColor ImageListItemDelegate::getBorderColor() const
{
    return borderColor;
}

QColor ImageListItemDelegate::getMarkBackgroundColor() const
{
    return markBackgroundColor;
}

void ImageListItemDelegate::setAlignment( Qt::Alignment alignment )
{
    this->alignment = alignment;
}

void ImageListItemDelegate::setAspectRatioMode(
    Qt::AspectRatioMode aspectRatioMode )
{
    this->aspectRatioMode = aspectRatioMode;
}

void ImageListItemDelegate::setRounding( int x, int y )
{
    roundingSize = QSize( x, y );
}

void ImageListItemDelegate::setMargins( int left, int top, int right, int bottom )
{
    margins = QMargins( left, top, right, bottom );
}

void ImageListItemDelegate::setFont( QFont font )
{
    this->font = font;
}

void ImageListItemDelegate::setImagePreferredHeight( int imageHeight )
{
    this->imageHeight = imageHeight;
}

void ImageListItemDelegate::paint(
    QPainter* painter, const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if( !index.data().canConvert< QImage >() )
    {
        QStyledItemDelegate::paint( painter, option, index );
        return;
    }

    /// Draw canvas.
    painter->setPen( Qt::GlobalColor::transparent );
    painter->setBrush( markBackgroundColor );
    painter->drawRoundedRect(
        option.rect, roundingSize.width(), roundingSize.height() );

    /// Draw mark.
    int markOffset = 0;
    if( index.data( Qt::DecorationRole ).canConvert< QString >() )
    {
        QString mark =
            qvariant_cast< QString >( index.data( Qt::DecorationRole ) );
        QFontMetrics fontMetrics = QFontMetrics( font );
        painter->setPen( fontColor );
        painter->setFont( font );
        painter->drawText(
            QPoint( option.rect.left() +
                    ( option.rect.width() - fontMetrics.width( mark ) ) / 2,
                    option.rect.bottom() ),
            mark );
        markOffset = fontMetrics.height() + 1;
    }

    QImage image = qvariant_cast< QImage >( index.data() );
    if( !image.isNull() )
    {
        QRect drawingRect = option.rect;
        drawingRect.setBottom( drawingRect.bottom() - markOffset );

        /// Scale image to proper size.
        QImage scaledImage =
            image.scaled( drawingRect.size(), aspectRatioMode )
                 .convertToFormat( QImage::Format_ARGB32 );

        /// Compute offsets.
        int x = drawingRect.left(), y = drawingRect.top();
        if( alignment & Qt::AlignLeft )
            x += 0;
        else if( alignment & Qt::AlignRight )
            x += drawingRect.width() - scaledImage.width();
        else if( alignment & Qt::AlignHCenter )
            x += ( drawingRect.width() - scaledImage.width() ) / 2;
        if( alignment & Qt::AlignTop )
            y += 0;
        else if( alignment & Qt::AlignBottom )
            y += drawingRect.height() - scaledImage.height();
        else if( alignment & Qt::AlignVCenter )
            y += ( drawingRect.height() - scaledImage.height() ) / 2;
        QPoint startPoint = QPoint( x, y );

        /// Draw image background.
        if( scaledImage.width() < drawingRect.width() ||
            scaledImage.height() < drawingRect.height() )
        {
            painter->setPen( Qt::transparent );
            painter->setBrush( backgroundColor );
            painter->drawRoundedRect(
                drawingRect, roundingSize.width(), roundingSize.height() );
        }

        /// Draw image.
        painter->setPen( QPen( borderColor, borderWidth ) );
        painter->setBrush( scaledImage.copy(
                               QRect( drawingRect.topLeft() - startPoint,
                                      drawingRect.size() ) ) );
        painter->setBrushOrigin( drawingRect.topLeft() );
        painter->drawRoundedRect(
            drawingRect, roundingSize.width(), roundingSize.height() );
    }

    /// Draw border.
    painter->setPen( QPen( borderColor, borderWidth ) );
    painter->setBrush( Qt::GlobalColor::transparent );
    painter->drawRoundedRect(
        option.rect, roundingSize.width(), roundingSize.height() );
}

QSize ImageListItemDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if( !index.data().canConvert< QImage >() )
    {
        return QStyledItemDelegate::sizeHint( option, index );
    }

    /// Compute width.
    QImage image = qvariant_cast< QImage >( index.data() );
    int width = qCeil( static_cast< qreal >( imageHeight ) /
                       image.height() * image.width() );
    /// Adjust height.
    int height = imageHeight;
    if( index.data( Qt::DecorationRole ).canConvert< QString >() )
    {
        height += QFontMetrics( font ).height() + 1;
    }

    return QSize( width, height );
}
