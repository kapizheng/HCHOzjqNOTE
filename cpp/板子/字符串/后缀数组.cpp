#include <bits/stdc++.h>

using namespace std;
const int maxn=2e6+10;

int hgt[maxn];
int a[maxn],sa[maxn],Rank[maxn],tax[maxn],tp[maxn];
int n,m;
void Rsort()
{
    for(int i=0;i<=m;i++)tax[i]=0;
    for(int i=1;i<=n;i++)tax[Rank[tp[i]]]++;
    for(int i=1;i<=m;i++)tax[i]+=tax[i-1];
    for(int i=n;i>=1;i--)sa[tax[Rank[tp[i]]]--]=tp[i];
}

bool cmp(int *f,int x,int y,int w)
{
    return f[x]==f[y]&&f[x+w]==f[y+w];
}

void Sa()
{
    for(int i=1;i<=n;i++)Rank[i]=a[i],tp[i]=i;
    m=256;Rsort();
    for(int p=1,w=1;p<n;m=p,w+=w)
    {
        int i;
        for(p=0,i=n-w+1;i<=n;i++)tp[++p]=i;
        for(i=1;i<=n;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
        Rsort();swap(tp,Rank);Rank[sa[1]]=p=1;
        for(int i=2;i<=n;i++)Rank[sa[i]]=cmp(tp,sa[i],sa[i-1],w)?p:++p;
    }
    int i,j;
    int k=0;
    for(i=1;i<=n;hgt[Rank[i++]]=k){
        for(k=k?k-1:k,j=sa[Rank[i]-1];a[i+k]==a[j+k];k++);
    }
}
int dp[2000006][25];
void RMQinit()
{
    for(int i=2;i<=n;i++)dp[i][0]=hgt[i];
    //for(int i=1;i<=n;i++)cout<<" "<<dp[i][0];cout<<endl;
    for(int j=1;(1<<j)<=n;j++){
        for(int i=2;i+(1<<j)-1<=n;i++){
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        }
    }
}
int RMQ(int l,int r)
{
    int k=0;while(r-l+1>=(1<<(k+1)))k++;
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
}

int LCP(int a,int b)//排名多少
{
    if(a>b)swap(a,b);
    return RMQ(a+1,b);
}
char s[maxn];


int pre[maxn],last[maxn];
int main()
{
    int t;
    cin>>t;int kk=1;
    while(t--){
        scanf("%s",s+1);
        n=strlen(s+1);
        memset(a,0,sizeof a);
        for(int i=1;i<=n;i++)a[i]=s[i];
        Sa();
        for(int i=1;i<=n;i++){
            if(hgt[i]==0)pre[i]=i;
            else pre[i]=pre[i-1];
        }//
        for(int i=n;i>=1;i--){
            if(hgt[i+1]==0||i==n)last[i]=i;
            else last[i]=last[i+1];
        }
        printf("Case #%d:\n",kk++);
        int i=1;
        
        while(i<=n)
        {
            int k,t;
            k=0,t=i;
            int now=Rank[i];
            int len=hgt[now];
            for(int j=now-1;j>=pre[now];j--){
                len=min(len,hgt[j+1]);//
                if(len<k)break;
                if(sa[j]<i&&(len>k||len==k&&sa[j]<t)){
                    k=len;t=sa[j];
                }
            }
            if(now+1<=last[now])len=hgt[now+1];
            for(int j=now+1;j<=last[now];j++){
                len=min(len,hgt[j]);
                if(len<k)break;
                if(sa[j]<i&&(len>k||len==k&&sa[j]<t)){
                    k=len;t=sa[j];
                }
            } 
            if(k==0)printf("-1 %d\n",s[i]);
            else printf("%d %d\n",k,t-1);
            if(k==0)i++;
            else i+=k;
        }
    }

}