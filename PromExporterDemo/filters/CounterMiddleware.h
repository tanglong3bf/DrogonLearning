/**
 *
 *  CounterMiddleware.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
#include <drogon/HttpMiddleware.h>
using namespace drogon;

class CounterMiddleware : public HttpMiddleware<CounterMiddleware>
{
  public:
    CounterMiddleware()
    {
    }

    virtual void invoke(const HttpRequestPtr &req,
                        MiddlewareNextCallback &&nextCb,
                        MiddlewareCallback &&mcb) override;
};
