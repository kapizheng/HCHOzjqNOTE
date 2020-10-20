#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int nxt[405];
char a[4005];
char s[4005];
void gnxt(int len)
{
    int i,j;
    nxt[0]=-1;i=0,j=-1;
    while(i<len)
    {
        if(j==-1||a[i]==a[j]){
            i++;j++;
            nxt[i]=j;
        }else j=nxt[j];
    }
}

char sz[4002][405];
bool kmp(int x,int L)
{
    int i,j;
    i=0;j=0;
    int len=strlen(sz[x]);
    while(i<len&&j<L){
        if(j==-1||sz[x][i]==a[j]){
            i++;j++;
        }else j=nxt[j];
        if(j>=L)return true;
    }
    return false;
}
char ans[4005];
char mins[205];
int main()
{
    int n;
    while(~scanf("%d",&n)&&n)
    {
        ans[0]='\0';
        int minv=0x3f3f3f3f;
        for(int i=1;i<=n;i++){
            scanf("%s",sz[i]);
            int len=strlen(sz[i]);
            if(len<minv){
                strcpy(mins,sz[i]);
                minv=len;
            }
        }
        int Len=minv;
        for(int be=0;be<Len;be++){
            for(int ed=be;ed<Len;ed++){
                strncpy(a,mins+be,ed-be+1);
                a[ed-be+1]='\0';
                gnxt(ed-be+1);
                int flag=1;
                for(int j=2;j<=n;j++){
                    if(!kmp(j,ed-be+1)){
                        flag=0;break;
                    }
                }
                if(flag){
                    int La=strlen(ans),Lb=strlen(a);
                    if(La<Lb)
                    strcpy(ans,a);
                    else if(La==Lb&&strcmp(ans,a)>0){
                        strcpy(ans,a);
                    }
                }
            }
        }
        int L=strlen(ans);
        if(L){
            puts(ans);
        }else {
            puts("IDENTITY LOST");
        }
    }
}