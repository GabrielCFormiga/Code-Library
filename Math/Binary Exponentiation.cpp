// Exponenciacao Rapida
//
// result = a^b % m 
// Time Complexity = O(log b)

ll binpow(ll a, ll b, ll m){
    ll result = 1;
    while(b > 0){
        if(b & 1) result = result * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return result;
}

// a^b^c -> Pequeno teorema de Fermat | M = 1e9 + 7
// binpow(a, binpow(b, c, m-1), m)