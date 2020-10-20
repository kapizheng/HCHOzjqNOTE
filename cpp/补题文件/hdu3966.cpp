#include<bits/stdc++.h>

using namespace std;

const int maxn=1e5+10;
struct node
{
    int l,r;long long sum;
    int L,R;
    long long lazy;
}no[maxn*30];
int a[maxn];
void push_up(int v)
{
    no[v].sum=no[no[v].L].sum+no[no[v].R].sum;
}
int t;
void build(int &v,int l,int r)
{
    v=++t;
    no[v].l=l,no[v].r=r;
    no[v].lazy=no[v].sum=0;
    if(l==r){
        no[v].sum=a[l];
        return ;
    }
    int m=(l+r)>>1;

    build(no[v].L,l,m);build(no[v].R,m+1,r);
    push_up(v);
}


void update(int &v,int pre,int l,int r,int val){
    v=++t;no[v]=no[pre];
    // cout<<l<<" "<<r<<endl;
    int L=no[v].l,R=no[v].r;
    no[v].sum=(min(r,R)-max(L,l)+1)*val;
    if(L==l&&R==r){
        no[v].lazy+=val;return ;
    }
    int m=(L+R)>>1;
    if(r<=m)update(no[v].L,no[pre].L,l,r,val);
    else if(m<l)update(no[v].R,no[pre].R,l,r,val);
    else {
        update(no[v].L,no[pre].L,l,m,val);
        update(no[v].R,no[pre].R,m+1,r,val);
    }
}
long long ans=0;
void query(int v,int l,int r){
    int L=no[v].l,R=no[v].r;
    ans+=(min(R,r)-max(L,l)+1)*no[v].lazy;
    if(L==l&&R==r){
        ans+=no[v].sum;return ;
    }
    int m=(L+R)>>1;
    if(r<=m)query(no[v].L,l,r);
    else if(m<l)query(no[v].R,l,r);
    else {
        query(no[v].L,l,m);
        query(no[v].R,m+1,r);
    }
}
int T[maxn];char ch[3];

int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        t=0;
        build(T[0],1,n);
        int now=0;
        for(int i=1;i<=m;i++){
            int a,b,c;
            scanf("%s",ch);
            if(ch[0]=='C'){
                scanf("%d%d%d",&a,&b,&c);
                now++;
                update(T[now],T[now-1],a,b,c);
            }else if(ch[0]=='Q'){
                ans=0;
                scanf("%d%d",&a,&b);
                query(T[now],a,b);
                printf("%lld\n",ans);
            }else if(ch[0]=='H'){
                ans=0;
                scanf("%d%d%d",&a,&b,&c);
                query(T[c],a,b);
                printf("%lld\n",ans);
            }else if(ch[0]=='B'){
                scanf("%d",&a);
                ans=0;
                now=a;
            }
        }
        puts("");
        // cout<<"OK"<<endl;
    }
    
}