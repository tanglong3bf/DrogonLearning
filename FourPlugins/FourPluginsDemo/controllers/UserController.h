#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UserController : public drogon::HttpController<UserController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::login,
                  "/user/login?username={1}&password={2}",
                  Get,
                  "TimerMiddleware",
                  "CounterMiddleware");
    ADD_METHOD_TO(UserController::info,
                  "/user/info",
                  Get,
                  "TimerMiddleware",
                  "CounterMiddleware");
    ADD_METHOD_TO(UserController::logout,
                  "/user/logout",
                  Get,
                  "TimerMiddleware",
                  "CounterMiddleware");
    METHOD_LIST_END
    Task<HttpResponsePtr> login(const HttpRequestPtr req,
                                const std::string &username,
                                const std::string &password) const;
    Task<HttpResponsePtr> info(const HttpRequestPtr req) const;
    Task<HttpResponsePtr> logout(const HttpRequestPtr req) const;
};
