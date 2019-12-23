#ifndef LOCAL_COMIC_LIST_MODEL_H
#define LOCAL_COMIC_LIST_MODEL_H

#include <QAbstractItemModel>

#include "comic_db.h"

class LocalComicListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit LocalComicListModel(QObject *parent = nullptr);

    void load(QList<ComicDB> &comics);

    //QAbstractItemModel methods
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QList<ComicDB> getData();

    void removeComics(const QList<QModelIndex> &selectedIndexes);
    void restoreAll();
signals:

public slots:
    void moveSelectionUp(const QList<QModelIndex> &selectedIndexes);
    void moveSelectionDown(const QList<QModelIndex> &selectedIndexes);
    void addExtraRows(int numRows);

private:
    int numExtraRows;
    QList<ComicDB> _data;
    QList<ComicDB> _removed;
};

#endif // LOCAL_COMIC_LIST_MODEL_H
