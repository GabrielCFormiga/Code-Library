// Inversa Modular
//
// The exact time complexity of the this recursion is not known. 
// It's is somewhere between  O(logm / loglogm) and O(m^(1/3 -2/177 + e))
// demo:
// m prime and a,r < m -> exist a_inv and r_inv
// m = k*a + r
// 0 ≡ k*a + r (mod m)
// -k*a ≡ r (mod m)
// -k ≡ r*a_inv (mod m)
// a_inv ≡ k*r_inv (mod m)

int inv(int a, int m){
    return a <= 1 ? a : m - (long long)(m / a) * inv(m % a, m) % m;
}

// Binary Exponentation method
// O(log m)
// if a and m are relatively prime and m is prime
// power(a, m - 2) ≡ a_inv (mod m)
long long binpow(long long a, long long b){
    long long result = 1;
    while(b > 0){
        if(b & 1) result *= a;
        a *= a;
        b >>= 1;
    }
    return result;
}

// precompute the inverse for every number in the range [1, m- 1] in O(m)
int main(){
    int m = 1000000007;
    int invArray[m];
    invArray[1] = 1;
    for(int a = 2; a < m; a++){
        invArray[a] = m - (long long)(m / a) * invArray[m % a] % m;
    }
}