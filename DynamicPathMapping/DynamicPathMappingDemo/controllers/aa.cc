#include "aa.h"

void aa::asyncHandleHttpRequest(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("Hello, aa!");
    callback(resp);
}
