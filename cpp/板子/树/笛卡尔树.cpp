#include<bits/stdc++.h>
//必要时可以+fa[maxn];
using namespace std;
const int maxn=2e6+10;
long long p[maxn];
long long d[maxn];
long long s[maxn];
long long ls[maxn],rs[maxn];
long long dfn[maxn];
int tot;
const long long mod=1e9+7;
long long inf=1e18;
void dfs(int l,int r,int rt)
{
	if(l>r)return ;
	if(l==r){
		dfn[l]=tot++;return ;
	}
	if(p[rt]==inf){
		for(int i=l;i<=r;i++){
			dfn[i]=tot++;
		}
		return ;
	}else if(p[rt]%10<d[rt]){dfs(l,rt,ls[rt]);dfs(rt+1,r,rs[rt]);}
	else {dfs(rt+1,r,rs[rt]);dfs(l,rt,ls[rt]);}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		tot=0;
		long long seed,pa,pb,pm;
		long long seedb,pab,pbb,pmb;
		scanf("%lld%lld%lld%lld",&seed,&pa,&pb,&pm);
		scanf("%lld%lld%lld%lld",&seedb,&pab,&pbb,&pmb);
		long long has=1;
		for(int i=0;i<n;i++){
			p[i]=i;
			ls[i]=rs[i]=0;
			d[i]=seedb%10;
			seedb=(seedb*pab+pbb)%pmb;
		}
		ls[n]=rs[n]=0;
		for(int i=1;i<n;i++){
			swap(p[seed%(i+1)],p[i]);
			seed=(seed*pa+pb)%pm;
		}
		for(int i=0;i<n;i++){
			if(p[i]%10==d[i])p[i]=inf;
		}
		int top;
		top=0;
		for(int i=0;i<n;i++){
			while(top&&p[s[top]]>p[i]){
				ls[i]=s[top];top--;
			}
			if(top)rs[s[top]]=i;
			s[++top]=i;
		}
		dfs(0,n,s[1]);
		long long ans=0;
		for(int i=0;i<=n;i++){
			ans+=(dfn[i]*has)%mod;
			ans%=mod;
			has=has*10000019;
			has%=mod;
		}
		printf("%lld\n",ans);
	}
}