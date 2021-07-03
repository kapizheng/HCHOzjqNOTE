### Day1

python 或者 java 要精通一种。大数字模板要去学。我好菜。

#### 第六题 乘法

比较难搞的二分，要认真对待下`lower_bound(,,,)`和`upper_bound(,,,)`两个函数

还要注意`long long`

还要注意`k`的值。

```
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
vector<ll> a1,a2,b1,b2;
ll la,lb;
ll check(ll m)
{
	ll res=0;
	if(m<0)
	{
		for(int i=0;i<a1.size();i++){//负数 
			ll t=m/a1[i];
			if(t*a1[i]!=m)t++;
			res+=b2.end()-lower_bound(b2.begin(),b2.end(),t);
		} 
		for(int i=0;i<b1.size();i++){
			ll t=m/b1[i];
			if(t*b1[i]!=m)t++;
			res+=a2.end()-lower_bound(a2.begin(),a2.end(),t);
		}
	}else {
		res+=la*(ll)(b1.size()+b2.size());
		res+=lb*(ll)(a2.size()+a1.size());
		res+=(ll)b1.size()*(ll)a2.size();
		res+=(ll)b2.size()*(ll)a1.size();
		res+=la*lb;
		if(m==0)return res;
		for(int i=0;i<a1.size();i++){
			ll t=m/a1[i];
			if(t==0)continue;
			res+=b1.end()-lower_bound(b1.begin(),b1.end(),t);
		} 
		for(int i=0;i<a2.size();i++){
			ll t=m/a2[i];
			if(t==0)continue;
			res+=upper_bound(b2.begin(),b2.end(),t)-b2.begin();
		}
	}
	return res;
}


int main()
{
	ll n,m,k;
	cin>>n>>m>>k;
	k=n*m-k+1;
	
	for(int i=1;i<=n;i++){
		ll x;scanf("%lld",&x);
		if(x==0)la++;
		else if(x<0)a1.push_back(x);
		else a2.push_back(x);
	}
	for(int i=1;i<=m;i++){
		ll x;scanf("%lld",&x);
		if(x==0)lb++;
		else if(x<0)b1.push_back(x);
		else b2.push_back(x);
	}
	sort(a1.begin(),a1.end());
	sort(a2.begin(),a2.end());
	sort(b1.begin(),b1.end());
	sort(b2.begin(),b2.end());
	ll l=-1e13,r=1e13;
	ll ans;
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(check(mid)>=k){
			ans=mid;r=mid-1;
		}else {
			l=mid+1;
		}
	} 
	cout<<ans<<endl;
} 



/*
3 3 3
2 3 4
4 5 6

*/ 
```



### Day2