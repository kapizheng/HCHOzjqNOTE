#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int i,j,k;
	freopen("test.in","w",stdout);
	// puts("1");
	srand((unsigned)time(NULL));
	int n=5,m=10;
	printf("%d %d %d\n",n,n-1,m);
	
	for(i=1;i<=n;i++)
	{
		printf("%d\n",rand()%100+1);
	}
	for(i=1;i<n;i++)
	{
		printf("%d %d\n",i+1,rand()%i+1);
	}
	for(int i=1;i<=m;i++){
		printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand()%n+1);
	}
	puts("DONE");
	fclose(stdout);
	return 0;
}