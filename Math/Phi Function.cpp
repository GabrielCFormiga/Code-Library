// Euler's totient function
//
// Time Complexity: O(sqrt(n))
int phi(int n){
    int result = n;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            int count = 0;
            while(n % i == 0){
                n /= i;
            }
            result -= result / i;
        }
    }
    if(n > 1) result -= result / n;
    return result;
}

// Euler's totient function 1 to n in O(nlog(log(n)))
// use the same ideas as the Sieve of Eratosthenes
vector<int> phi_1_to_n(int n){
    vector<int> vec(n + 1);
    for(int i = 0; i <= n; i++) 
        vec[i] = i;
    for(int i = 2; i <= n; i++){
        if(vec[i] == i){
            for(int j = i; j <= n; j += i){
                vec[j] -= vec[j] / i;
            }
        }
    }
    return vec;
}
