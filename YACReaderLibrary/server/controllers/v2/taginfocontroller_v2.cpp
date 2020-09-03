#include "taginfocontroller_v2.h"

#include "db_helper.h"

#include "folder.h"
#include "comic_db.h"

#include "template.h"
#include "../static.h"

using stefanfrings::HttpRequest;
using stefanfrings::HttpResponse;

TagInfoControllerV2::TagInfoControllerV2() { }

void TagInfoControllerV2::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "text/plain; charset=utf-8");

    QString path = QUrl::fromPercentEncoding(request.getPath()).toUtf8();
    QStringList pathElements = path.split('/');
    int libraryId = pathElements.at(3).toInt();
    QString libraryName = DBHelper::getLibraryName(libraryId);
    qulonglong listId = pathElements.at(5).toULongLong();

    serviceComics(libraryId, listId, response);

    response.write("", true);
}

void TagInfoControllerV2::serviceComics(const int &library, const qulonglong &tagId, HttpResponse &response)
{
    QList<ComicDB> comics = DBHelper::getLabelComics(library, tagId);

    for (const ComicDB &comic : comics) {
        response.write(QString("/v2/library/%1/comic/%2:%3:%4:%5:%6\r\n")
                               .arg(library)
                               .arg(comic.id)
                               .arg(comic.getFileName())
                               .arg(comic.getFileSize())
                               .arg(comic.info.read ? 1 : 0)
                               .arg(comic.info.hash)
                               .toUtf8());
    }
}
