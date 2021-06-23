# Go的学习

## 1、切片

### 基础

- 切片是基于数组构建的，但是更加强大和便利。
- 能用make创建`func make([]T,len,cap)[]T`类型，长度，容量，加入cap被忽略就默认为指定长度。
- 加入切片为nil（零值）len和cap都为0
- 作为函数传递的时候是值传递。

### 内幕

- 每个切片都是一个数组片段的描述，有指针，长度和容量。指针和长度决定该切片能取那个范围，而容量有时候会表示包含该切片的数组长度大小。
- 对切片进行复制的时候，对新切片的操作会对原切片造成影响。

![image-20210531150650883](C:\Users\kapizheng\AppData\Roaming\Typora\typora-user-images\image-20210531150650883.png)

![image-20210531151756788](C:\Users\kapizheng\AppData\Roaming\Typora\typora-user-images\image-20210531151756788.png)

![image-20210531162545537](C:\Users\kapizheng\AppData\Roaming\Typora\typora-user-images\image-20210531162545537.png)

![image-20210531192009947](C:\Users\kapizheng\AppData\Roaming\Typora\typora-user-images\image-20210531192009947.png)

## 2、go的方法接口等内容

- 对于方法接收者，假如是值接受就只会更改其副本内容，假如是指针的话就会更改其本来的内容。
- 因为上面一条，所以接收者和参数的一个区别是，参数是要一一对应的，但是接收者可以为值也可以为指针

- go接收者可以为nil，这个时候需要在接口函数实现中进行判断nil。但是不能对空接口进行函数调用。

- 空接口可以存放任何数据。



- `panic` 能够改变程序的控制流，调用 `panic` 后会立刻停止执行当前函数的剩余代码，并在当前 Goroutine 中递归执行调用方的 `defer`；
- `recover` 可以中止 `panic` 造成的程序崩溃。它是一个只能在 `defer` 中发挥作用的函数，在其他作用域中调用不会发挥作用；

### 3、go mod

go mod tidy 是用来拉依赖的

go mod vendor 是来将依赖放到vendor包里面的





### 写一个接口，将测试从项目入口进入，能否触发该接口，但是！我项目还没启动呢。。。。。
