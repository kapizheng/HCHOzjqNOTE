 
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,m,w[N],b[N];
struct edge
{
    int to,next;
} vec[N<<1];
int head[N],tot;
 
///主席树
int root[N] ,chairtree,rnu;
struct node
{
    int lc,rc,sum;
} ctree[N*20];
void build(int &i,int l,int r)
{
    ctree[++chairtree]=ctree[i];
    i=chairtree;
    ctree[i].sum=0;
    if(l>=r)return ;
    int m =((r-l)>>1)+l;
    build(ctree[i].lc,l,m);
    build(ctree[i].rc,m+1,r);
}
 
void update(int& i,int l,int r,int pos)
{
    ctree[++chairtree]=ctree[i];
    i=chairtree;
    ctree[i].sum++;
    if(l>=r) return ;
    int m=((r-l)>>1)+l;
    if(pos<=m)
        update(ctree[i].lc,l,m,pos);
    else
        update(ctree[i].rc,m+1,r,pos);
}
 
int query(int i,int l,int r,int j,int lca,int flca,int k)
{
    if(l>=r) return l;
    int m=((r-l)>>1)+l;
    int cnt=ctree[ctree[i].lc].sum+ctree[ctree[j].lc].sum-ctree[ctree[lca].lc].sum-ctree[ctree[flca].lc].sum;
    if(k<=cnt)
        query(ctree[i].lc,l,m,ctree[j].lc,ctree[lca].lc,ctree[flca].lc,k);
    else
        query(ctree[i].rc,m+1,r,ctree[j].rc,ctree[lca].rc,ctree[flca].rc,k-cnt);
}
 
///树链剖分
void add(int u,int v)
{
    vec[++tot].to=v,vec[tot].next=head[u],head[u]=tot;
    vec[++tot].to=u,vec[tot].next=head[v],head[v]=tot;
}
 
 
int dep[N],fa[N],siz[N],son[N];
void dfs1(int u,int f,int d)
{
    dep[u]=d;
    fa[u]=f;
    siz[u]=1;
    son[u]=0;
    for(int i=head[u];i;i=vec[i].next)
    {
        int v=vec[i].to;
        if(v==f) continue;
        dfs1(v,u,d+1);
        siz[u]+=siz[v];
        if(siz[son[u]]<siz[v])
            son[u]=v;
    }
}
 
int tree[N],top[N] ,cnt;
void dfs2(int u,int tp)
{
    top[u]=tp,tree[u]=++cnt;//cnt是当前树的编号  而chairtree是当前树上  主席树的部分
    update(root[u]=root[fa[u]],1,rnu,w[u]);
    if(!son[u])
        return ;
    for(int i=head[u];i;i=vec[i].next)
    {
        int v=vec[i].to;
        if(v==fa[u]||v==son[u])
            continue;
        dfs2(v,v);
    }
}
 
int Lca(int x,int y)
{
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]<dep[fy])
            swap(x,y),swap(fx,fy);
        x=fa[fx],fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}
 
int main()
{
	freopen("test.in","r",stdin);
	freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&w[i]);
        b[i]=w[i];
    }
    for(int i=1; i< n; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v );
        add(u,v);
    }
    fa[1]=0;
    sort(b+1,b+n+1);
    rnu = unique(b+1,b+n+1)-(b+1);
    for(int i=1; i<=n; i++)
        w[i]=lower_bound(b+1,b+rnu+1,w[i])-b;
    build(root[0],1,rnu);
    dfs1(1,0,1);
    dfs2(1,1);
    while(m--)
    {
        int u,v,k;
        scanf("%d%d%d",&u,&v,&k);
        int lca=Lca(u,v);
		// cout<<lca<<endl;
        printf("%d\n",(b[query(root[u],1,rnu,root[v],root[lca],root[fa[lca]],k)]));
    }
    return 0;
}