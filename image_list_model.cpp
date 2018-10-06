#include "image_list_model.hpp"

#include <QPixmap>

ImageListModel::ImageListModel( QObject* parent )
    : QAbstractListModel( parent )
{
    connect( this, &ImageListModel::dataChanged,
             [ this ]( const QModelIndex& topLeft,
                 const QModelIndex& bottomRight,
                 const QVector<int> )
             {
                 if( topLeft.column() != bottomRight.column() )
                 {
                     return;
                 }
                 for( int i = topLeft.row(); i <= bottomRight.row(); i++ )
                 {
                     emit rowUpdated( i );
                 }
             } );
}

int ImageListModel::rowCount( const QModelIndex& parent ) const
{
    if (parent.isValid()) return 0;

    return images.size();
}

QVariant ImageListModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() ) return QVariant();

    if( role == Qt::DisplayRole )
    {
        return *images.at( index.row() );
    }

    return QVariant();
}

void ImageListModel::updateRow( int rowIndex )
{
    emit dataChanged( this->index( rowIndex ), this->index( rowIndex),
                      QVector< int >{ Qt::DisplayRole } );
}

void ImageListModel::addImage( std::shared_ptr< QImage > image )
{
    beginInsertRows( QModelIndex(),
                     images.size(), images.size() );
    images.push_back( image );
    endInsertRows();
}