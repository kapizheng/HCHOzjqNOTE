### **i7-3** **2C. 纳新一百的石子游戏**

`Nim game`

![image-20200119002736708](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20200119002736708.png)

有结论：异或和为0的时候，先手输，反之不为0先手赢。

但题目要求的是前序列有多少次先手操作可以赢得比赛，那么有如下。

`y > x or y`x表示异或和，x异或y表示y还没出手的，情况，如果`y`的位数大于`y`还没出手的情况，那么可以构成最终异或和为0的情况。那么代码也出来了，简单判断就可以了。

```C++
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N=1e5+50;
ll a[N];
int num[100];
void solve(ll x)
{
	int cnt=0;
	while(x)
	{
		if(x%2)num[cnt]++;
		x/=2;
		cnt++;
	}
}
int get(ll x)
{
	int cnt=0;
	while(x)
	{
		cnt++;x/=2;
	}
	return cnt-1;
}

int main()
{
	int n;cin>>n;
	ll x=0;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		x^=a[i];
		solve(a[i]);
		printf("%d\n",num[get(x)]);
	}
}
/*
输入样例：
6
0 0 2 8 7 0
输出样例：
0
0
1
1
1
1
*/
```



### **7-5** **2E. 阔力梯的树**

这题目可能需要树链刨分的操作吧？？？

题目如题，然后用的是启发式合并的思想。`add`函数用的就是这个内容。然后对于每个节点的子节点，先查看非重子节点，然后再清零贡献。再去合并重子节点以及它与所有轻子节点的贡献。emm，比较迷代码是如何构建的。//值得回味

![image-20200118235614027](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20200118235614027.png)

```C++
#include<bits/stdc++.h>

using namespace std;
set<int>s;
long long ans[100005];
int sz[100005]; 
int son[100005];
long long res=0;
vector<int>g[100005];
typedef long long ll;
void dfs1(int u)//求重子树 
{
	sz[u]=1;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];dfs1(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
}
void  add(int u)
{
	if(!s.size()){
		s.insert(u);return ;
	}
	s.insert(u);
	auto it=s.find(u);
	if(it==s.begin()){
		auto pre=++it;
		int v=*pre;
		res+= (ll)(u-v)*(u-v);
	}else if(it==(--s.end())){
		auto pre=--it;
		int v=*pre;
		res+= (ll)(u-v)*(u-v);
	}else 
	{
		auto pre=--it;
		int v=*pre;++it;
		auto last=++it;
		int y=*last;
		res-=(ll)(v-y)*(v-y);
		res+= (ll)(u-v)*(u-v)+(ll)(u-y)*(u-y);
	}
}

void dfs3(int u)
{
	add(u);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		dfs3(v);
	}
}

void dfs2(int u)
{

	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==son[u])continue;
		dfs2(v);
		s.clear();
		res=0;
	}	
	if(!son[u]){
		add(u);return ;
	}
	dfs2(son[u]);
	add(u);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==son[u])continue;
		dfs3(v);
	}
	ans[u]=res;
	
}

int main()
{
	int n;scanf("%d",&n);
	for(int i=2;i<=n;i++){
		int f;scanf("%d",&f);
		g[f].push_back(i);
	}
	dfs1(1);
	dfs2(1);
	
	for(int i=1;i<=n;i++){
		printf("%lld\n",ans[i]);
	}
} 
/*输入样例：
5
1
1
1
1

      
    
5
1
2
3
4

      
    
输出样例：
4
0
0
0
0

      
    
4
3
2
1
0*/
```



### H **7-11** **2K. 破忒头的匿名信**

![image-20200115130431897](C:\Users\zjq\AppData\Roaming\Typora\typora-user-images\image-20200115130431897.png)

### 输出格式

如果有可能让萨博写出破忒头想要的信件内容，那么输出一个正整数，表示最小需要付出的代价。否则，输出-1。

### 输入样例：

```in
4
ab 5
cd 10
abc 100
d 1
abcd

      
    
1
ab 1
abc

      
    
```

### 输出样例：

```out
15

      
    
-1
```

__题解__

AC自动机题目，题目是给出一些串和它的花费和一个长串。求用小串去覆盖大串需要的最小花费。

比赛时候想到ac自动机和`dp`，然后就不会了。赛后看了看题解，搞了蛮久，因为数据得要开`longlong`

`longlong 初始化最大值要用1ll*INF*INF`

接下去就在`dp`上搞，在插入小串的时候，要用一个数组表明这是第几个字母，然后才可以`dp`操作。

贴个板子吧，虽然没有优化ac自动机。

```C++
#include<bits/stdc++.h>

using namespace std;
int p[500005];
const int INF=0x3f3f3f3f;
long long dp[500005];
struct AC
{
	int ch[500004][30];
	int fail[500004];
	int val[500004];
	int dep[500005];
	int cnt;
	void init()
	{
		cnt=1;memset(ch[0],0,sizeof ch[0]);
		
	}
	int idx(char ch){return ch-'a';}
	
	void insert(char *str,int pos)
	{
		int root=0;
		for(int i=0;i<strlen(str);i++){
			int c=idx(str[i]);
			if(ch[root][c]==0){
				memset(ch[cnt],0,sizeof ch[cnt]);
				ch[root][c]=cnt;
				val[cnt]=INF;
				cnt++;
			}root=ch[root][c];
			dep[root]=i+1;	
		}
		val[root]=min(val[root],pos);
	}
	void build()
	{
		int root=0;
		queue<int> que;
		for(int i=0;i<30;i++){
			if(ch[root][i]){
				que.push(ch[root][i]);
				fail[ch[root][i]]=root;
			}
		}
		while(!que.empty()){
			int u=que.front();que.pop();
			for(int i=0;i<30;i++){
				if(ch[u][i]){
					que.push(ch[u][i]);
					fail[ch[u][i]]=ch[fail[u]][i];	
				}else {
					ch[u][i]=ch[fail[u]][i];
				}
			}
		}
	}
	void query(char *txt)
	{
		int root=0;
		for(int i=1;i<=strlen(txt+1);i++){
		int u=ch[root][idx((txt[i]))];
		for(int j=u;j;j=fail[j]){
			if(val[j]!=INF&&i-dep[j]>=0&&dp[i-dep[j]]!=INF){
				dp[i]=min(dp[i],dp[i-dep[j]]+val[j]);
			} 
		}
		root=ch[root][idx(txt[i])];
	}	
	}
}ac;
char str[500005];
char txt[500005]; 
int main()
{
	int n;
	cin>>n;
	ac.init();
	for(int i=1;i<=n;i++){int x;
		
		scanf("%s",str);scanf(" %d",&x);
		ac.insert(str,x);
	}
	
	ac.build();
	scanf("%s",txt+1);
	int root=0;
	
	for(int i=1;i<=strlen(txt+1);i++)
	dp[i]=1ll*INF*INF;
	dp[0]=0;
	ac.query(txt); 
	if(dp[strlen(txt+1)]!=1LL*INF*INF){
		cout<<dp[strlen(txt+1)];
	}
	else cout<<-1<<endl;
}
```

