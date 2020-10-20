#include<bits/stdc++.h>

using namespace std;
const int maxn=1e6+10;
int son[maxn][2];
int fa[maxn];
int sz[maxn];
int num[maxn];
int tag[maxn];
int val[maxn];
void push_up(int p){sz[p]=sz[son[p][0]]+sz[son[p][1]]+num[p];}
void clear(int p){sz[p]=son[p][0]=son[p][1]=num[p]=fa[p]=0;}
bool get(int p){return son[fa[p]][1]==p;}
void push_down(int p){
    if(tag[p]){
        tag[son[p][0]]^=1;
        tag[son[p][1]]^=1;
        swap(son[p][0],son[p][1]);
        tag[p]=0;
    }
}

void rotate(int x)
{
    int y=fa[x];
    int z=fa[y];
    int d=get(x);
    push_down(y);push_down(x);
    son[y][d]=son[x][d^1];
    fa[son[x][d^1]]=y;
    son[x][d^1]=y;
    fa[y]=x;

    fa[x]=z;
    if(z)son[z][son[z][1]==y]=x;
    push_up(y);
    push_up(x);
}
int rt;
void splay(int cur,int goal)
{
    for(int f;(f=fa[cur])!=goal;rotate(cur)){
        if(fa[f]!=goal){rotate(get(f)==get(cur)?f:cur);}
    }
    if(!goal)rt=cur;
}
int tot;
void ins(int x)
{
    if(!rt){
        rt=++tot;
        num[rt]++;
        val[rt]=x;
        push_up(rt);
        return ;
    }
    int cur=rt;
    int f=0;
    while(1){
        if(val[cur]==x){
            num[cur]++;
            push_up(f);
            push_up(cur);
            splay(cur,0);
            break;
        }
        f=cur;
        cur=son[cur][val[cur]<x];
        if(!cur){
            cur=++tot;
            num[tot]=1;
            val[tot]=x;
            son[f][val[f]<x]=tot;
            fa[tot]=f;
            push_up(tot);
            push_up(f);
            splay(tot,0);break;
        }
    }
}
int Rank(int x)//找到他的排名？
{
    int res=0;
    int cur=rt;
    while(1){
        if(x<val[cur]){
            cur=son[cur][0];
        }else {
            res+=sz[son[cur][0]];
            if(val[cur]==x){
                splay(cur,0);
                return res+1;
            }
            res+=num[cur];
            cur=son[cur][1];
        }
    }
}
int Kth(int x)//找到排名为x的值
{
    int cur=rt;
    
    while(1){
        push_down(cur);
        if(sz[son[cur][0]]>=x){
            cur=son[cur][0];
        }else {
            x-=sz[son[cur][0]]+num[cur];
            if(x<=0){
                splay(cur,0);
                return cur;
            }
            cur=son[cur][1];
        }
    }
}

void turn(int l,int r)
{
    r+=2;
    l=Kth(l);
    r=Kth(r);
    splay(l,0);
    splay(r,l);
    push_down(rt);
    tag[son[son[rt][1]][0]]^=1;
}
void print(int rt)
{
    push_down(rt);
    if(son[rt][0])print(son[rt][0]);
    if(val[rt]!=1e9&&val[rt]!=-1e9)printf("%d ",val[rt]);
    if(son[rt][1])print(son[rt][1]);
}

int a[1000006];
int build(int v,int l,int r)
{
    if(l>r)return 0;
    int m=(l+r)>>1;
    int V=v;
    v=++tot;
    fa[v]=V;
    val[v]=a[m];
    num[v]=1;

    son[v][0]=build(v,l,m-1);
    son[v][1]=build(v,m+1,r);
    push_up(v);
    return v;
}

int main()
{
    int n,m;
    cin>>n>>m;
    a[1]=-1e9;
    a[n+2]=1e9;
    for(int i=2;i<=n+1;i++){
        a[i]=i-1;
    }
    rt=build(rt,1,n+2);

    while(m--){
        int l,r;
        cin>>l>>r;
        turn(l,r);
    }
    print(rt);
}