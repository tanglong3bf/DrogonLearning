#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class cc : public drogon::HttpSimpleController<cc>
{
  public:
    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    // list path definitions here;
    // PATH_ADD("/path", "filter1", "filter2", HttpMethod1, HttpMethod2...);
    PATH_ADD("/api", Get);
    PATH_LIST_END
};
