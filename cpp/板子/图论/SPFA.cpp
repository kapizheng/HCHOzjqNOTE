#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;

int p[maxn];
int m;
int cap[202][202];
int liu[202][202];
int n;
int pre[maxn];
int head[maxn];
struct edge
{
    int u,v,nxt,w,cost;
}e[maxn];
int cnt;
void add_edge(int u,int v,int w,int c){
    e[cnt].u=u;e[cnt].v=v;e[cnt].nxt=head[u];e[cnt].w=w;e[cnt].cost=c;
    head[u]=cnt++;
}
int d[maxn];
int vis[maxn];
int idx[maxn];
int flow[maxn];
void bfs(int s,int t)
{
    queue<int>que;
    que.push(s);
    memset(pre,0,sizeof pre);
    memset(d,0x3f,sizeof d);
    memset(vis,0,sizeof vis);
    flow[s]=0x3f3f3f3f;
    d[s]=0;
    vis[s]=1;
    while(!que.empty()){
        // cout<<"EM"<<endl;
        int u=que.front();que.pop();
        vis[u]=0;
        for(int i=head[u];~i;i=e[i].nxt){
            int v=e[i].v;
            if(e[i].w>0&&d[v]>d[u]+e[i].cost){
                d[v]=d[u]+e[i].cost;
                flow[v]=min(flow[u],e[i].w);
                pre[v]=u;
                idx[v]=i;
                if(vis[v]==0){
                    que.push(v);vis[v]=1;
                }
            }
        }
    }
}

int find(int s,int t)
{
    int now=flow[t];
    while(pre[t]){
        e[idx[t]].w-=now;
        e[idx[t]^1].w+=now;
        t=pre[t];
    }
    return now;
}

void EK(int s,int t)
{
    long long ans=0;
    int ans1=0,ans2=0;
    int z=0;
    while(1){
        bfs(s,t);
        if(d[t]==0x3f3f3f3f)break;
        int now=find(s,t);
        ans1+=now;
        ans2+=now*d[t];
    }
    cout<<ans1<<" "<<ans2<<endl;
}


int main()
{
    int s,t;
    cin>>m>>n>>s>>t;
    memset(head,-1,sizeof head);
    for(int i=1;i<=n;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        add_edge(a,b,c,d);
        add_edge(b,a,0,-d);
    }
    EK(s,t);
}