// Longest Common Subsequence
//
// Encontrar a maior subsequência de duas strings

// O(|S| * |T|)

#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3010;
int dp[N][N];

int main() {
    string s,t;
    cin>>s>>t;
    
    int n = s.size(), m = t.size();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    // Tamanho da maior subsequencia
    cout << dp[n][m] << '\n';

    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i-1] == t[j-1]) {
            lcs.push_back(s[i-1]);
            i--, j--;
        }
        else if (dp[i-1][j] > dp[i][j-1]) i--;
        else j--;
    }
    reverse(lcs.begin(), lcs.end());

    cout << lcs << '\n';
}