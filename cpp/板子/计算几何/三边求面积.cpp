#include <bits/stdc++.h>

using namespace std;



double Helen(double i,double j,double k){
    double p;
    p=(i+j+k)/2;
    return sqrt(p*(p-i)*(p-j)*(p-k));
}
int a[10000];
int b[20005];
int dp[2005][2005];
int val[2006][2006];
long long suma[2006];
long long sumb[2006];
struct node
{
    long long sum;
    int len;
    node(){}
    node(long long s,int l){
        sum=s,len=l;
    }
}A[4000006],B[4000006];
long long cha[4000006];
long long l[2006],c[2006];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        suma[i]=suma[i-1]+a[i];
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
        sumb[i]=sumb[i-1]+b[i];
    }
    int cnta=0;
    int cntb=0;
    memset(c,0x3f,sizeof c);
    memset(l,0x3f,sizeof l);
    for(int i=1;i<=n;i++){
        for(int j=1;j+i-1<=n;j++){
            c[i]=min(c[i],suma[j+i-1]-suma[j-1]);
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j+i-1<=m;j++){
            l[i]=min(l[i],sumb[j+i-1]-sumb[j-1]);
        }
    }
    int ans=0;long long k;cin>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i]*l[j]<=k){
                ans=max(i*j,ans);
            }
        }
    }
    cout<<ans<<endl;
}