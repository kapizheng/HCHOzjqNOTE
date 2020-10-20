#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1
const int MAX=50009;
struct Edge{
    int next,to;
}edge[MAX*2];
int head[MAX],cnt=0;
int fa[MAX],deep[MAX],son[MAX],size[MAX],top[MAX],id[MAX],rk[MAX],tot;
int n,m,p,a[MAX],u,v;
char op[2];
int sum[MAX<<2],lazy[MAX<<2];
inline void add(int u,int v)
{
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void dfs1(int u,int f,int d)
{
    deep[u]=d;
    fa[u]=f;
    size[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v!=fa[u])
        {
            dfs1(v,u,d+1);
            size[u]+=size[v];
            if(son[u]==-1||size[son[u]]<size[v])
                son[u]=v;
        }
    }
}
void dfstop(int u,int t)
{
    top[u]=t;
    id[u]=tot++;
    rk[id[u]]=u;
    
    if(son[u]==-1)return;
    dfstop(son[u],t);
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v!=son[u]&&v!=fa[u])
            dfstop(v,v);
    }
}

void PushUp(int rt)            //维护区间和 
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void Build(int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=a[rk[l]];
        return;
    }
    int m=l+r>>1;
    Build(ls);
    Build(rs);
    PushUp(rt);
}
void PushDown(int ln,int rn,int rt)    //lazy标记下传    
{
    if(lazy[rt])
    {
        lazy[rt<<1]+=lazy[rt];
        lazy[rt<<1|1]+=lazy[rt];
        sum[rt<<1]+=lazy[rt]*ln;
        sum[rt<<1|1]+=lazy[rt]*rn;
        lazy[rt]=0;
    }
}
void Update(int L,int R,int val,int l,int r,int rt)//区间更新 
{
    if(L<=l&&r<=R)
    {
        sum[rt]+=(r-l+1)*val;
        lazy[rt]+=val;
        return;
    }
    int m=l+r>>1;
    PushDown(m-l+1,r-m,rt);
    if(L<=m)Update(L,R,val,ls);
    if(R>m)Update(L,R,val,rs);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
        return sum[rt];
    int m=l+r>>1;
    int ans=0;
    PushDown(m-l+1,r-m,rt);
    if(L<=m)ans+=Query(L,R,ls);
    if(R>m)ans+=Query(L,R,rs);
    return ans;
}
void change(int x,int y,int v)        //更新x->y路径的权值 
{
    while(top[x]!=top[y])
    {
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        Update(id[top[x]],id[x],v,1,tot,1);
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    Update(id[x],id[y],v,1,tot,1);
}
void init()
{
    cnt=0;
    memset(head,-1,sizeof(head));
    tot=1;
    memset(son,-1,sizeof(son));
    memset(sum,0,sizeof(sum));
    memset(lazy,0,sizeof(lazy));
    memset(deep,0,sizeof(deep));
}
int main()
{ 
    freopen("in.txt","r",stdin);

    while(~scanf("%d%d%d",&n,&m,&p))
    {
        init(); 
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        while(m--)
        {
            scanf("%d%d",&u,&v);
            add(u,v);add(v,u);
        }
        dfs1(1,0,0);dfstop(1,1);
        Build(1,tot,1);
        while(p--)
        {
            int c1,c2,k;
            scanf("%s",op);
            if(op[0]=='I')
            {
                scanf("%d%d%d",&c1,&c2,&k);
                change(c1,c2,k);
            }
            if(op[0]=='D')
            {
                scanf("%d%d%d",&c1,&c2,&k);
                change(c1,c2,-k);
            }
            if(op[0]=='Q')
            {
                scanf("%d",&c1);
                printf("%d\n",Query(id[c1],id[c1],1,tot,1));
            } 
        }
    }
    return 0; 
}