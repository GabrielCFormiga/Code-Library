// Quadrado Perfeito

#include <bits/stdc++.h>

// Time Complexity: O(log n)
// Auxiliary Space: O(1)
bool isPerfectSquare(long double n){
    if(n >= 0){
        // se a raiz de n é inteira não haverá arredondamento para o menor inteiro
        long long sr = sqrt(n);

        // verifica se houve o arredondamento e retorna a reposta
        return (sr * sr == n);
    }

    //retorna falso caso x < 0
    return false;
}

// Time Complexity: O(log n)
// Auxiliary Space: O(1)
bool binary_isPerfectSquare(long long n){
    // caso 0 e 1
    if(n <= 1) return true;
    
    // limites da busca binária
    long long l = 1, r = n;
    long long square, mid;
    while(l <= r){
        // calcular valor do meio
        mid = (l + r) / 2;

        // calcular quadrado do termo do meio
        square = mid * mid;

        if(square == n){
            return true; 
        } 
        
        // buscar na direita
        else if(square < n){
            l = mid + 1;
        }
        
        // buscar na esquerda
        else {
            r = mid - 1;
        }
    }
    
    // caso saia do loop sem achar um quadrado perfeito
    return false;
}


// Time Complexity: O(sqrt(n))
// Auxiliary Space: O(1)
bool isPerfectSquare(long double n){
    if(floor(sqrt(n)) == ceil(sqrt(n))) return true;
    else return false;
}