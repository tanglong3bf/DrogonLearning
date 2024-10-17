#include "bb.h"

void bb::asyncHandleHttpRequest(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(drogon::CT_TEXT_HTML);
    resp->setBody("Hello bb!");
    callback(resp);
}
