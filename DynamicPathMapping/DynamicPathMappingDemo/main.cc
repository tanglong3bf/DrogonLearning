#include <drogon/drogon.h>

int main()
{

    // 关于第三个参数，类型是可以省略的，视频里把它搞得复杂化了
    drogon::app().registerHttpSimpleController("/bb",
                                               "bb",
                                               {drogon::Get, drogon::Post});

    // Load config file
    drogon::app().loadConfigFile("../config.json");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
