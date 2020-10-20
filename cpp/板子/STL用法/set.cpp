#include<bits/stdc++.h>

using namespace std;
const long long maxn=2e5+10;
struct edge
{
    long long u,v,w,nxt;
}e[maxn];

long long cnt=0;
long long head[maxn];
void add_edge(long long u,long long v,long long w)
{
    e[cnt].v=v;
    e[cnt].u=u;
    e[cnt].w=w;
    e[cnt].nxt=head[u];
    head[u]=cnt++;
}
long long fa[maxn],d[maxn],sz[maxn];
long long son[maxn];
long long dis[maxn];
void dfs1(long long u,long long f)
{
    fa[u]=f;
    d[u]=d[f]+1;
    sz[u]=1;
    for(long long i=head[u];~i;i=e[i].nxt){
        long long v=e[i].v;
        if(v==f)continue;

        dis[v]=dis[u]+e[i].w;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v])son[u]=v;
    }
}
long long rnk[maxn],dfn[maxn];
long long top[maxn];
long long s[maxn];
long long TOP,tim;
void dfs2(long long u,long long f)
{
    if(son[u]){
        dfn[son[u]]=++tim;
        rnk[tim]=son[u];
        top[son[u]]=top[u];
        dfs2(son[u],u);
    }
    for(long long i=head[u];~i;i=e[i].nxt){
        long long v=e[i].v;if(v==f)continue;
        if(v==son[u])continue;
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
    if(d[a]>d[b])return b;
    else return a;
}
long long vis[maxn];
long long DIS(long long a,long long b){
    long long lca=LCA(a,b);
    return dis[a]+dis[b]-2*dis[lca];
}
int main()
{
    long long n,m;
    scanf("%lld%lld",&n,&m);
    memset(head,-1,sizeof head);
    for(long long i=1;i<=n-1;i++){
        long long a,b,c;
        scanf("%lld%lld%lld",&a,&b,&c);
        add_edge(a,b,c);
        add_edge(b,a,c);
    }
    dfs1(1,0);
    rnk[1]=dfn[1]=top[1]=1;tim=1;
    dfs2(1,0);
    set<long long> st;
    long long ans=0;
    for(long long i=1;i<=m;i++){
        long long x;
        scanf("%lld",&x);
        x=dfn[x];
        if(vis[rnk[x]]==0){
            st.insert(x);
        }
        auto it=st.begin();
        long long y=rnk[(it=st.lower_bound(x))==st.begin()?*--st.end():*--it];//找到大于等于的
        long long z=rnk[(it=st.upper_bound(x))==st.end()?*st.begin():*it];//找到大于的
        
        if(vis[rnk[x]])st.erase(x);
        x=rnk[x];
        long long D=DIS(y,z)-DIS(x,y)-DIS(x,z);
        if(vis[x]){
            vis[x]=0;
            ans+=D;
        }else {
            vis[x]=1;
            ans-=D;
        }
        cout<<ans<<endl;
    }

}