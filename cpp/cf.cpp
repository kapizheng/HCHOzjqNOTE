#include<bits/stdc++.h>

using namespace std;

struct node
{
    long long l,r;
    bool operator<(const node &n)const{
        if(r==n.r)return l<n.l;
        return r<n.r;
    }
}no[100006];
long long A[100006];
long long hs[100006];
long long Cnt[2000006];
const long long mod=998244353;
long long ksm(long long a,long long b)
{
    long long ans=1;
    while(b)
    {
        if(b&1)ans=ans*a;
        a*=a;
        a%=mod;
        ans%=mod;
        b>>=1;
    }
    return ans;
}

long long cal(long long a,long long b)
{
    return A[a]*ksm(A[b],mod-2)%mod*ksm(A[a-b],mod-2)%mod;
}

int main()
{
    long long n,m;
    cin>>n>>m;
    long long cnt=0;
    for(long long i=1;i<=n;i++){
        long long l,r;
        scanf("%d%d",&l,&r);
        no[i].l=l,no[i].r=r;
        hs[++cnt]=l;
        hs[++cnt]=r;
        hs[++cnt]=r+1;
    }
    sort(hs+1,hs+1+cnt);
    sort(no+1,no+1+n);
    cnt=unique(hs+1,hs+1+cnt)-hs-1;
    A[0]=1;
    for(long long i=1;i<=n;i++){
        long long l=no[i].l,r=no[i].r;
        long long L=lower_bound(hs+1,hs+1+cnt,l)-hs;
        long long R=lower_bound(hs+1,hs+1+cnt,r+1)-hs;
        Cnt[L]++;
        Cnt[R]--;
    }
    for(long long i=1;i<=cnt;i++){
        Cnt[i]+=Cnt[i-1];
    }
    for(long long i=1;i<=100006;i++){
        A[i]=A[i-1]*i%mod;
    }
    long long now=0;
    long long ans=0;
    for(long long i=1;i<=cnt;i++){
        if(Cnt[i]>=m){
            ans+=cal(Cnt[i],m-1)%mod;
        }
    }
    cout<<ans<<endl;
}