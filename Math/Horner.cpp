// Método de Horner para Avaliação Polinomial
//
// f(x) = (Cn * x^n) + (Cn-1 * x^n-1) + (Cn-2 * x^n-2) + ... + (C1 * x) + C0
/* Ex:
 f(x) = 2x3 - 6x2 + 2x - 1
 poly = {2, -6, 2, -1}
 x = 3 -> f(3) = 5
*/

//Time Complexity: O(n)
//Auxiliary Space: O(1)

int horner(vector<int> &poly, int x){
    int result = poly[0];
    int n = poly.size();
    
    for(int i = 1; i < n; i++){
        result = result * x + poly[i];
    }

    return result;
}