#include <drogon/drogon.h>
#include <drogon/nosql/RedisResult.h>

using namespace drogon;

int main()
{
    // 如果需要在程序启动时，向Redis数据库中写入初始数据，可以用以下代码：
    // app().registerBeginningAdvice([] {
    //     auto redis = app().getRedisClient();
    //     redis->execCommandSync(
    //         [](const nosql::RedisResult &r) {
    //             return r.type() == nosql::RedisResultType::kInteger;
    //         },
    //         "DEL website_name user_list");
    //     redis->execCommandSync(
    //         [](const nosql::RedisResult &r) {
    //             return r.type() == nosql::RedisResultType::kStatus &&
    //                    r.getStringForDisplaying() == "OK";
    //         },
    //         "SET website_name blog");
    //     redis->execCommandSync(
    //         [](const nosql::RedisResult &r) {
    //             return r.type() == nosql::RedisResultType::kInteger &&
    //                    r.asInteger() == 4;
    //         },
    //         "RPUSH user_list zhangsan lisi wangwu zhaoliu");
    // });

    app().registerBeginningAdvice([] {
        auto redis = app().getRedisClient();

        // 如果存在 website_name 这个键，但是类型不是 string
        // 可能会抛出 nosql::RedisException 异常
        const auto websiteName = redis->execCommandSync(
            [](const nosql::RedisResult &r) -> std::optional<std::string> {
                LOG_INFO << r.getStringForDisplaying();
                if (r)
                {
                    return r.asString();
                }
                return std::nullopt;
            },
            "GET %s",
            "website_name");
        if (websiteName)
        {
            // 如果为空，这一行会抛出 std::bad_alloc 异常，加层判断
            LOG_INFO << *websiteName;
        }

        try
        {
            const auto websiteName = redis->execCommandSync(
                [](const nosql::RedisResult &r) -> std::optional<std::string> {
                    LOG_INFO << r.getStringForDisplaying();
                    if (r)
                    {
                        return r.asString();
                    }
                    return std::nullopt;
                },
                "GE %s",
                "website_name");

            if (websiteName)
            {
                // 如果为空，这一行会抛出 std::bad_alloc 异常，加层判断
                LOG_INFO << *websiteName;
            }
        }
        catch (const nosql::RedisException &e)
        {
            LOG_ERROR << e.what();
        }

        // 如果存在 user_list 这个键，但是类型不是 list
        // 可能会抛出 nosql::RedisException 异常
        const auto userList = redis->execCommandSync(
            [](const nosql::RedisResult &r) -> std::vector<std::string> {
                LOG_INFO << r.getStringForDisplaying();
                auto array = r.asArray();
                std::vector<std::string> result;
                for (const auto &item : array)
                {
                    result.emplace_back(item.asString());
                }
                return result;
            },
            "LRANGE %s 0 -1",
            "user_list");

        LOG_INFO << userList.size();
        for (const auto &item : userList)
        {
            LOG_INFO << item;
        }
    });
    // Load config file
    app().loadConfigFile("../config.json");
    // Run HTTP framework,the method will block in the internal event loop
    app().run();
    return 0;
}
