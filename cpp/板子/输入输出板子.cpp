#include <iostream>
#include <map>
#include <ctime>
#include <vector>
#include <climits>
#include <algorithm>
#include <random>
#include <cstring>
#include <cstdio>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#define inf 0x3f3f3f3f
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define rep(i, a, n) for(register int i = a; i <= n; ++ i)
#define per(i, a, n) for(register int i = n; i >= a; -- i)
//#define ONLINE_JUDGE
using namespace std;
typedef long long ll;
const int mod=1e9+7;
template<typename T>void write(T x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9)
    {
        write(x/10);
    }
    putchar(x%10+'0');
}
  
template<typename T> void read(T &x)
{
    x = 0;char ch = getchar();ll f = 1;
    while(!isdigit(ch)){if(ch == '-')f*=-1;ch=getchar();}
    while(isdigit(ch)){x = x*10+ch-48;ch=getchar();}x*=f;
}
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;};
ll ksm(ll a,ll n){//看是否要mod
    ll ans=1;
    while(n){
        if(n&1) ans=((ans%mod)*(a%mod))%mod;
        a=((a%mod)*(a%mod))%mod;
        n>>=1;
    }
    return ans%mod;
}

int main()
{

}
