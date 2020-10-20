#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<sstream>


using namespace std;
const int maxn=1000006;
struct edge
{
    int v,nxt,val;
}e[maxn];
int cnt;
int head[maxn];
void add_edge(int u,int v,int w)
{
    e[cnt].val=w;
    e[cnt].v=v;e[cnt].nxt=head[u];
    head[u]=cnt++;
}
int dp[maxn];
int sz[maxn];
int du[maxn];
void dfs(int u,int fa)
{
    dp[u]=0;
    for(int i=head[u];~i;i=e[i].nxt)
    {
        int v=e[i].v;if(v==fa)continue;
        dfs(v,u);
        if(du[v]==1)dp[u]+=e[i].val;
        else dp[u]+=min(dp[v],e[i].val);
    }
}
void dfs1(int u,int fa)
{
    for(int i=head[u];~i;i=e[i].nxt)
    {
        int v=e[i].v;if(v==fa)continue;
        if(du[u]==1)sz[v]=dp[v]+e[i].val;
        else sz[v]=min(sz[u]-e[i].val,e[i].val)+dp[v];
        dfs1(v,u);
    }
}

int main()
{
    int t;cin>>t;
    while(t--)
    {
        int n;memset(du,0,sizeof du);
        scanf("%d",&n);
        memset(head,-1,sizeof head);cnt=0;
        for(int i=1;i<=n-1;i++){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            du[a]++;du[b]++;
            add_edge(a,b,c);
            add_edge(b,a,c);
        }
        dfs(1,-1);
        for(int i=1;i<=n;i++){
            sz[i]=dp[i];
        }
        dfs1(1,-1);
        int ans=0;
        for(int i=1;i<=n;i++){
            ans=max(ans,sz[i]);
        }
        cout<<ans<<endl;
    }
}