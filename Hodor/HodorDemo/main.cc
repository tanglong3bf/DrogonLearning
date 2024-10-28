#include <drogon/drogon.h>

int main()
{
    drogon::app().registerBeginningAdvice([] {
        auto *hodor = drogon::app().getPlugin<drogon::plugin::Hodor>();
        if (hodor)
        {
            // 需要搭配 `user_capacity` 配置项才有意义
            hodor->setUserIdGetter([](const drogon::HttpRequestPtr &req)
                                       -> std::optional<std::string> {
                auto userId = req->session()->get<std::string>("userId");
                if (userId != "")
                {
                    return userId;
                }
                return std::nullopt;
            });
            // 如果调用了此接口设置了回调函数，则 `rejection_message`
            // 配置项将被忽略
            hodor->setRejectResponseFactory(
                [](const drogon::HttpRequestPtr &req)
                    -> drogon::HttpResponsePtr {
                    Json::Value json;
                    json["error"] = "系统繁忙，请稍后重试";

                    auto resp = drogon::HttpResponse::newHttpJsonResponse(json);
                    resp->setStatusCode(drogon::k429TooManyRequests);
                    return resp;
                });
        }
        else
        {
            LOG_ERROR << "获取插件失败，请检查配置文件";
        }
    });

    // Load config file
    drogon::app().loadConfigFile("../config.json");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
