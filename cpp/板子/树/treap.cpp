#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;
int son[maxn][2];
int sz[maxn];
int d[maxn];
int val[maxn];
int tot;
int num[maxn];

void pushup(int p)
{
    sz[p]=sz[son[p][0]]+sz[son[p][1]]+num[p];
}
int rd[maxn];
void rotate(int &p,int d)
{
    int k=son[p][d^1];
    son[p][d^1]=son[k][d];
    son[k][d]=p;
    pushup(p);
    pushup(k);
    p=k;
}
void ins(int &p,int x)
{
    if(!p){
        p=++tot;
        val[p]=x;
        sz[p]=1;
        num[p]=1;
        rd[p]=rand();
        return ;
    }
    if(val[p]==x){
        sz[p]++;
        num[p]++;
        return ;
    }
    int d=(x>val[p]);
    ins(son[p][d],x);
    if(rd[p]<rd[son[p][d]])
        rotate(p,d^1);
    pushup(p);
}


void del(int &p,int x)
{
    if(!p)return ;
    if(val[p]<x){
        del(son[p][1],x);
    }else if(val[p]>x){
        del(son[p][0],x);
    }else {
        if(!son[p][0]&&!son[p][1]){
            sz[p]--;
            num[p]--;
            if(num[p]==0)p=0;
        }else if(!son[p][0]&&son[p][1]){
            rotate(p,0);
            del(son[p][0],x);
        }else if(!son[p][1]&&son[p][0]){
            rotate(p,1);
            del(son[p][1],x);
        }else {
            int d=(rd[son[p][1]]<rd[son[p][0]]);
            rotate(p,d);
            del(son[p][d],x);
        }
    }
    pushup(p);
}
int Rank(int p,int x)
{
    if(!p)return 0;
    if(val[p]==x)return sz[son[p][0]]+1;
    else if(val[p]>x){
        return Rank(son[p][0],x);
    }else if(val[p]<x){
        return Rank(son[p][1],x)+sz[son[p][0]]+num[p];
    }
}
int find(int p,int x)
{
    if(!p)return 0;
    if(sz[son[p][0]]>=x)return find(son[p][0],x);
    if(sz[son[p][0]]+num[p]<x)return find(son[p][1],x-sz[son[p][0]]-num[p]);
    return val[p];
}
const int inf=1e9;

int pre(int p,int x)//找小于他的最大值
{
    if(!p)return -inf;
    if(x<=val[p])return pre(son[p][0],x);
    return max(val[p],pre(son[p][1],x));
}

int suf(int p,int x)//找大于他的最小值
{
    if(!p)return inf;
    if(x>=val[p])return suf(son[p][1],x);
    return min(val[p],suf(son[p][0],x));
}

int main()
{
    int t;
    cin>>t;
    int rt=0;
    srand(unsigned(time(0)));
    tot=0;
    while(t--){
        int a,b;
        cin>>a>>b;
        if(a==1){
            ins(rt,b);
        }else if(a==2){
            del(rt,b);
        }else if(a==3){
            cout<<Rank(rt,b)<<endl;
        }else if(a==4){
            cout<<find(rt,b)<<endl;
        }else if(a==5){
            cout<<pre(rt,b)<<endl;
        }else {
            cout<<suf(rt,b)<<endl;
        }
    }
}