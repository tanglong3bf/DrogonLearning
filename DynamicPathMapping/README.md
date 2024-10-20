# DynamicPathMapping

代码见 `DynamicPathMappingDemo` 目录。

1. 类内绑定的路径关系：

| 控制器 | 路径 | 请求方式 |
| ------ | ---- | -------- |
| aa     | /    | Get      |
| bb     | /    | Post     |

2. 主动调用 `registerHttpSimpleController` 函数，实现的路径映射关系如下：

| 控制器 | 路径 | 请求方式  |
| ------ | ---- | --------- |
| bb     | /bb  | Get, Post |

3. 配置文件内绑定的关系：

| 控制器 | 路径 | 请求方式  |
| ------ | ---- | --------- |
| aa     | /aa  | Get, Post |

## 优先级

其余两种方式其实都是框架在自动调用 `registerHttpSimpleController` 。

类内绑定的时机是在静态代码中，早于 `main` 函数执行。

配置文件的绑定时机在 `loadConfigFile` 函数执行期间。

在路径和请求方式相同的情况下，如果绑定到了不同的控制器，后调用的会覆盖前面的。
