//P4001洛谷
#include<bits/stdc++.h>

using namespace std;
const int maxn=250+10;
struct edge
{
    int v,w,nxt;
}e[maxn<<1];

int cnt;
int head[maxn];
void add(int u,int v,int w){
    e[cnt].v=v;e[cnt].w=w;e[cnt].nxt=head[u];head[u]=cnt++;

    e[cnt].v=u;e[cnt].w=w;e[cnt].nxt=head[v];head[v]=cnt++;
}
int d[maxn];
int vis[maxn];
int n,m;
void dij(int s,int t){
    priority_queue<pair<int,int> > que;
    que.push({0,s});
    memset(d,0x3f,sizeof d);
    d[s]=0;
    memset(vis,0,sizeof vis);

    while(!que.empty()){
        pair<int,int> pii=que.top();que.pop();
        if(vis[pii.second])continue;
        vis[pii.second]=1;
        for(int i=head[pii.second];~i;i=e[i].nxt){
            int v=e[i].v;
            if(d[v]>max(d[pii.second],e[i].w)){
                d[v]=max(d[pii.second],e[i].w);
                if(vis[v]==0)
                que.push({-d[v],v});
            }
        }
    }
    cout<<d[t]<<endl;
}


int get(int x,int y){
    return (x-1)*(m-1)+y;
}
int s,t;
pair<int,int> heng(int x,int y)
{
    if(x==1)return {get(x,y)*2,t};
    if(x==n)return {get(x-1,y)*2-1,s};
    return {get(x-1,y)*2-1,get(x,y)*2};
}
pair<int,int> shu(int x,int y){
    if(y==1)return {get(x,y)*2-1,s};
    if(y==m)return {get(x,y-1)*2,t};
    return {get(x,y-1)*2,get(x,y)*2-1};
}
pair<int,int> xie(int x,int y){
    return {get(x,y)*2-1,get(x,y)*2};
}

int main()
{
    int m;
    while(cin>>n>>m)
    {
        memset(head,-1,sizeof head);
        cnt=0;
        for(int i=1;i<=m;i++){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
        }
        dij(1,m);
    }
    
}