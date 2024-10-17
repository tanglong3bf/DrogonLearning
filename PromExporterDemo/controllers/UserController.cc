#include "UserController.h"
#include <drogon/HttpTypes.h>

// Add definition of your processing function here
Task<HttpResponsePtr> UserController::login(const HttpRequestPtr req,
                                            const std::string &username,
                                            const std::string &password) const
{
    auto session = req->session();
    session->erase("userId");

    Json::Value json;
    if (username == "admin123" && password == "123456")
    {
        session->insert("userId", std::string("1"));
        json["message"] = "登录成功！";
        co_return HttpResponse::newHttpJsonResponse(json);
    }
    else if (username == "tanglong3bf" && password == "111111")
    {
        session->insert("userId", std::string("2"));
        json["message"] = "登录成功！";
        co_return HttpResponse::newHttpJsonResponse(json);
    }
    else
    {
        json["error"] = "用户名或密码错误，登录失败！";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(drogon::k401Unauthorized);
        co_return resp;
    }
}

Task<HttpResponsePtr> UserController::info(const HttpRequestPtr req) const
{
    // counter_->increment();
    auto userId = req->session()->get<std::string>("userId");
    Json::Value json;
    {
        Json::Value data;

        if (userId == "1")
        {
            data["name"] = "张三";
            data["gender"] = "男";
            data["age"] = 23;
            data["email"] = "zhangsan@example.com";
            data["desp"] = "法外狂徒";
        }
        else if (userId == "2")
        {
            data["name"] = "唐龙";
            data["gender"] = "男";
            data["age"] = 18;
            data["email"] = "tanglong3bf@example.com";
            data["desp"] =
                "英俊潇洒、性格温和、风流倜傥、风度翩翩、玉树临风、气度不凡、温"
                "文尔雅、俊美无涛、面如冠玉、一表人才、鹤立鸡群、高大威猛";
        }

        json["data"] = data;
    }
    co_return HttpResponse::newHttpJsonResponse(json);
}

Task<HttpResponsePtr> UserController::logout(const HttpRequestPtr req) const
{
    req->session()->erase("userId");
    Json::Value json;
    json["message"] = "退出成功！";
    co_return HttpResponse::newHttpJsonResponse(json);
}
