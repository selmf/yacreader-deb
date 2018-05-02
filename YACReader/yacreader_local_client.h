#ifndef YACREADER_LOCAL_CLIENT_H
#define YACREADER_LOCAL_CLIENT_H

#include <QObject>

class QLocalSocket;
class ComicDB;

class YACReaderLocalClient : public QObject
{
    Q_OBJECT
public:
    explicit YACReaderLocalClient(QObject *parent = 0);
    ~YACReaderLocalClient();
signals:
    void finished();
public slots:
    void readMessage();
    bool requestComicInfo(quint64 libraryId, ComicDB & comic,QList<ComicDB> & siblings);
    bool sendComicInfo(quint64 libraryId, ComicDB & comic);

private:
    QLocalSocket * localSocket;
    
};

#endif // YACREADER_LOCAL_CLIENT_H
