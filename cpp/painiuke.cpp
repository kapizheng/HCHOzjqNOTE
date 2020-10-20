#include <bits/stdc++.h>

using namespace std;
int A[100000];
int main()
{
    freopen("in.txt","w",stdout);
    srand(((unsigned)(time(NULL))));
    int n=10,m=10;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++){
        cout<<(A[i]=rand()%10)<<" ";
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        printf("%d %d %d\n",rand()%10,rand()%i+1,rand()%i+1);
    }
    
}