#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string> duval(string str){
	int i = 0,j,k,n = str.size();
	
	vector<string> ans;
	
	while(i < n){
		k = i;
		j = i + 1;
		while(j < n && str[k] <= str[j]){
			k = str[k] == str[j] ? k + 1 : i;
			j++;
		}
		while(i <= k){
			ans.push_back(str.substr(i,j - k));
			i += j - k;
		}
	}
	return ans;
}

int main(){
	string str;
	cin >> str;
	vector<string> ans = duval(str);
	for(int i = 0;i < ans.size();i++){
		cout << ans[i] << endl;
	}
}
