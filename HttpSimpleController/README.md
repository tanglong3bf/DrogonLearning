# HttpSimpleControllerDemo

可以使用命令行工具（`drogon_ctl`）创建简单控制器（`HttpSimpleController`）：

```shell
$ drogon_ctl create controller <controller_name>
```

**简单控制器**的特点：

1. 每一个控制器可以绑定多个请求路径
2. 不论绑定多少个路径，都会走同一个处理函数
