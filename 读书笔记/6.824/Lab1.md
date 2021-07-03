1. 一个map语句需要分成中间键到筒里面，从而放到nReduce个reduce任务里面。
2. workder实现如何输出reduce为out-x
3. mr-out-x文件需要包含reduce的输出。一行通过go的“%v %v”格式输出。可以在mrsequential中看到。
4. 当工作结束后，工作进程应该退出，这时候得要用call。
5. 开始的时候在worker的worker中去发送一个rpc到coo中请求任务。
6. map喝reduce用插件包加载好了
7. 改变了mr的话，需要rebuild
8. 最后文件名应该是mr-x-y,x是nmap,y是nreduce
9. -race去测试竞态条件
10. reduce需要等最后一个map执行结束后才能开始
11. 



