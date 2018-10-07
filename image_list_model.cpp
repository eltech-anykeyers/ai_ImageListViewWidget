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

    auto image = images.at( index.row() );
    switch( role )
    {
        case Qt::DisplayRole :
        {
            return image.first ? *image.first : QImage();
        }
        case Qt::DecorationRole :
        {
            if( image.second ) return image.second.value();
            else [[ fallthrough ]];
        }
        default:
        {
            return QVariant();
        }
    }
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
    images.push_back( std::make_pair( image, std::nullopt ) );
    endInsertRows();
}

void ImageListModel::addImage( std::shared_ptr< QImage > image, const QString& mark )
{
    beginInsertRows( QModelIndex(),
                     images.size(), images.size() );
    images.push_back( std::make_pair( image, mark ) );
    endInsertRows();
}

void ImageListModel::setMark( int rowIndex, const QString& mark )
{
    images[ rowIndex ].second = mark;
    updateRow( rowIndex );
}
