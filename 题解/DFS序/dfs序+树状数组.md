```C++
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

#define mem(a) memset(a,0,sizeof(a))
const int maxn=100005;
int ll[maxn],rr[maxn],apple[maxn];
int sum[maxn];
vector<vector<int> > g(maxn);
int n;
void init()
{
	mem(ll);mem(rr);
	mem(apple);mem(sum);
	for(int i=0;i<maxn;i++)g[i].clear();
}

int lowbit(int x){
	return x&(x^(x-1));
}

void update(int pos,int val)
{
	while(pos<=n)
	{
		sum[pos]+=val; 
		pos+=lowbit(pos);
	}
}

int all(int pos)
{
	int ans=0;
	while(pos>0)
	{ 
		ans+=sum[pos];
		pos-=lowbit(pos);
	}
	return ans;
}
int tim;
void dfs(int u)
{
	ll[u]=tim;
	for(int i=0;i<g[u].size();i++){
		tim+=1;
		dfs(g[u][i]);
	}
	rr[u]=tim;
	return ; 
}
int main()
{
	while(~scanf("%d",&n))
	{
		init();
		
		for(int i=0;i<n-1;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			g[a].push_back(b);
		}
		tim=1;
		dfs(1);	
		for(int i=1;i<=n;i++){
			apple[i]=1;
			update(i,1);
		}
		int t;
		scanf("%d",&t);
		
		while(t--)
		{
			char ch;int x;getchar();
			scanf("%c %d",&ch,&x);
			
			if(ch=='Q'){
				printf("%d\n",all(rr[x])-all(ll[x]-1));
			}else {
				if(apple[x]){
					update(ll[x],-1);
				}else {
					update(ll[x],1);
				}
				apple[x]=1-apple[x];
			}
		}	
	}
	
}
```

Q查询该结点有多少个苹果

C对该节点进行操作

dfs的作用是把树的结点的区间给标记出来。