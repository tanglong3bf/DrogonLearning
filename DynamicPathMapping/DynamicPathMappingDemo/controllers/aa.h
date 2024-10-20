#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class aa : public drogon::HttpSimpleController<aa>
{
  public:
    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/", Get);
    PATH_LIST_END
};
