#include<bits/stdc++.h>

using namespace std;

int is(string str)
{
	string tmp=str;
	reverse(str.begin(),str.end());
	int num=0;
	for(int i=0;i<str.length();i++){
		if(tmp[i]!=str[i]){
			num++;
		}
	}
	return num;
}
//aabaaa
//aaabaa
//bbaabb
//
//aabaa

int check(string now,string stdd)
{
	int cnt=0;
	int len=stdd.length();
	while(now!=stdd){
		char fi=now.front();
		now.erase(0,1);
		now+=fi;
		cnt++;
		if(cnt>len)return -1;
	}
	return cnt;

}
int a[100005];
int main()
{
	int n,m;
	cin>>n>>m;

	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		priority_queue<int> que;
		for(int j=x;j<=y;j++){
			que.push(-1*a[j]);
		}
		int pos=z-x+1;
		while(pos-->1){
			que.pop();
		}
		int now=que.top()*-1;
		if(now==a[z]){
			cout<<"Yes"<<endl;
		}else {
			cout<<"No"<<endl;
		}
	}
}
//abbaa
//aaabbb