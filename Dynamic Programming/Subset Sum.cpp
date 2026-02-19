// Subset Sum
//
// Time Complexity: O(N*K)
// Space Complexity: O(K/32)

#include <bits/stdc++.h>
using namespace std;

int n,k;
vector<int> v;

int main() {
    cin>>n>>k;
    v.resize(n);

    for (int i = 0; i < n; i++)
        cin>>v[i];

    vector<bool> dp(k+1);
    dp[0] = true;  // Base case: we can always form sum 0 with an empty set
    
    for (int i = 0; i < n; i++) {
        for (int j = k; j >= v[i]; j--) {
            dp[j] = dp[j] || dp[j - v[i]];
        }
    }

    cout << dp[k] << '\n';
}