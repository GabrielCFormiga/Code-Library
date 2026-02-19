// Ruina do Jogador

#include <bits/stdc++.h>

using namespace std;

// p é a probabilidade de ganhar um turno 
// q = 1 - p, ou seka, a probabilidade de perder um turno 
// Ri é a quantia inicial de dinheiro
// N é quantidade de dinheiro para ser vitorioso

double solve(double p, double q, int Ri, int N){
    if(Ri == 0) return 0;
    if(Ri == N) return 1;
    
    // jogo justo
    if(p == q) return (double)Ri / N;
    
    // p != q
    return (1 - (double)pow(q / p, Ri)) / (1 - (double)pow(q / p, N));
}