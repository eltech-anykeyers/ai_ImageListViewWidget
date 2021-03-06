#ifndef IMAGE_LIST_MODEL_HPP
#define IMAGE_LIST_MODEL_HPP

#include <QAbstractListModel>
#include <QVector>

#include <memory>
#include <optional>

class ImageListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    using ImagePtr = std::shared_ptr< QImage >;
    using OptMark = std::optional< QString >;
    using MarkedImage = QPair< ImagePtr, OptMark >;

    explicit ImageListModel( QObject* parent = Q_NULLPTR );
    virtual ~ImageListModel() override = default;

    virtual int rowCount(
        const QModelIndex& parent = QModelIndex() ) const override;
    virtual QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole ) const override;

    QPair< QImage, QString > getImage( int rowIndex ) const;
    QVector< QPair< QImage, QString > > getImages() const;
    int size() const;

signals:
    void rowUpdated( int rowIndex );

public slots:
    void clear();
    void removeRow( int rowIndex );
    void updateRow( int rowIndex );
    void addImage( std::shared_ptr< QImage > image );
    void addImage( std::shared_ptr< QImage > image, const QString& mark );
    void setMark( int rowIndex, const QString& mark );

private:
    QVector< MarkedImage > images;

};

#endif /// IMAGE_LIST_MODEL_HPP
