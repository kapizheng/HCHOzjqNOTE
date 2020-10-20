#include<iostream>
#include<cstring>
#include<cstdio>
#include <algorithm>

using namespace std;
const int maxn=200010;
struct node
{
    int l,r;
    int lazy;
    long long  maxv,minv;
}no[maxn*4];

int sz[maxn];
int top[maxn];
int fa[maxn];
int son[maxn];
int d[maxn];
int head[maxn];
struct edge
{
    int u,v,nxt;

}e[maxn*2];
long long val[maxn];
void dfs(int u,int f)
{
    d[u]=d[f]+1;
    sz[u]=1;
    fa[u]=f;
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;if(v==f)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn];
int tim;
void dfs1(int u,int f)
{
    if(son[u]){
        dfn[son[u]]=++tim;
        rnk[tim]=son[u];
        top[son[u]]=top[u];
        dfs1(son[u],u);
    }
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(v==f)continue;
        if(son[u]==v)continue;
        dfn[v]=++tim;rnk[tim]=v;top[v]=v;
        dfs1(v,u);
    }
}

void push_up(int v){
    no[v].maxv=max(no[v<<1].maxv,no[v<<1|1].maxv);
    no[v].minv=min(no[v<<1].minv,no[v<<1|1].minv);
}

void push_down(int v)
{
    if(no[v].lazy){
        no[v<<1].lazy=1-no[v<<1].lazy;
        no[v<<1|1].lazy=1-no[v<<1|1].lazy;
        swap(no[v<<1].maxv,no[v<<1].minv);
        no[v<<1].maxv=-no[v<<1].maxv;
        no[v<<1].minv=-no[v<<1].minv;
        swap(no[v<<1|1].maxv,no[v<<1|1].minv);
        no[v<<1|1].maxv=-no[v<<1|1].maxv;
        no[v<<1|1].minv=-no[v<<1|1].minv;
        no[v].lazy=0;
    }
}
void build(int v,int l,int r)
{
    no[v].l=l,no[v].r=r;
    no[v].lazy=0;
    if(l==r){
        no[v].minv=no[v].maxv=val[rnk[l]];
        return ;
    }
    int m=(l+r)>>1;
    build(v<<1,l,m);build(v<<1|1,m+1,r);
    push_up(v);
}
void update(int v,int pos,long long val)
{
    int ll=no[v].l,rr=no[v].r;
    if(ll==rr&&pos==ll){
        no[v].maxv=no[v].minv=val;
        return ;
    }
    push_down(v);
    int m=(ll+rr)>>1;
    if(pos<=m)update(v<<1,pos,val);
    else update(v<<1|1,pos,val);
    push_up(v);
}
void update2(int v,int l,int r)
{
    // if(v<1000000)
    // cout<<v<<" "<<l<<" "<<r<<endl;
    int ll=no[v].l,rr=no[v].r;
    if(ll==l&&r==rr){
        swap(no[v].maxv,no[v].minv);
        no[v].maxv=-no[v].maxv;
        no[v].minv=-no[v].minv;
        no[v].lazy=1-no[v].lazy;
        return ;
    }
    push_down(v);
    int m=(ll+rr)>>1;
    if(r<=m)update2(v<<1,l,r);
    else if(l>m) update2(v<<1|1,l,r);
    else update2(v<<1,l,m),update2(v<<1|1,m+1,r);
    push_up(v);
    return ;
}
long long maxv,sum;
void query(int v,int l,int r)
{
    int ll=no[v].l,rr=no[v].r;
    if(ll==l&&r==rr){
        maxv=max(no[v].maxv,maxv);
        return ;
    }
    push_down(v);
    int m=(ll+rr)>>1;
    if(r<=m)query(v<<1,l,r);
    else if(l>m) query(v<<1|1,l,r);
    else query(v<<1,l,m),query(v<<1|1,m+1,r);
    push_up(v);
    return ;
}

int cnt=0;
void add_edge(int u,int v)
{
    e[cnt].v=v;e[cnt].nxt=head[u];
    head[u]=cnt++;
}

void ask(int x,int y)
{
    int tx=top[x],ty=top[y];
    while(tx!=ty){
        if(d[tx]<d[ty])swap(tx,ty),swap(x,y);
        
        query(1,dfn[tx],dfn[x]);
        x=fa[tx],tx=top[x];
    }
    if(d[x]>d[y])swap(x,y);
    if(x!=y)
    query(1,dfn[son[x]],dfn[y]);
    return ;
}
void upd(int x,int y)
{
    int tx=top[x],ty=top[y];
    while(tx!=ty){
        if(d[tx]<d[ty])swap(tx,ty),swap(x,y);
        update2(1,dfn[tx],dfn[x]);
        x=fa[tx],tx=top[x];
    }
    if(d[x]>d[y])swap(x,y);
    if(x!=y)
    update2(1,dfn[son[x]],dfn[y]);
    
    return ;
}



int lca(int a,int b)
{
    int ta=top[a],tb=top[b];
    while(ta!=tb)
    {
        if(d[ta]<d[tb])swap(a,b),swap(ta,tb);
        a=fa[ta],ta=top[a];
    }
    if(d[a]>d[b])return b;
    else return a;
}
int  a[maxn],b[maxn];
long long c[maxn];
int  main()
{
    int n,m,p,q;
    // freopen("test.in","r",stdin);
    int t;cin>>t;
    while(t--)
    {
        cnt=0;
        scanf("%d",&n);
        memset(head,-1,sizeof head);
        for(int  i=1;i<=n-1;i++){
            son[i]=0;
            scanf("%d%d%lld",&a[i],&b[i],&c[i]);
            add_edge(a[i],b[i]);
            add_edge(b[i],a[i]);
        }
        son[n]=0;
        dfs(1,0);
        rnk[1]=top[1]=dfn[1]=1;tim=1;
        dfs1(1,0);
        for(int i=1;i<=n-1;i++){
            if(d[a[i]]<d[b[i]])swap(a[i],b[i]);
            val[a[i]]=c[i];
        }
        val[1]=-1e18;
        build(1,1,tim);
        while(true){
            char ch[10];
            scanf("%s",&ch);
            if(ch[0]=='D')break;
            if(ch[0]=='Q'){
                int  x,y;scanf("%d%d",&x,&y);
                maxv=-1e18;ask(x,y);
                printf("%lld\n",maxv);
            }else if(ch[0]=='C') {
                int  x;long long y;scanf("%d%lld",&x,&y);
                update(1,dfn[a[x]],y);
            }else if(ch[0]=='N'){
                int  x;int y;scanf("%d%d",&x,&y);
                upd(x,y);
            }
        }
    }
    
    
}