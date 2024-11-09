/**
 *
 *  LoginCheckFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class LoginCheckFilter : public HttpFilter<LoginCheckFilter>
{
  public:
    LoginCheckFilter() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

