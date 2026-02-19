// Crivo de Erastotenes
//
// Time Complexity: O(nloglogn)
// Auxiliary Space: O(n)
// Find primes in range [2, n]

vector<int> sieve(int n){
    vector<int> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for(int i = 2; (long long)i * i <= n; i++){
        if(is_prime[i]){
            for(int j = i * i; j <= n; j += i){
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}
