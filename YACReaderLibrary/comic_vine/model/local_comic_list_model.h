#ifndef LOCAL_COMIC_LIST_MODEL_H
#define LOCAL_COMIC_LIST_MODEL_H

#include <QAbstractItemModel>

#include "comic_db.h"

class LocalComicListModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit LocalComicListModel(QObject *parent = 0);

	void load(QList<ComicDB> & comics);

	//QAbstractItemModel methods
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
						int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QList<ComicDB> getData();

    void removeComics(const QList<QModelIndex> & selectedIndexes);
    void restoreAll();
signals:

public slots:
	void moveSelectionUp(const QList<QModelIndex> & selectedIndexes);
	void moveSelectionDown(const QList<QModelIndex> & selectedIndexes);
	void addExtraRows(int numRows);

private:
	int numExtraRows;
	QList<ComicDB> _data;
    QList<ComicDB> _removed;
};

#endif // LOCAL_COMIC_LIST_MODEL_H
