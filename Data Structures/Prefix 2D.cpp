// Prefix 2d
//

int main(){
    
    prefix[i][j] = array[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
    
    // Achando o valor de alguma célula:
    valor = prefix[y2][x2] - prefix[y2][x1-1] - prefix[y1-1][x2] + prefix[y1-1][x1-1];
}
