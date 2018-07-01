#ifndef SYNCCONTROLLER_V2_H
#define SYNCCONTROLLER_V2_H

#include <QObject>

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class SyncControllerV2 : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(SyncControllerV2)
public:
    /** Constructor */
    SyncControllerV2();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SYNCCONTROLLER_H
