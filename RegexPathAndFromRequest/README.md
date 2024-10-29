# RegexPathAndFromRequestDemo

## 使用正则

动态路径参数可以使用正则来限制参数的格式。
例如，我们可以限制参数只能是数字：

```c++
METHOD_LIST_BEGIN
ADD_METHOD_VIA_REGEX(blog::remove,
                     "/api/blog/remove/([1-9]\\d*)",
                     Get);  // path is /api/blog/remove/{blog_id}
METHOD_LIST_END
void remove(const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            int blog_id);
```

正则表达式里的一个括号就对应一个分组，而每一个分组会对应到参数列表的一个参数，比如上面的例子里，正则表达式里的 `([1-9]\\d*)` 对应到 `blog_id` 参数。

如果有多个参数，则可以用多个分组，比如：

```c++
METHOD_LIST_BEGIN
ADD_METHOD_VIA_REGEX(comment::list,
                     "/api/blog/list/(\\d+)-(\\d+)-(\\d+)",
                     Get);  // path is /api/blog/edit/{year}-{month}-{day}
METHOD_LIST_END
// 假设是一个获取指定日期的评论列表的接口
void list(const HttpRequestPtr &req,
          std::function<void(const HttpResponsePtr &)> &&callback,
          int year,
          int month,
          int day) const;
```

这样，路径 `/api/blog/list/2021-07-15` 对应的 `year` 参数为 `2021`，`month` 参数为 `7`，`day` 参数为 `15`。

如果存在分组嵌套，则使用左括号确定先后顺序。

## fromRequest

对于更加复杂的参数，我们可以把它们放到请求体中，再通过定义 `drogon::fromRequest<>` 的偏特化来进行解析。

和 json 相关的例子可以直接看代码。

更复杂的情况：

```cpp
struct user {
    std::string username;
    std::string password;
};
namespace drogon {
template <>
inline user fromRequest(const HttpRequest &req)
{
    user result;
    // 如果是 json 格式，使用 getJsonObject
    auto jsonPtr = req.getJsonObject();
    // 如果是 xml 等其他格式，需要自行解析，或借助第三方库
	// auto body = req.body();
    // ... // 从 json/body 中解析 user 对象
    return result;
}
}
```
