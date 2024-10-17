# Prometheus

Prometheus是由谷歌公司使用go语言开发的一个**服务监控系统**，可以监控内存占用、CPU使用率、网络带宽等数据，并在数据异常时给出告警。

官方文档：https://prometheus.io/docs/introduction/overview/
中文文档：https://hulining.gitbook.io/prometheus

## docker安装Prometheus

使用docker安装：

```shell
docker run -d --name=prometheus
    -p 9090:9090
    -v ~/docker/data/prometheus.yml:/etc/prometheus/prometheus.yml
    prom/prometheus
```

使用 `prom/prometheus` **镜像**，后台（ `-d` ）运行（ `run` ）一个**容器**，并给**容器**起一个名字（ `--name` ）叫 `prometheus` 。

建立起一个**数据卷**（ `-v` ），认为宿主机的 `~/docker/data/prometheus.yml` 文件和容器内的 `/etc/prometheus/prometheus.yml` 文件是同一个文件。

同时接管宿主机的 `9090` 端口号，把所有访问到 `9090` 端口号的请求都转发到**容器**内部的 `9090` 端口号。（格式： `-p 宿主机端口:容器内端口` ）

## 配置并运行Prometheus

修改配置文件：

```yml
scrape_configs:
  - job_name: "prometheus"
    static_configs:
      - targets: ["localhost:9090"]
  - job_name: "drogon_plugin_demo" # 监控的终端名称
    # metrics_path: "/metrics" # 默认值为 /metrics
    scrape_interval: 5s # 访问 /metrics 接口的频率
    scrape_timeout: 5s # 接口访问超时时间
    static_configs:
      - targets: ["localhost:8000"] # 此终端下的多个节点
```

重新运行**容器**：

```shell
docker restart prometheus
```

## 浏览器访问

```shell
localhost:9090
```

我们主要关注 `Graph` 页面和 `Status/Targets` 页面。

`Status/Targets` 页面可以看到当前监控的终端。

`Graph` 页面可以把监控到的数据展示出来，可以使用各种表达式对数据进行处理。

### /metrics数据

Prometheus通过访问节点的 `/metrics` 路径（默认值、可通过配置文件修改）来获取每个节点的数据，比如 `localhost:9090/metrics` 。

对于每一个采集器都满足如下格式：

```
# HELP 采集器（Collector）名称 帮助信息
# TYPE 采集器名称 采集器类型（counter、gauge、histogram、summary）（计数器、仪表盘、直方图、摘要）
... （0-n行的样本（Sample），根据采集器类型的不同，格式也不同）
```

每行样本的格式一般为：

```
样本名称 数据
```

每行样本可能会额外携带一些标签，这些标签可以用于查询时的过滤条件。

```
样本名称{键="值"} 数据
```

#### 名词解释

这里只是我个人的一些理解，不一定完全准确。

采集器（Collector）：采集器存在不同的类型，我们也可以指定采集器的标签名字，标签用于区分采集器下不同的指标（Metric）。

指标（Metric）：同一个采集器下可以存在不同的指标，指标的类型也与所属的采集器一致，不同的指标之间具有相同的标签名，通过标签的值可以区分同一采集器下的指标。

样本（Sample）：同一个指标下可能会存在多个样本，样本可能会在指标的基础上添加额外的标签（比如le），每一条样本对应一条数据，和一个时间戳（看不到）。

指标的名称和采集器相同，但是样本的名字可能不同，当指标类型为histogram时，样本的名字会添加一些额外的后缀。

我们在 `Graph` 页面输入的是样本的名字，需要加上那些后缀。

#### 一些栗子

1. counter示例：

```
# HELP net_conntrack_listener_conn_accepted_total Total number of connections opened to the listener of a given name.
# TYPE net_conntrack_listener_conn_accepted_total counter
net_conntrack_listener_conn_accepted_total{listener_name="http"} 5
```

2. gauge示例：

```
# HELP process_open_fds Number of open file descriptors.
# TYPE process_open_fds gauge
process_open_fds 47
```

3. histogram示例：

