// Edit Distance DP
//
// Encontrar o valor minimo de operações 
// para tornar uma string igual a outra.

// Operações:
// Adicionar um elemento na string
// Remover um elemento da string
// Modificar um elemento da string

// O(|S| * |T|)

#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2010;
int dp[N][N];

int main() {
    string s,t;
    cin>>s>>t;
    
    int n = s.size(), m = t.size();

    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int i = 0; i <= m; i++)
        dp[0][i] = i;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j-1], dp[i][j-1], dp[i-1][j]});
        }
    }

    cout << dp[n][m] << '\n';
}