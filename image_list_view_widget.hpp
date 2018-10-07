#ifndef IMAGE_LIST_VIEW_WIDGET_HPP
#define IMAGE_LIST_VIEW_WIDGET_HPP

#include <QListView>

#include <memory>

#include "image_list_item_delegate.hpp"
#include "image_list_model.hpp"

class ImageListViewWidget : public QListView
{
    Q_OBJECT

public:
    explicit ImageListViewWidget( QWidget* parent = Q_NULLPTR );
    virtual ~ImageListViewWidget() override = default;

signals:

public slots:
    ImageListModel* model() const;
    ImageListItemDelegate* delegate() const;

private:
    ImageListModel* imageListModel;
    ImageListItemDelegate* imageListItemDelegate;
};

#endif /// IMAGE_LIST_VIEW_WIDGET_HPP
