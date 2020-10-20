#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("in.txt","w",stdout);
    srand((unsigned)(time(NULL)));
    // puts("1");//
    puts("5 5");
    int n=5;
    for(int i=1;i<=n;i++){
        printf("%d ",rand()%(n));
    }
    cout<<endl;
    for(int i=2;i<=n;i++){
        printf("%d %d\n",i,rand()%(i-1)+1);
    }
    int m=5;
    for(int i=1;i<=m;i++){
        int opt=rand()%2+1;
        // if(opt==0){
        //     printf("I %d %d %d\n",rand()%n+1,rand()%n+1,rand()%100);
        // }else if(opt==1){
        //     printf("Q %d\n",rand()%n+1);
        // }else {
        //     printf("D %d %d %d\n",rand()%n+1,rand()%n+1,rand()%100);

        // }
        if(opt==1){
            printf("%d %d %d\n",opt,rand()%n+1,rand()%10);
        }else {
            printf("%d %d\n",opt,rand()%n+1);
        }
    }

}

/*s
5 5
0 0 0 0 0 
2 1
3 2
4 2
5 2
1 1 7
2 3
2 1
1 5 0
2 2
*/