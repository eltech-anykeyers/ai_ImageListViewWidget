#include "image_list_view_widget.hpp"

ImageListViewWidget::ImageListViewWidget( QWidget* parent )
    : QListView( parent )
{
    imageListModel = new ImageListModel();

    imageListItemDelegate = new ImageListItemDelegate();
    imageListItemDelegate->setAlignment( Qt::AlignCenter );
    imageListItemDelegate->setAspectRatioMode( Qt::KeepAspectRatio );
    imageListItemDelegate->setImagePreferredHeight( 200 );

    this->setModel( imageListModel );
    this->setItemDelegate( imageListItemDelegate );
    this->setHorizontalScrollMode( QAbstractItemView::ScrollPerPixel );
    this->setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );
    this->setSpacing( 5 );
}

ImageListModel* ImageListViewWidget::model() const
{
    return imageListModel;
}

ImageListItemDelegate* ImageListViewWidget::delegate() const
{
    return imageListItemDelegate;
}
