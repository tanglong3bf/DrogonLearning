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
    ADD_METHOD_VIA_REGEX(blog::remove,
                         "/api/blog/remove/([1-9]\\d*)",
                         Get);  // path is /api/blog/remove/{blog_id}
    // 可以使用 postman/apipost/apifox 发送请求
    ADD_METHOD_TO(blog::add, "/api/blog/add",
                  Post);  // path is /api/blog/add
    METHOD_LIST_END

    void list(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              int category_id) const;
    void remove(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                int blog_id);
    // 如果参数类型是 std::shared_ptr<Json::Value>
    // 框架有一个默认的实现，就在 HttpRequest.h 的末尾
    void add(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback,
             Json::Value &&blog);

  private:
    Json::Value data;
};
}  // namespace api

namespace drogon
{
template <>
inline Json::Value fromRequest(const HttpRequest &req)
{
    // 如果请求体为空，或者请求体有内容但不是 json 格式
    // 这里获得的指针是一个空指针
    auto jsonPtr = req.getJsonObject();
    if (jsonPtr)
    {
        return *jsonPtr;
    }
    LOG_ERROR << "请求体格式错误，请使用 json";
    return {};
}
}  // namespace drogon
