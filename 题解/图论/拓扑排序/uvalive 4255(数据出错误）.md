拓扑排序，用路线上的和代替前缀和。

答案只要求出数字的前后关系就可以了。

拓扑排序：找到入度为0的点，然后找到边，删掉边的入度，重复找入度0找边。

```C++
#include<bits/stdc++.h>

using namespace std;
int tu[100][100];
int du[100];
int dis[100];
int vis[100];
void toposort(int n)
{
	queue<int> que;
	
	
	for(int i=0;i<=n;i++)
	{
		if(du[i]==0){
			que.push(i);
		}
	}
	while(!que.empty())
	{
		int u=que.front();
		que.pop();
		
		for(int i=0;i<=n;i++){
			if(tu[u][i]){
				dis[i]=dis[u]+1;
				--du[i];
				if(!du[i])que.push(i);
			}
		}
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;cin>>n;
		memset(dis,0,sizeof dis);
		memset(tu,0,sizeof tu);
		memset(du,0,sizeof du);
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				char x;
				cin>>x;
				if(x=='-'){
					tu[j][i-1]=1;
					du[i-1]++;
				}else if(x=='+'){
					tu[i-1][j]=1;
					du[j]++;
				}
			}
		}
		toposort(n);
		for(int i=1;i<=n;i++){
			if(i!=1)cout<<" ";
			cout<<dis[i]-dis[i-1];
		}
		cout<<endl;
	}
}
```

