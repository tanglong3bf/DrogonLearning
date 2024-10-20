#include "api_blog.h"

using namespace api;

// Add definition of your processing function here

void blog::list(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                int category_id) const
{
    Json::Value json;
    json["code"] = 0;
    json["message"] = "get blog list success";

    json["data"] = data;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void blog::remove(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  int blog_id)
{
    Json::Value json;

    int i = 0;
    for (; i < data.size(); ++i)
    {
        if (data[i]["blog_id"].asInt() == blog_id)
        {
            data.removeIndex(i, nullptr);
            break;
        }
    }

    if (i != data.size())
    {
        json["code"] = 0;
        json["message"] = "remove blog success";
    }
    else
    {
        json["code"] = -1;
        json["message"] = "remove blog failed";
    }
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
