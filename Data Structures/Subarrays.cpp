// Subarrays
//
// Subarray Sums II https://cses.fi/problemset/task/1661/

// Calculando a quantidade de subarrays válidos.
// Se a soma de um subarray é igual a k

int main(){
    int n, k; cin >> n >> k;

    vector<int> arr(n);
    for (auto &i : arr) cin >> i;
 
    ll ans = 0;
    ll prefix_sum = 0;
    map<ll, int> rastreio;
 
    rastreio[0]++;
    for (int x : arr){
        prefix_sum += x;
 
        ans += rastreio[prefix_sum - k];
 
        rastreio[prefix_sum]++;
    }
 
    cout << ans << "\n";
}


// Subarray Divisibility: https://cses.fi/problemset/view/1662/
// Contando a quantidade de subarrays que a soma é divisível por n.

int main(){
    
    int n; cin >> n;
 
    vector<ll> arr(n);
    arr[0]++;
    ll prefix = 0;
    for (int i = 1; i <= n; i++){
        ll a; cin >> a;
 
        prefix += a;
        arr[((prefix % n) + n) % n]++;
    }
 
    ll ans = 0;
    for (auto x : arr){
        ans += ((x-1)*(x))/2;
    }
 
    cout << ans << "\n";
}
