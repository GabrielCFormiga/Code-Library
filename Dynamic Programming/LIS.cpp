// Longest Increasing Subsequence
//
// Maior subsequência crescente de um vetor de números
// O(n log(n))

#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

int main() {
    int n;
    cin>>n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin>>v[i];

    vector<int> lis;
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(lis.begin(), lis.end(), v[i]);
        if (it == lis.end()) lis.push_back(v[i]);
        else {
            int k = it-lis.begin();
            lis[k] = v[i];
        }
    }

    // Tamanho da maior subsequencia
    cout << lis.size() << '\n';
}