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
    if( parent.isValid() ) return 0;

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

QPair< QImage, QString > ImageListModel::getImage( int rowIndex ) const
{
    auto item = images[ rowIndex ];
    return qMakePair( item.first  ? *item.first  : QImage(),
                      item.second ? *item.second : QString() );
}

QVector< QPair< QImage, QString > > ImageListModel::getImages() const
{
    QVector< QPair< QImage, QString > > result;
    std::transform( images.begin(), images.end(), std::back_inserter( result ),
                    []( const MarkedImage& img ) -> QPair< QImage, QString >
                    {
                        return qMakePair( img.first  ? *img.first  : QImage(),
                                          img.second ? *img.second : QString() );
                    } );
    return result;
}

int ImageListModel::size() const
{
    return images.size();
}

void ImageListModel::clear()
{
    if( images.empty() ) return;
    beginRemoveRows( QModelIndex(),
                     0, images.size() - 1 );
    images.clear();
    endRemoveRows();
}

void ImageListModel::removeRow( int rowIndex )
{
    if( rowIndex >= images.size() ) return;
    beginRemoveRows( QModelIndex(),
                     rowIndex, rowIndex );
    images.remove( rowIndex );
    endRemoveRows();
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
    images.push_back( qMakePair( image, std::nullopt ) );
    endInsertRows();
}

void ImageListModel::addImage( std::shared_ptr< QImage > image, const QString& mark )
{
    beginInsertRows( QModelIndex(),
                     images.size(), images.size() );
    images.push_back( qMakePair( image, mark ) );
    endInsertRows();
}

void ImageListModel::setMark( int rowIndex, const QString& mark )
{
    images[ rowIndex ].second = mark;
    updateRow( rowIndex );
}
