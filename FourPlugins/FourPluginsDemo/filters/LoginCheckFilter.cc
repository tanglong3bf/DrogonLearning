/**
 *
 *  LoginCheckFilter.cc
 *
 */

#include "LoginCheckFilter.h"
#include <drogon/HttpTypes.h>

using namespace drogon;

void LoginCheckFilter::doFilter(const HttpRequestPtr &req,
                                FilterCallback &&fcb,
                                FilterChainCallback &&fccb)
{
    // Edit your logic here
    if (!req->session()->get<std::string>("userId").empty())
    {
        // Passed
        fccb();
        return;
    }
    Json::Value json;
    json["error"] = "当前用户未登录";
    auto res = drogon::HttpResponse::newHttpJsonResponse(json);
    res->setStatusCode(drogon::k401Unauthorized);
    fcb(res);
}
