#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
long long a[100005];
int vis[100005];

void exgcd(long long a,long long b,long long &x,long long &y,long long &c){//其中a%b的逆元为x,c为gcd
    if(!b){y=0;x=1;c=a;return ;}
    else {
        exgcd(b,a%b,y,x,c);y-=(a/b)*x;
    }
}//推理一下
long long b[100005];
int main()
{
    long long n,k;
    scanf("%lld%lld",&n,&k);
    for(long long i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    vector<long long> v;
    for(long long i=1;i<=n;i++){
        if(vis[i]==0){
            vis[i]=1;
            long long cnt=1;
            long long tmp=a[i];
            v.clear();
            v.push_back(i);
            while(tmp!=i){
                vis[tmp]=1;
                v.push_back(tmp);
                cnt++;
                tmp=a[tmp];
            }
            if(cnt==1){
                b[i]=i;
                continue;
            }
            long long inv,y,c;
            exgcd(k%cnt,cnt,inv,y,c);
            if(inv<0)inv+=cnt;
            for(int j=0;j<v.size();j++){
                b[v[j]]=v[(j+inv)%v.size()];
            }
        }
    }
    for(int i=1;i<=n;i++){
        printf("%lld ",b[i]);
    }
    
    
}