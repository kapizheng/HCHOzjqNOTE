#include<bits/stdc++.h>

const long long maxn=250010*2;
using namespace std;
struct edge
{
    long long v,nxt,w;
}e[maxn];
long long cnt;
long long head[maxn];
long long rnk[maxn],dfn[maxn],top[maxn],sz[maxn],fa[maxn];
long long son[maxn];
long long d[maxn];
long long tim;
long long mn[maxn];
vector<long long> g[maxn];
long long s[maxn];
void add(long long u,long long v,long long w)
{
    e[cnt].w=w;e[cnt].v=v;e[cnt].nxt=head[u];head[u]=cnt++;
}
void dfs1(long long u,long long f)
{
    sz[u]=1;fa[u]=f;
    d[u]=d[f]+1;
    for(long long i=head[u];~i;i=e[i].nxt){
        long long v=e[i].v;if(v==f)continue;
        mn[v]=min(mn[u],e[i].w);
        dfs1(v,u);
        sz[u]+=sz[v];

        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
}
void dfs2(long long u,long long f)
{
    if(son[u]){
        dfn[son[u]]=++tim;
        rnk[tim]=son[u];
        top[son[u]]=top[u];
        dfs2(son[u],u);
    }
    for(long long i=head[u];~i;i=e[i].nxt){
        long long v=e[i].v;if(v==f||v==son[u])continue;
        dfn[v]=++tim;
        rnk[tim]=v;
        top[v]=v;
        dfs2(v,u);
    }
}
long long LCA(long long a,long long b)
{
    long long ta=top[a],tb=top[b];
    while(ta!=tb){
        if(d[ta]<d[tb])swap(ta,tb),swap(a,b);
        a=fa[ta],ta=top[a];
    }
    if(d[a]<d[b])return a;
    else return b;
}

void add2(long long u,long long v)
{
    g[u].push_back(v);
}
long long TOP;
void ins(long long now)
{
    if(TOP==1){
        s[++TOP]=now;return ;
    }
    long long lca=LCA(s[TOP],now);
    // cout<<s[TOP]<<" "<<now<<" "<<lca<<"LCA"<<endl;
    if(lca==s[TOP]){
        return;
    }
    while(TOP>=2&&dfn[s[TOP-1]]>=dfn[lca]){
        add2(s[TOP-1],s[TOP]);//y->x
        TOP--;
    }
    if(s[TOP]!=lca)
    {
        add2(lca,s[TOP]);
        s[TOP]=lca;
    }
    s[++TOP]=now;
}

long long K[maxn];
bool cmp(const long long &a,const long long &b){
    return dfn[a]<dfn[b];
}

long long DP(long long u)
{
    if(g[u].size()==0)return mn[u];
    long long sum=0;
    for(long long i=0;i<g[u].size();i++){
        long long v=g[u][i];
        sum+=DP(v);
    }
    g[u].clear();
    return min(sum,(long long)mn[u]);
}

void getAns(long long n)
{
    TOP=1;
    s[TOP]=1;
    sort(K+1,K+1+n,cmp);
    for(long long i=1;i<=n;i++){
         ins(K[i]);
    }
    while(TOP>=1){
        add2(s[TOP-1],s[TOP]);
        TOP--;
    }
    cout<<DP(1)<<endl;
}

int main()
{
    long long n;
    scanf("%lld",&n);
    memset(head,-1,sizeof head);
    for(long long i=1;i<=n-1;i++){
        long long a,b,c;
        scanf("%lld%lld%lld",&a,&b,&c);
        add(a,b,c);
        add(b,a,c);
    }
    mn[1]=1e18;
    dfs1(1,0);
    rnk[1]=top[1]=dfn[1]=1;tim=1;
    dfs2(1,0);
    long long m;
    scanf("%lld",&m);
    for(long long i=1;i<=m;i++){
        long long x;
        scanf("%lld",&x);
        for(long long j=1;j<=x;j++){
            scanf("%lld",&K[j]);
        }
        getAns(x);
    }
}