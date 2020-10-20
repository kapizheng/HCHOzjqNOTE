#include <bits/stdc++.h>

using namespace std;
const int maxn=1e5+5;
struct edge
{
    int v,nxt,val;
}e[maxn];
int cnt;
int head[maxn];
void add_edge(int u,int v)
{
    e[cnt].v=v;e[cnt].nxt=head[u];
    head[u]=cnt++;
}
int dis[maxn];

int Long;
int pre[maxn];
void dfs(int u,int fa)
{
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(v!=fa){
            pre[v]=u;
            dis[v]=dis[u]+1;
            if(dis[v]>dis[Long])Long=v;
            dfs(v,u);
        }
    }
}
int dis2[maxn];
int vis[maxn];
pair<int,int> tu[maxn];
void dfs2(int u,int fa,int Len,int aim)
{
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(fa!=v){
            if(!vis[v]){
                if(Len+1>tu[v].first)
                tu[v]={Len+1,aim};
            }
            dfs2(v,u,Len+1,aim);
        }
    }
}
struct node
{
    int a,b;
};
vector<node> ans;
long long ansl=0; 
void DFS(int u,int fa)
{
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(fa!=v){
            if(vis[v]==0){
                ans.push_back({v,tu[v].second});
                ansl+=tu[v].first;DFS(v,u);
            }
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    memset(head,-1,sizeof head);
    for(int i=1;i<=n-1;i++){
        int a,b;scanf("%d%d",&a,&b);
        add_edge(a,b);
        add_edge(b,a);
    }
    dfs(1,-1);
    dis[Long]=0;
    int A=Long;
    memset(pre,0,sizeof pre);
    dfs(Long,-1);
    //求直径
    vector<int> link;
    for(int i=Long;i;i=pre[i]){
        vis[i]=1,link.push_back(i);
    }//求出那条链

    int B=Long;
    dfs2(A,-1,0,A);//求到a的线
    dfs2(B,-1,0,B);//搞出所有线段


    for(int i=0;i<link.size();i++){
        DFS(link[i],-1);
    }

    for(int i=0;i<link.size();i++){
        if(link[i]!=A)ans.push_back({link[i],A});ansl+=dis[link[i]];
    }
    cout<<ansl<<endl;
    for(int i=0;i<ans.size();i++){
        printf("%d %d %d\n",ans[i].a,ans[i].b,ans[i].a);
    }
}