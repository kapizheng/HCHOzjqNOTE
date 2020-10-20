#include <bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;
struct PAM
{
    int ch[maxn*2][26],fail[maxn*2],S[maxn*2];
    int n[2],tot,Len[maxn*2],cnt[maxn*2],num[maxn*2];
    int l,r;
    int last[2];
    int newnode(int len)
    {
        for(int i=0;i<26;i++)ch[tot][i]=0;
        Len[tot]=len,fail[tot]=0,cnt[tot]=0,num[tot]=0;
        return tot++;
    }
    void init()
    {
        tot=l=r=0;
        newnode(0),newnode(-1);//1表示左边插入
        fail[0]=1;
        memset(S,-1,sizeof S);
        n[1]=maxn-9,n[0]=maxn-10;//0表示右边的边界，1表示左边边界//
    }
    int getFail(int x,int k)//k=0表示向右+，反之
    {
        while(S[n[k]-(Len[x]+1)*(k?-1:1)]!=S[n[k]]){x=fail[x];}
        return x;
    }
    int ins(int c,int k){
        c-='a';
        S[n[k]+=(k?-1:1)]=c;
        int cur=getFail(k?l:r,k);
        if(!ch[cur][c]){
            int now=newnode(Len[cur]+2);
            fail[now]=ch[getFail(fail[cur],k)][c];
            ch[cur][c]=now;
            num[now]=num[fail[now]]+1;
           
        }
        if(k==1){
            l=ch[cur][c];cnt[l]++;
             if(n[0]-n[1]+1==Len[l]){
                    r=l;
            }
            return num[l];
        }else {
            r=ch[cur][c];cnt[r]++;
            if(n[0]-n[1]+1==Len[r]){
                l=r;
            }
            return num[r];
        }
    }
}pam;


int main()
{
    int n;
    
    while(cin>>n)
    {
        pam.init();
        int all=0;
        for(int i=1;i<=n;i++){
            int a;char b;
            scanf("%d",&a);
            if(a==1||a==2){
                cin>>b;
                all+=pam.ins(b,a==1);
            }else if(a==3){
                printf("%d\n",pam.tot-2);
            }else {
                printf("%d\n",all);
            }
        }
    }
    
}