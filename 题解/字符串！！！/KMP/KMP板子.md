```C++
#include<iostream>
#include<cstring>
const int maxn=1000010;
char ch[maxn];
char b[maxn];
int nxt[maxn];
char str[maxn];
using namespace std;
void getnxt()
{
	int len=strlen(ch);
	int i,j;
	i=0;j=-1;
	nxt[0]=-1;
	while(i<len)
	{
		if(j==-1||ch[i]==ch[j])
		{
			i++;j++;
			nxt[i]=j;
		}else j=nxt[j];
	}
}

void kmp()
{
	getnxt();
	
	int len=strlen(str);
	int len2=strlen(ch);
	int i,j;i=0,j=0;
	int ans=0;
	while(i<len)
	{
		
		if(j==-1||str[i]==ch[j])
		{
			i++;j++;
		}else j=nxt[j];
		if(j>=len2){
			ans++;j=nxt[j];
		}
	} 
	
	printf("%d\n",ans);
}

int main()
{
	//freopen("in.txt","r",stdin);
	int t;cin>>t;
	
	while(t--)
	{
		scanf("%s",ch);
		scanf("%s",str);
		kmp();
	}
	
}
```

