[论文]: https://pdos.csail.mit.edu/6.824/papers/mapreduce.pdf

### 第一节 

- MapReduce 是将多文件进行一个数据处理的模型框架
  - 先将数据切分也就是map，再将数据shuttle之后进入reduce中去。

### 第二节给了一些简单示例

- 给了几个伪代码
- 简单理解mapreduce就是map将数据分割，reduce将数据归类的一个模型。
- 各种实际例子：
  - **倒排索引**：搜索引擎。具体的一个作用是为了能够通过value去查找该信息所在的位置。例如如何查找一个单词在哪些文档当中。

### 第三节给了集群中Map reduce的实现

### 第四节给了几个改进

### 第五节对几个实现进行一个性能度量

### 第六节探索谷歌的mapreduce

### 第七节讲了未来的mapreduce

