Chamber of Secrets

题目用的是01BFS，一般用在棋盘问题，主要是，当权值为0的时候加在队列前面其余在队列后面，可以减少时间复杂度。

这题坑点蛮多，可能是我自己瞎搞出来的坑点。。

为零做一个入列，为1做一个入列。

注意，为1的时候并没有移动，所有还是原来位置，但是方向变了，为0的时候，位置变了但是方向没变。

```C++
#include<bits/stdc++.h>

using namespace std;
struct node
{
	int x,y,dir,step;
};

int dis[1005][1005][5];
bool vis[1005][1005][5];
char ch[1005][1005];
int nx[4]={0,1,0,-1};
int ny[4]={1,0,-1,0};
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		getchar();
		for(int j=1;j<=m;j++){
			scanf("%c",&ch[i][j]);
		}
	}
	deque<node> que;
	memset(dis,0x3f,sizeof dis);
	que.push_front({n,m,2,0});
	dis[n][m][2]=0;
	while(!que.empty())
	{
		node u=que.front();que.pop_front();
		int dx=u.x+nx[u.dir];
		int dy=u.y+ny[u.dir];
		
		if(vis[u.x][u.y][u.dir])continue;
		vis[u.x][u.y][u.dir]=1;
		if(ch[u.x][u.y]=='#'){
			for(int i=0;i<4;i++){
				if(i!=u.dir){
					if(dis[u.x][u.y][i]>u.step+1)
					{
					dis[u.x][u.y][i]=min(dis[u.x][u.y][i],u.step+1);
					que.push_back({u.x,u.y,i,u.step+1});	
					}
				}
			}
		}
		if(dx<1||dy<1||dx>n||dy>m)continue;
		
		if(dis[dx][dy][u.dir]>u.step)
		{
		dis[dx][dy][u.dir]=min(dis[dx][dy][u.dir],u.step);
		que.push_front({dx,dy,u.dir,u.step});	
		}		
		
	}
	if(dis[1][1][2]!=0x3f3f3f3f)
	cout<<dis[1][1][2]<<endl;
	else cout<<-1<<endl;
}
```



