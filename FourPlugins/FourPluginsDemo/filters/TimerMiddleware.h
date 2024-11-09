/**
 *
 *  TimerMiddleware.h
 *
 */

#pragma once

#include <drogon/HttpMiddleware.h>
using namespace drogon;

class TimerMiddleware : public HttpMiddleware<TimerMiddleware>
{
  public:
    TimerMiddleware()
    {
    }

    virtual void invoke(const HttpRequestPtr &req,
                        MiddlewareNextCallback &&nextCb,
                        MiddlewareCallback &&mcb) override;
};
