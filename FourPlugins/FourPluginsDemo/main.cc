#include <drogon/drogon.h>
#include <drogon/plugins/Redirector.h>

int main()
{
    drogon::app().registerBeginningAdvice([] {
        auto *hodor = drogon::app().getPlugin<drogon::plugin::Hodor>();
        if (hodor)
        {
            hodor->setUserIdGetter([](const drogon::HttpRequestPtr &req)
                                       -> std::optional<std::string> {
                auto userId = req->session()->get<std::string>("userId");
                if (userId != "")
                {
                    return userId;
                }
                return std::nullopt;
            });
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

    drogon::app().registerBeginningAdvice([] {
        auto *redirector =
            drogon::app().getPlugin<drogon::plugin::Redirector>();

        redirector->registerRedirectHandler(
            [](const drogon::HttpRequestPtr &req,
               std::string &protocol,        // "http://" or "https://"
               std::string &host,            // 域名
               bool &pathChanged) -> bool {  // 请求路径是否被修改
                if (req->path() == "/")
                {
                    protocol = "https://";
                    host = "www.bilibili.com";
                    req->setPath("/video/BV1NZ4y1y7Qz");
                    pathChanged = true;
                }
                return true;
            });

        redirector->registerPathRewriteHandler(
            [](const drogon::HttpRequestPtr &req) -> bool {
                if (!req->path().starts_with("/user") && req->path() != "/")
                {
                    req->setPath("/");
                    return true;
                }
                return false;
            });

        redirector->registerForwardHandler(
            [](const drogon::HttpRequestPtr &req) {
                if (req->path() == "/user")
                {
                    req->setPath("/user/info");
                }
            });
    });

    // Load config file
    drogon::app().loadConfigFile("../config.json");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
