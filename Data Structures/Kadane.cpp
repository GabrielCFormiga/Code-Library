// Kadane
//
// Calcula o subarray com maior soma em O(n)

int kadane(vector<int> &vec) {
    int mx = INT_MIN;
    int curr = 0;
    for (int x : vec) {
        curr += x;
        mx = max(mx, curr);
        curr = max(curr, 0);
    }
    return curr;
}
