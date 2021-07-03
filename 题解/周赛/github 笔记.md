#### 1、本地初始化

- `git init `

​	作用：会出现一个.git的文件，保存与本地库相关的文件

#### 2、设置签名

1、项目级别：

​	`git config user.name _____`

​	`git config user.email ____`

2、系统级别

​	`git config --global user.name _____`

​	`git config --global user.email _____`

3、查看

​	`git config`

#### 3、库与库操作

- `git status`表示目前所有库的状态

- `git add ____`把文件提到缓存库

- `git rm --cached _____` 后悔add操作

- `git commit _____`提到本地库

#### PS: Vim的一些操作

- `:set nu`显示行号

- `:wq`保存退出

#### PS: Linux 的操作

- `ll`&`-l` 显示目录(格式不一样)

- `ls -la`显示目录(包括隐藏)

- `ls`显示目录

#### 4、版本操作

1、显示

- `git log --pretty=oneline`一行表示

- `git log --oneline`

- `git reflog`显示操作日志

2、操作

- 基于索引 	`git reset --hard hash值`	跑到hash的位置

- 基于“^"	`git reset --hard HEAD ^` 跑到下一个位置

- 基于”~“	`git reset --hard HEAD~n`向下移动n个位置

3、`git help reset`查看帮助文档

#### 5、查看文件差异

- `git diff ` 查看当前工作与暂存区的差别
- `git diff HEAD` 查看当前与最近提交的差别
- `git diff HEAD^ ______`和___的上一个文件比较

#### 6、分支与合并

- 显示分支 `git branch -v`
- 创建分支 `git branch ____`
- 切换分支 `git checkout _____`

创建+切换=`git checkout _____`

- 切换到上一个分支`git checkout -`

- 合并分支

  切换到要合并的分支

  `git merge --no-ff_____`要合并的内容   __--no-ff的作用是直接复制一份心的与之合并 __ 

- 图示分支

  `git log --graph`

#### 7、合并冲突，历史冲突

- 提示冲突
- 进入编辑器
- 修改
- add commit

#### 8、修改日志

`git commit --amend`进入vim

#### 9、压缩历史或永久删除

- `git rebase -i HEAD~2 `以最近两个历史记录为对象
- 编辑：把要删除的pick改为fix up 关闭，结束

#### 10、本地库与远程库交互

- `git remote add 别名 地址`

  给地址起个别名

- `git push -u origin master `

  将master push 到origin

  __-u__的作用是以后默认push和pull的操作为origin与master之间的操作

- 别的分支与远程库的交互，先切换再push

- 获取远程库

  `git clone 地址`

  注意不要在之前的目录之下，防止被覆盖

- `git branch -a`显示本地与远程库的信息

- 获取别的分支

  `git checkout -b 新分支名 origin/获取的分支名`

  -b是新建分支，origin是别名

- 改新分支，把远程分支拉过来

  git pull origin 分支名