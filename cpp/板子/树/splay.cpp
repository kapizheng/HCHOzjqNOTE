#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;
int son[maxn][2],sz[maxn],num[maxn];
int fa[maxn],val[maxn];

bool get(int x){return x==son[fa[x]][1];}
void maintain(int x){sz[x]=sz[son[x][0]]+sz[son[x][1]]+num[x];}
void clear(int x){son[x][0]=son[x][1]=fa[x]=sz[x]=num[x]=val[x]=0;}

void rotate(int x)
{
    int y=fa[x];
    int z=fa[y];
    int d=get(x);
    son[y][d]=son[x][d^1],fa[son[x][d^1]]=y;
    son[x][d^1]=y,fa[y]=x;
    fa[x]=z;
    if(z)son[z][son[z][1]==y]=x;
    maintain(x);
    maintain(y);
    return ;
}
int rt;
void splay(int cur)
{
    for(int f=fa[cur];f=fa[cur],f;rotate(cur)){
        if(fa[f]){rotate(get(cur)==get(f)?f:cur);}
    }
    rt=cur;
}
int tot;
void ins(int x)
{
    if(!rt){
        rt=++tot;
        sz[tot]=1;
        num[tot]=1;
        val[tot]=x;
        maintain(tot);
        return ;
    }
    int cur=rt;
    int f=0;
    while(1){
        if(val[cur]==x){
            num[cur]++;
            maintain(cur);
            maintain(f);
            splay(cur);
            break;
        }
        f=cur;
        cur=son[cur][val[cur]<x];
        if(!cur)
        {
            cur=++tot;
            val[tot]=x;
            fa[tot]=f;
            num[tot]=1;
            son[f][val[f]<x]=tot;
            maintain(tot);
            maintain(f);
            splay(tot);
            break;
        }

    }
}
int pre()
{
    int cnr=son[rt][0];
    while(son[cnr][1])cnr=son[cnr][1];
    splay(cnr);
    return cnr;
}
int suf()
{
    int cnr=son[rt][1];
    while(son[cnr][0])cnr=son[cnr][0];
    splay(cnr);
    return cnr;
}

int Rank(int x)//查找他的排名
{
    int cur=rt;
    int res=0;
    while(1){
        if(x<val[cur]){
            cur=son[cur][0];
        }else {
            res+=sz[son[cur][0]];
            if(x==val[cur]){
                splay(cur);
                return res+1;
            }
            res+=num[cur];
            cur=son[cur][1];
        }
    }

}

int find(int x)//查找排名为x的数字
{
    int cur=rt;
    while(1){
        if(son[cur][0]&&x<=sz[son[cur][0]]){
            cur=son[cur][0];
        }else {
            x-=sz[son[cur][0]]+num[cur];
            if(x<=0){
                splay(cur);
                return val[cur];
            }
            cur=son[cur][1];
        }
    }
}


void del(int x)
{
    Rank(x);
    if(num[rt]>1){
        num[rt]--;
        maintain(rt);
        return ;
    }
    if(!son[rt][0]&&!son[rt][1]){
        clear(rt);
        rt=0;
        return ;
    }
    if(!son[rt][0]){
        int cnr=rt;
        rt=son[rt][1];
        fa[rt]=0;
        clear(cnr);
        return ;
    }
    if(!son[rt][1]){
        int cnr=rt;
        rt=son[rt][0];
        fa[rt]=0;
        clear(cnr);
        return ;
    }
    int cnr=rt,now=pre();
    splay(now);
    fa[son[cnr][1]]=now;
    son[now][1]=son[cnr][1];
    clear(cnr);
    maintain(rt);
}

int main()
{
    int n;
    cin>>n;
    
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        if(a==1){
            ins(b);
        }else if(a==2){
            del(b);
        }else if(a==3){
            cout<<Rank(b)<<endl;
        }else if(a==4){
            cout<<find(b)<<endl;
        }else if(a==5){
            ins(b);cout<<val[pre()]<<endl;
            del(b);
        }else if(a==6){
            ins(b);cout<<val[suf()]<<endl;
            del(b);
        }
    }
}