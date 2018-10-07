#ifndef IMAGE_LIST_ITEM_DELEGATE_HPP
#define IMAGE_LIST_ITEM_DELEGATE_HPP

#include <QStyledItemDelegate>
#include <QPair>

class ImageListItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ImageListItemDelegate( QWidget* parent = Q_NULLPTR );
    virtual ~ImageListItemDelegate() override = default;

    Qt::Alignment getAlignment() const;
    Qt::AspectRatioMode getAspectRatioMode() const;
    QPair< int, int > getRounding() const;
    QMargins getMargins() const;
    QFont getFont() const;
    int getImagePreferredHeight() const;
    QColor getBackgroundColor() const;
    QColor getFontColor() const;
    QColor getBorderColor() const;
    QColor getMarkBackgroundColor() const;

public slots:
    void setAlignment( Qt::Alignment alignment );
    void setAspectRatioMode( Qt::AspectRatioMode aspectRatioMode );
    void setRounding( int x, int y );
    void setMargins( int left, int top, int right, int bottom );
    void setFont( QFont font );
    void setImagePreferredHeight( int imageHeight );

protected:
    virtual void paint(
        QPainter* painter, const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;
    virtual QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const override;

private:
    Qt::Alignment alignment;
    Qt::AspectRatioMode aspectRatioMode;
    QSizeF roundingSize;
    QMargins margins;
    QFont font;
    QColor backgroundColor;
    QColor fontColor;
    QColor borderColor;
    QColor markBackgroundColor;
    qreal borderWidth;
    int imageHeight;
};

#endif /// IMAGE_LIST_ITEM_DELEGATE_HPP
