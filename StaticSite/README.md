# 准备依赖

以 Ubuntu 20.04 为例。（其他系统（包括Ubuntu的其他版本）没有实操，不敢bb）

## 必备依赖

```shell
$ sudo apt-get install libjsoncpp-dev
$ sudo apt-get install uuid-dev
$ sudo apt-get install zlib1g-dev
```

## 可选依赖

```shell
$ sudo apt-get install libssl-dev
$ sudo apt-get install libbrotli-dev
$ sudo apt-get install postgresql-all
$ sudo apt-get install libmariadbclient-dev
$ sudo apt-get install libsqlite3-dev
$ sudo apt-get install libhiredis-dev
```

### c-ares

Ubuntu20.04 有一个`libc-ares-dev`，但是它版本较低。

Trantor 的[这个PR](https://github.com/an-tao/trantor/pull/331)，用到了 `c-ares` 较新版本的功能。

如果您使用的是较老版本的 `drogon` 和 `trantor`，可以直接 `apt-get install libc-ares-dev`。

我们这里使用源码安装 `c-ares`：

```shell
$ git clone https://github.com/c-ares/c-ares
$ cd c-ares
$ mkdir build && cd build
$ cmake ..
$ make -j8
$ sudo make install
```

#### 可能存在的问题

> 运行 `drogon_ctl` 时提示：`undefined symbol: ares_getaddrinfo`，可能是 `drogon_ctl` 没有找到 `libcares.so.2` 的动态连接库。
> 可以执行：`which drogon_ctl`，得到 `drogon_ctl` 的路径。
> 然后执行：`ldd /path/to/drogon_ctl`，找到 `libcares.so.2` 的路径。
> 最后将其加入环境变量：`export LD_LIBRARY_PATH=/path/to/libcares.so.2:$LD_LIBRARY_PATH`。（注意：只要路径，不需要动态库文件）
> 建议将上一条命令追加到 `~/.bashrc` 中，然后 `source ~/.bashrc`。

### yamlcpp

`yamlcpp` 也需要使用源码安装：

```shell
$ git clone https://github.com/jbeder/yaml-cpp.git
$ cd yaml-cpp
$ mkdir build && cd build
$ cmake ..
$ make -j8
$ sudo make install
```

# 安装 Drogon

1. 拉取最新代码

```shell
$ git clone https://github.com/drogonframework/drogon.git
```

2. 获取 `trantor` 依赖

```shell
$ cd drogon
$ git submodule update --init
```

3. 安装 `Drogon`

```shell
$ mkdir build && cd build
$ cmake ..
$ make -j8
$ sudo make install
```

4. 检查是否安装成功

```shell
$ drogon_ctl --version
```

# 静态网站实例

使用 `drogon_ctl` 创建一个项目：

```shell
$ drogon_ctl create project <project_name>
$ cd <project_name>
```

## 项目的目录结构

```shell
$ tree .
.
├-- CMakeLists.txt # CMake 配置文件
├── build # 空目录，用于编译
├── config.json # 配置文件，和 yaml 格式的二选一，具体通过修改 app().loadConfigFile() 的参数进行选择
├── config.yaml # 配置文件，1.8.4 版本开始支持，在安装 drogon 时需要提供 yaml-cpp 的支持
├── controllers # 控制器目录
├── filters # 过滤器目录
├── main.cc # 主程序，入口文件
├── models # 数据模型目录
|   └── model.json # 数据模型配置文件，用于生成代码
├-- plugins # 插件目录
├-- test # 测试目录
|   ├── CMakeLists.txt
|   └── test_main.cc
└-- views # 视图目录，存放视图文件
```

剩下的内容就看代码吧。
