/**
 *
 *  TimerMiddleware.cc
 *
 */

#include "TimerMiddleware.h"
#include <drogon/HttpAppFramework.h>
#include <drogon/plugins/PromExporter.h>
#include <drogon/utils/monitoring/Histogram.h>

using namespace drogon;

void TimerMiddleware::invoke(const HttpRequestPtr &req,
                             MiddlewareNextCallback &&nextCb,
                             MiddlewareCallback &&mcb)
{
    // nextCb 就表示正常的走后续流程，并用回调函数的参数接收响应体
    nextCb([req, mcb = std::move(mcb)](const HttpResponsePtr &resp) {
        using namespace std::chrono;

        // mcb 表示向客户端做出响应
        mcb(resp);

        // 获取处理请求的时间差
        auto start = req->creationDate();
        auto end = trantor::Date::now();
        auto duration =
            end.microSecondsSinceEpoch() - start.microSecondsSinceEpoch();
        auto seconds = static_cast<double>(duration) / 1000000.0;

        static auto *promExporter = app().getPlugin<plugin::PromExporter>();

        // 具体可以看metric函数的实现，这里的参数包会被转发到 Histogram
        // 的构造函数的参数列表中
        promExporter
            ->getCollector<monitoring::Histogram>(
                "http_request_duration_seconds")
            ->metric({req->getPath()},
                     std::vector<double>{0.1, 0.2, 0.4, 1, 3, 10},
                     1min,
                     5)
            ->observe(seconds);
    });
}
