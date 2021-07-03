```C++
#include<bits/stdc++.h>

using namespace std;
const int N=2000100;
long long ans;
long long bin[N];
long long zz[N];
const int mod=1000000007;
struct PAM
{
	int fail[N],tire[N][11];
	long long cnt[N],num[N];
	long long all[N];
	int S[N];
	int Len[N];
	int last,tot,n;
	int newnode(int l)
	{
		for(int i=0;i<10;i++)tire[tot][i]=0;
		cnt[tot]=num[tot]=all[tot]=0;
		Len[tot]=l;
		return tot++;
	}
	void init()
	{
		tot=n=last=0;
		newnode(0),newnode(-1);
		S[0]=-1;fail[0]=1;
	}
	int getfail(int x)
	{
		while(S[n-Len[x]-1]!=S[n]){
			x=fail[x];
		}
		return x;
	}
	
	int insert(int c,int i)
	{
		c-='0';
		S[++n]=c;
		int cur=getfail(last);
	
		if(!tire[cur][c])
		{
			int now=newnode(Len[cur]+2);
			fail[now]=tire[getfail(fail[cur])][c];
			tire[cur][c]=now;
			ans=(ans%mod+(zz[i]%mod-zz[i-Len[now]]*bin[Len[now]]%mod+mod))%mod;
			num[now]=num[fail[now]]+1;
		}
		last=tire[cur][c];
		cnt[last]++;
		return num[last];
	}
	void count()
	{
		for(int i=tot-1;i>=2;i--){
			ans+=all[i];
			ans%=mod;
		}
	}
}pam;
void dfs(int u)
{
	for(int i=1;i<10;i++){
		if(pam.tire[u][i]){
			ans+=(pam.cnt[pam.tire[u][i]]*pam.all[pam.tire[u][i]])%mod;
			ans%=mod;
			dfs(pam.tire[u][i]);
		}
	}
}

int main()
{

	string str;
	bin[1]=1;
	//cout<<((123456789+1111111111)%1000000007)<<endl;
	
	while(cin>>str)
	{
		ans=0;
		zz[0]=str[0]-'0';bin[0]=1;
		for(int i=1;i<str.length();i++)bin[i]=(bin[i-1]*10)%mod,zz[i]=(zz[i-1]*10%mod+str[i]-'0')%mod;
		pam.init();
		for(int i=0;i<str.length();i++)pam.insert(str[i],i);
		//pam.count();
		printf("%lld\n",ans);	
	}
}
```

字符串hash++回文串，不知道为什么hash后还保存着原来的大小，不会因为太大而emm。好像是可以的

嘚研究下字符串hash，

或许

不久之后就要退役了吧，记录一下这道题。

