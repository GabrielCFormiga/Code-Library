// Problema das 8 Damas

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
using namespace std;

int n;
int cnt = 0;

void add(vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2, int row, int col) {
    cols[col] = true;
    diag1[row - col + n - 1] = true;
    diag2[row + col] = true;
}

void rem(vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2, int row, int col) {
    cols[col] = false;
    diag1[row - col + n - 1] = false;
    diag2[row + col] = false;
}

void backtracking(int row, vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2) {
    if(row == n) {
        cnt += 1;
        return; 
    }                  
    for(int col = 0; col < n; col++) {
        if(!cols[col] && !diag1[row - col + n - 1] && !diag2[row + col]) {
            add(cols, diag1, diag2, row, col);
            backtracking(row + 1, cols, diag1, diag2);
            rem(cols, diag1, diag2, row, col);
        }
    }
}

int main(){ _
    cin >> n; // number of rows = columns
    vector<bool> cols(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
    backtracking(0, cols, diag1, diag2);
    cout << cnt << endl;

    return 0;
}