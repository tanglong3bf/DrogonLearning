#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api
{
class blog : public drogon::HttpController<blog>
{
  public:
    blog()
    {
        Json::Value temp;

        temp["blog_id"] = 1;
        temp["category_id"] = 1;
        temp["title"] = "C++是世界上最好的语言";
        temp["content"] = "<p>不接受任何反驳</p>";

        data[0] = temp;

        temp["blog_id"] = 2;
        temp["category_id"] = 1;
        temp["title"] = "Drogon是世界上最好的框架";
        temp["content"] = "<p>不接受任何反驳</p>";

        data[1] = temp;
    }

  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(blog::list,
               "/list/{category_id}",
               Get);  // path is /api/blog/list/{category_id}
    // 更合适的请求方式为 DELETE，但为了演示方便，使用 GET
    ADD_METHOD_TO(blog::remove,
                  "/api/blog/remove/{blog_id}",
                  Get);  // path is /api/blog/remove/{blog_id}
    METHOD_LIST_END

    void list(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              int category_id) const;
    void remove(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                int blog_id);

  private:
    Json::Value data;
};
}  // namespace api
