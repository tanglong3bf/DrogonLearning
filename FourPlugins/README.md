# 四个插件

## GlobalFilters

`GlobalFilters` 是一个**全局过滤器**，只需要简单的配置即可以让指定的过滤器在所有接口及**静态文件**生效，省去了反复设置的麻烦。

### 配置项

- `filters` ：过滤器名字数组
- `exempt` ：排除掉的路径，支持正则表达式

## Redirector

`Redirector` 插件通过注册不同的回调函数完成请求的**重定向**和**转发**。

### 回调函数类型

- `RedirectorHandler` ：可以指定**重定向**后的协议、域名、请求路径，任何一项作出修改，插件会做出 `302` 的响应状态码，并将几项设置拼接成新的网址放到响应头的`location`字段中。如果认为请求非法，也可以返回 `false` ，此时插件会自动做出 `404` 的响应状态码。
- `PathRewriteHandler` ：大体上和上一条类似，区别在于它只能修改请求路径，返回值表示是否修改过请求路径。
- `ForwardHandler` ：实现请求的转发，只需要指定新的请求路径即可。

## SecureSSLRedirector

此插件可以自动地将 `http` 地请求重定向到 `https` ，需要依赖 `Redirector` 插件。

### 配置项

- `ssl_redirect_exempt` ：排除掉的路径数组，支持正则
- `secure_ssl_host` ：重定向的域名和端口号，如： `localhost:8849`

## SlashRemover

此插件用于移除请求路径中多余的斜线，支持重定向和转发两种方式，需要依赖 `Redircetor` 插件。

### 配置项

- `remove_trailing_slashes` ：是否要移除末尾的斜线。
- `remove_duplicate_slashes` ：是否要将连续的多个斜线移除到只剩一个。
- `redirect` ：如果为 `true` ，重定向到新路径，如果为 `false` ，转发到新路径。