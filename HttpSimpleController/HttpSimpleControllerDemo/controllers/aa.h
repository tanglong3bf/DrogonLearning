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
    // 当控制器绑定的路径和静态文件路径冲突时，控制器会优先生效
    // 解开注释的话会覆盖掉静态文件
    // PATH_ADD("/", Get);
    PATH_ADD("/test", Get);
    PATH_LIST_END
};
