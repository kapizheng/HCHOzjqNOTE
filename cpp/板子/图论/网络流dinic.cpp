#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;

const int N=200006;
const int maxn=200006;
int cost[N];
int head[maxn];
struct edge
{
    int v,nxt,w;
}e[N];
int cnt;
void add_edge(int u,int v,int w){
    e[cnt].v=v;e[cnt].nxt=head[u];e[cnt].w=w;
    head[u]=cnt++;
}
int d[maxn];

int bfs(int s,int t)
{
    queue<int> que;
    memset(d,0,sizeof d);que.push(s);
    d[s]=1;
    while(!que.empty()){
        int u=que.front();que.pop();
        for(int i=head[u];~i;i=e[i].nxt){
            int v=e[i].v;
            if(!d[v]&&e[i].w>0){
                que.push(v);
                d[v]=d[u]+1;
            }
        }
    }
    if(d[t]==0)return 0;
    else return 1;
}

int dfs(int u,int t,int limit)
{
    if(u==t||!limit)return limit;
    int f;
    int flow=0;
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(d[v]==d[u]+1&&(f=dfs(v,t,min(e[i].w,limit)))>0){
            flow+=f;
            limit-=f;
            e[i].w-=f;
            e[i^1].w+=f;
            if(limit==0)break;
        }
    }
    return flow;
}


void dinic(int s,int t)
{
    int ans=0;
    while(bfs(s,t)){
        ans+=dfs(s,t,0x3f3f3f3f);
    }
    cout<<ans<<endl;
}


int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int a,b,c;cnt=0;
        memset(head,-1,sizeof head);
        for(int i=0;i<n;i++){
            
            scanf("%d%d%d",&a,&b,&c);
            add_edge(a,b,c);
            add_edge(b,a,0);
        }
        dinic(1,m);
        
    }
}