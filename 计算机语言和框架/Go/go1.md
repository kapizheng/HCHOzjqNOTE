### 函数是GO中的一等公民！

### 主体结构

- 声明该包
- 导入包

- 主函数

### 标识符

- 大字母开头是全部可见。
- 小字母开始是只有本包可见。





### 1、go的闭包

- 匿名函数可以改变函数外部的变量，所以包括该变量的一个环境叫做闭包。

## 2、匿名函数

- 类似于C++lambda，可以改变函数外的变量。

### 3、协程

**一种用户态的轻量级线程，**协程的调度完全由用户控制，协程间切换只需要保存任务的上

下文，没有内核的开销。

### 4、defer

- 保证了无论该函数最后执行情况如何，最后都能执行改行代码。后进后出的顺序。

### 

### 5、go的多态

是指一个方法，不同对象使用有不同结果

```
type jiekou interface{
	name string
}
type stu struct{
	jiekou
}
func (*stu)show(){
	fmt.Print("学生")
	fmt.Println(name)
}
type tea sturct{
	jiekou
}
func (*tea)show(){
	fmt.print("老师")
	fmt.Println(name)
}
func main(){
	s:=stu{"zjq"}
	t:=tea{"tea"}
	s.show()
	t.show()
}

```

### 6、Go中的make

- go中的make只能用来分配及初始化类型为slice、map、chan的数据，new可以分配任意类型的数据。
- new分配返回的是指针，即类型*type。make返回引用。
- new的分配的空间被清零。make分配空间后，会进行初始化。

### 7、Go语言的垃圾回收机制

- 通过独立的进程执行，它会搜索不再使用的变量。并将其释放。
- 
