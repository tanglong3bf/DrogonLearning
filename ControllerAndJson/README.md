# ControllerAndJsonDemo

## HttpController

### 绑定请求路径

```cpp
namespace api {
class blog : public drogon::HttpController<blog> {
  public:
    METHOD_LIST_BEGIN
        METHOD_ADD(blog::list,
                   "/list/{category_id}",
                   Get);  // path is /api/blog/list/{category_id}
        // 更合适的请求方式为 DELETE，但为了演示方便，使用 GET
        ADD_METHOD_TO(blog::remove,
                      "/api/blog/remove/{category_id}",
                      Get);  // path is /api/blog/remove/{category_id}
    METHOD_LIST_END
  public:
    // 省略处理函数的声明
}; // class blog
} // namespace api
```

METHOD_ADD和ADD_METHOD_TO的区别：

前者会自动将控制器的命名空间和类名添加到请求路径的前面，后者则不会。

### 和 HttpSimpleController 的区别：

HttpSimpleController 类型的控制器只能有一个处理函数，而 HttpController 类型的控制器可以有多个处理函数。

HttpController 可以获取动态路径参数，而 HttpSimpleController 不能。

HttpController 的处理函数在注册到框架的时候可以将命名空间和控制器名添加到请求路径的前缀。

## Json 格式数据的响应

```c++
Json::Value json;
// json
auto r = HttpResponse::newHttpJsonResponse(json);
callback(r);
```

其中的 `newHttpJsonResponse` 可以接收一个 `Json::Value` 类型的参数，会以此为基础生成一个响应体。

在此函数内部，会自动设置 `resp` 对象的 `Content-Type` 为 `application/json` 类型，并将传递进来的参数放到响应体中。

## 当时留下的那些坑：

坑一：关于数据库，后期有一系列的视频进行展开讲解，从 数据库同步接口和全局异常处理器 到 ORM-关联查询。

坑二：对于敏感操作，我们可以通过 `Filter` 来检查用户是否登录，同时检查用户的权限。相关内容在后期的 Filter的使用和案例 视频中有展开讲解。

坑三：请求路径的骚操作，就是下一期视频 [HttpController与自定义类型参数的接收](../RegexPathAndFromRequest/README.md) 中的内容。
