// Permutacoes de String
//
// CSES - Creating Strings
// https://cses.fi/problemset/task/1622/

#include <bits/stdc++.h>
 
using namespace std;
 
string str;
vector<string> perms;
int char_count[26];
 
void search(const string &curr = ""){
    if(curr.size() == str.size()){
        perms.push_back(curr);
        return;
    }
    for(int i = 0; i < 26; i++){
        if(char_count[i] > 0){
            char_count[i]--;
            search(curr + (char)('a' + i));
            char_count[i]++;
        }
    }
}
 
int main(){ 
    cin >> str;
    for(char c : str){
        char_count[c - 'a']++;
    }
 
    search();
    
    cout << perms.size() << endl;
    for(int i = 0; i < perms.size(); i++){
        cout << perms[i] << endl;
    }
 
    return 0;
}