```
# HELP go_gc_heap_allocs_by_size_bytes Distribution of heap allocations by approximate size. Bucket counts increase monotonically. Note that this does not include tiny objects as defined by /gc/heap/tiny/allocs:objects, only tiny blocks.
# TYPE go_gc_heap_allocs_by_size_bytes histogram
go_gc_heap_allocs_by_size_bytes_bucket{le="8.999999999999998"} 16684
go_gc_heap_allocs_by_size_bytes_bucket{le="24.999999999999996"} 136967
go_gc_heap_allocs_by_size_bytes_bucket{le="64.99999999999999"} 315521
go_gc_heap_allocs_by_size_bytes_bucket{le="144.99999999999997"} 421507
go_gc_heap_allocs_by_size_bytes_bucket{le="320.99999999999994"} 443832
go_gc_heap_allocs_by_size_bytes_bucket{le="704.9999999999999"} 448934
go_gc_heap_allocs_by_size_bytes_bucket{le="1536.9999999999998"} 451554
go_gc_heap_allocs_by_size_bytes_bucket{le="3200.9999999999995"} 453418
go_gc_heap_allocs_by_size_bytes_bucket{le="6528.999999999999"} 454576
go_gc_heap_allocs_by_size_bytes_bucket{le="13568.999999999998"} 455343
go_gc_heap_allocs_by_size_bytes_bucket{le="27264.999999999996"} 455691
go_gc_heap_allocs_by_size_bytes_bucket{le="+Inf"} 456327
go_gc_heap_allocs_by_size_bytes_sum 2.59185312e+08
go_gc_heap_allocs_by_size_bytes_count 456327
```

`Prometheus` 在收集到数据之后会添加额外的两个标签，用于指明数据的来源。 `job` 用于区分终端， `instance` 用于区分节点。

# PromExporter

来一段配置：

```json
{
  "name": "drogon::plugin::PromExporter",
  "dependencies": [],
  "config": {
    // The path of the metrics. the default value is "/metrics".
    "path": "/metrics",
    // The list of collectors.
    "collectors": [
      {
        // The name of the collector.
        "name": "http_requests_total",
        // The help message of the collector.
        "help": "The total number of http requests",
        // The type of the collector. The default value is "counter".
        // The other possible value is as following:
        // "gauge", "histogram".
        "type": "counter",
        // The labels of the collector.
        "labels": ["method", "code"]
      }
    ]
  }
}
```

此时访问drogon的 `/metrics` ，得到如下结果：

```
# HELP http_requests_total The total number of http requests
# TYPE http_requests_total counter
```

只有 `collector` 的帮助信息和类型，没有样本数据，因为我们只是配置了 `cellector` 的信息，还没有采集数据，数据并不会凭空产生。

## counter收集数据

### 单接口

**准备counter**

```cpp
class UserController : public drogon::HttpController<UserController>
{
  public:
    // ...
    UserController()
    {
        // 获取插件
        auto *promExporter = app().getPlugin<drogon::plugin::PromExporter>();
        // 指定收集器（collector）的名称、并指定收集器下指标（metric）的属性值
        counter_ =
            promExporter
                ->getCollector<monitoring::Counter>("http_requests_total")
                ->metric({"GET", "200"});
    }

  private:
    std::shared_ptr<drogon::monitoring::Counter> counter_;
};
```

**收集数据**

```cpp
Task<HttpResponsePtr> UserController::info(const HttpRequestPtr req) const
{
    counter_->increment();
    // ...
}
```

### 提取到Middleware

别忘了修改ADD_METHOD_TO，添加中间件的名字

```cpp
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

```

## gauge

和counter的区别仅在于其值可以减少，可能会在这里补充一个案例

## histogram

**配置文件**

```json
{
  "name": "http_request_duration_seconds",
  "help": "Histogram of latencies for HTTP requests.",
  "type": "histogram",
  "labels": ["url"]
}
```

**代码**

```cpp
void TimerMiddleware::invoke(const HttpRequestPtr &req,
                             MiddlewareNextCallback &&nextCb,
                             MiddlewareCallback &&mcb)
{
    static auto *promExporter = app().getPlugin<plugin::PromExporter>();

    // nextCb 就表示正常的走后续流程，并用回调函数的参数接收响应体
    nextCb([req, mcb = std::move(mcb)](const HttpResponsePtr &resp) {
        using namespace std::chrono;

        // mcb 表示向客户端做出响应
        mcb(resp);

        // 获取处理请求的时间差
        auto start = req->creationDate();
        auto end = trantor::Date::now();
        auto duration =
            end.microSecondsSinceEpoch() - start.microSecondsSinceEpoch();
        auto seconds = static_cast<double>(duration) / 1000000.0;

        // 具体可以看metric函数的实现，这里的参数包会被转发到 Histogram
        // 的构造函数的参数列表中
        promExporter
            ->getCollector<monitoring::Histogram>(
                "http_request_duration_seconds")
            ->metric({req->getPath()},
                     std::vector<double>{0.1, 0.2, 0.4, 1, 3, 10},
                     1min,
                     5)
            ->observe(seconds);
    });
}

```
