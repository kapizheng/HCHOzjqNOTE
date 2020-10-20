#include<bits/stdc++.h>
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

int lim;
struct node
{
    int l,r,d,idx;
    bool operator<(const node &n)const{
        if(l/lim==n.l/lim){
            if(idx%2)return r<n.r;
            else return r>n.r;
        }else return l<n.l;
    }
}no[100006];
int is[100006];
int a[100006];
int cnt[100006];
int val[100006];
vector<int> v;
int num[100006][400];
void add(int pos)
{
    pos=val[pos];
    cnt[pos]++;
}
void sub(int pos)
{
    pos=val[pos];
    cnt[pos]--;
}
bool check(int L,int R,int d)
{
    for(int i=0;i<v.size()&&d<=v[i];i++){
        int tmp=v[i];
        if(d%tmp==0){
        	int Cnt=0;
        	while(d%tmp==0){
        		Cnt++;d/=tmp;
        	}
        	if(num[R][i]-num[L-1][i]<Cnt){
                return false;
            }
        }
    }
    if(d!=1){
    	if(!cnt[d])return false;
    }
    return true;
}

int CCt[100006][340];
int vis[100006];
int NOW[100006];
void solve(int x)
{
    
    int pos=x;
    for(int i=0;i<v.size()&&x<=v[i];i++){
        if(x%v[i]==0){
            while(x%v[i]==0){
                CCt[pos][i]++;
                x/=v[i];
            }
        }
    }
    if(x!=0){
        NOW[pos]=x;
    }
}

int ans[100006];
int main()
{
    int t;
    for(int i=2;i<=sqrt(100000);i++){
        if(is[i]==0){
            for(int j=i*2;j<=100000;j+=i){
                is[j]=1;
	        }
            v.push_back(i);
        }
    }
    read(t);
    int Left,Right;
    while(t--){
        int n,m;
        memset(cnt,0,sizeof cnt);
        read(n);read(m);
        lim=sqrt(m);
        for(int i=1;i<=n;i++){
            read(a[i]);
            if(!vis[a[i]]){
                solve(a[i]);
                vis[a[i]]=1;
            }
            for(int j=0;j<v.size();j++){
            	num[i][j]=num[i-1][j];
            }
            int tmp=a[i];
            for(int j=0;j<v.size();j++){
            	num[i][j]+=CCt[a[i]][j];
            }
            if(tmp!=1){
            	val[i]=NOW[a[i]];
            }
        }
        for(int i=1;i<=m;i++){
            read(no[i].l);
            read(no[i].r);
            read(no[i].d);
            no[i].idx=i;
        }
        sort(no+1,no+1+m);
        Left=1,Right=0;
        for(int i=1;i<=m;i++){
            int L=no[i].l,R=no[i].r;
            
            while(Left>L)add(--Left);
            while(Left<L)sub(Left++);
            while(Right<R)add(++Right);
            while(Right>R)sub(Right--);
            
            if(check(L,R,no[i].d)){
                ans[no[i].idx]=1;
            }else {
                ans[no[i].idx]=0;
            }
        }
        for(int i=1;i<=m;i++){
            if(ans[i])puts("Yes");
            else puts("No");
        }
    }
}