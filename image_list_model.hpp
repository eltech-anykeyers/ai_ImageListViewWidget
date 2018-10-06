#ifndef IMAGE_LIST_MODEL_HPP
#define IMAGE_LIST_MODEL_HPP

#include <QAbstractListModel>
#include <QVector>

#include <memory>

class ImageListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ImageListModel( QObject* parent = Q_NULLPTR );
    virtual ~ImageListModel() override = default;

    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;

signals:
    void rowUpdated( int rowIndex );

public slots:
    void updateRow( int rowIndex );
    void addImage( std::shared_ptr<QImage> image );

private:
    QVector< std::shared_ptr< QImage > >  images;

};

#endif /// IMAGE_LIST_MODEL_HPP
