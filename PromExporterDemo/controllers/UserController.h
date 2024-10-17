#pragma once

#include <drogon/HttpController.h>
// #include <drogon/plugins/PromExporter.h>
// #include <drogon/utils/monitoring/Counter.h>

using namespace drogon;

class UserController : public drogon::HttpController<UserController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::login,
                  "/user/login?username={1}&password={2}",
                  Get);
    ADD_METHOD_TO(UserController::info, "/user/info", Get, "LoginCheckFilter");
    ADD_METHOD_TO(UserController::logout,
                  "/user/logout",
                  Get,
                  "LoginCheckFilter");
    METHOD_LIST_END
    Task<HttpResponsePtr> login(const HttpRequestPtr req,
                                const std::string &username,
                                const std::string &password) const;
    Task<HttpResponsePtr> info(const HttpRequestPtr req) const;
    Task<HttpResponsePtr> logout(const HttpRequestPtr req) const;

    //   UserController()
    //   {
    //       // 获取插件
    //       auto *promExporter =
    //       app().getPlugin<drogon::plugin::PromExporter>();
    //       //
    //       指定收集器（collector）的名称、并指定收集器下指标（metric）的属性值
    //       counter_ =
    //           promExporter
    //               ->getCollector<monitoring::Counter>("http_requests_total")
    //               ->metric({"GET", "200"});
    //   }
    //
    // private:
    //   std::shared_ptr<drogon::monitoring::Counter> counter_;
};
