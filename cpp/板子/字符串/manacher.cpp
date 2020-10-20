#include<bits/stdc++.h>


using namespace std;
const int maxn=1000006;
int mana[maxn*2];
char a[maxn];
int Len[maxn];
int L,R;
int ANS=0;
void Mana()
{
    int c,r;c=r=-1;
    int n=strlen(a);
    int pos=0;mana[0]='$';
    for(int i=0;i<n;i++){
        mana[++pos]='#';
        mana[++pos]=a[i];
    }
        mana[++pos]='#';mana[pos+1]='\0';
        int ans=0;
        int l;
    for(int i=1;i<=pos;i++){
        if(i<r)Len[i]=min(r-i,Len[2*c-i]);
        else Len[i]=1;
        while(mana[i-Len[i]]==mana[i+Len[i]]&&i-Len[i]>=0)Len[i]++;
        if(i+Len[i]>r){
            r=i+Len[i];
            c=i;
        }
        if(Len[i]-1<=ANS)continue;
        if(Len[i]-1>ANS){
            if(Len[i]+i-1==pos){ANS=Len[i]-1;
                R=1;L=0;
            }
            if(i-Len[i]+1==1){ANS=Len[i]-1;
                R=0;L=1;
            }
        }
    }
}

//性质：是左边的情况为：i-len[i]+1==1,1为可用符号的最小点
//是右边的情况为：i+Len[i]-1==pos,pos为可用符号的最大点
char now[maxn];
char fi[maxn];
char se[maxn];
int main()
{
    int t;
    cin>>t;
    while(t--){
        scanf("%s",now);
        int l=0,r=strlen(now)-1;
        int A,B;
        A=B=0;
        ANS=0;
        L=0,R=0;
        while(l<r){
            if(now[l]==now[r]){
                fi[A++]=now[l];
                se[B++]=now[r];
                l++,r--;
            }else
            {
                 break;
            }
        }
        int z=0;
        
        for(int i=l;i<=r;i++){
            a[z++]=now[i];
        }
        // cout<<"EM"<<endl;
        a[z]='\0';
        Mana();
        for(int i=0;i<A;i++){
            putchar(fi[i]);
        }
        if(L){
            for(int i=l;i<l+ANS;i++){
                putchar(now[i]);
            }
        }else if(R){
            // cout<<"E"<<endl;
            for(int i=r;i>r-ANS;i--){
                putchar(now[i]);
            }
            // cout<<"A"<<endl;
        }
        for(int i=B-1;i>=0;i--){
            putchar(se[i]);
        }
        puts("");
    }
}