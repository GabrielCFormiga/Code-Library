// Algoritmo de Euclides
//
// Time Complexity: O(log min(a,b))
// Auxiliary Space: O(log min(a,b))

int gcd(int a, int b){
    if(b == 0) return a;
    else return cd(b, a % b);
}

int lcm(int a, int b){
    // return a * b / __gcd(a, b) could be overflow
    return a / __gcd(a, b) * b;
}