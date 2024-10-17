#include "aa.h"

void aa::asyncHandleHttpRequest(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    auto resp = HttpResponse::
        newHttpResponse();  // 请永远使用框架提供的函数来创建响应体
    resp->setStatusCode(k200OK);                     // 默认值
    resp->setContentTypeCode(drogon::CT_TEXT_HTML);  // 默认值
    resp->setBody("Hello Simple Controller!");
    callback(resp);
}
