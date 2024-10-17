/**
 *
 *  CounterMiddleware.cc
 *
 */

#include "CounterMiddleware.h"
#include <drogon/drogon.h>
#include <drogon/utils/monitoring/Counter.h>

using namespace drogon;

void CounterMiddleware::invoke(const HttpRequestPtr &req,
                               MiddlewareNextCallback &&nextCb,
                               MiddlewareCallback &&mcb)
{
    // nextCb 就表示正常的走后续流程，并用回调函数的参数接收响应体
    nextCb([req, mcb = std::move(mcb)](const HttpResponsePtr &resp) {
        // mcb 表示向客户端做出响应
        mcb(resp);

        static auto *promExporter =
            app().getPlugin<drogon::plugin::PromExporter>();

        auto url = req->path();
        auto method = drogon::to_string(req->method());
        auto code = std::to_string((int)resp->getStatusCode());

        // Collector 类内部有一个缓存，我们只需要获取就好，不需要自己再存一份
        promExporter->getCollector<monitoring::Counter>("http_requests_total")
            ->metric({url, method, code})
            ->increment();
    });
}
