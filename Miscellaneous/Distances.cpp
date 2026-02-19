// Distancias
//

// Localização de um ponto em relação a 2 duas retas
int main() {

    ll x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    // Vetor p1→p2 = (x2-x1, y2-y1)
    // Vetor p1→p3 = (x3-x1, y3-y1)
    // Cross = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)
    ll cross = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);

    if (cross > 0) {
        cout << "ESQUERDA\n";
    } else if (cross < 0) {
        cout << "DIREITA\n";
    } else {
        cout << "TOCANDO\n";
    }

}

// Distância de um ponto a uma reta
double pointLineDistance(
    ll x1, ll y1,
    ll x2, ll y2,
    ll x3, ll y3
) {
    // Numerador = área do paralelogramo entre p1→p2 e p1→p3
    ll num = (x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3);
    double area2 = abs((double)num);

    // Denominador = comprimento de p1→p2
    double dx = double(x2 - x1);
    double dy = double(y2 - y1);
    double len = sqrt(dx*dx + dy*dy);

    // distância
    return area2 / len;
}

int main(){

    long long x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    double d = pointLineDistance(x1,y1, x2,y2, x3,y3);
    cout << fixed << setprecision(6) << d << "\n";
    return 0;
}

// Distância de um ponto ao plano

double pointPlaneDistance(
    // pontos do plano
    double x1, double y1, double z1,
    double x2, double y2, double z2,
    double x3, double y3, double z3,
    // ponto externo
    double x0, double y0, double z0
) {
    // vetores u = P2-P1, v = P3-P1
    double ux = x2 - x1, uy = y2 - y1, uz = z2 - z1;
    double vx = x3 - x1, vy = y3 - y1, vz = z3 - z1;
    // normal n = u x v
    double A = uy * vz - uz * vy;
    double B = uz * vx - ux * vz;
    double C = ux * vy - uy * vx;
    // coeficiente D
    double D = - (A * x1 + B * y1 + C * z1);

    // avalia distância
    double num = fabs(A * x0 + B * y0 + C * z0 + D);
    double den = sqrt(A*A + B*B + C*C);
    return num / den;
}

int main(){
    double x1,y1,z1, x2,y2,z2, x3,y3,z3, x0,y0,z0;
    // Plano
    cin >> x1 >> y1 >> z1
        >> x2 >> y2 >> z2
        >> x3 >> y3 >> z3;
    // Ponto
    cin >> x0 >> y0 >> z0;

    double d = pointPlaneDistance(
        x1,y1,z1, x2,y2,z2, x3,y3,z3,
        x0,y0,z0
    );
    cout << fixed << setprecision(6) << d << "\n";
    return 0;
}

// Ponto está dentro ou fora do Plano

int main(){
    // Plano
    double x1,y1,z1, x2,y2,z2, x3,y3,z3;
    cin >> x1 >> y1 >> z1
        >> x2 >> y2 >> z2
        >> x3 >> y3 >> z3;

    // Ponto
    double x0,y0,z0;
    cin >> x0 >> y0 >> z0;

    // Normal (A,B,C) = (P2-P1)×(P3-P1)
    double ux = x2 - x1, uy = y2 - y1, uz = z2 - z1;
    double vx = x3 - x1, vy = y3 - y1, vz = z3 - z1;
    double A = uy*vz - uz*vy;
    double B = uz*vx - ux*vz;
    double C = ux*vy - uy*vx;
    // Constante D da equação do plano
    double D = - (A*x1 + B*y1 + C*z1);

    // Avalia F(P0)
    double F = A*x0 + B*y0 + C*z0 + D;

    if (F > 0) {
        cout << "LADO POSITIVO\n";
    } else if (F < 0) {
        cout << "LADO NEGATIVO\n";
    } else {
        cout << "SOBRE O PLANO\n";
    }
}

// Ponto dentro ou fora da circunferência
int main(){

    double xc, yc, R;
    cin >> xc >> yc >> R;

    double x, y;
    cin >> x >> y;

    double dx = x - xc;
    double dy = y - yc;
    double dist2 = dx*dx + dy*dy;
    double R2 = R*R;

    if (dist2 < R2) {
        cout << "DENTRO\n";
    }
    else if (dist2 == R2) {
        cout << "SOBRE\n";
    }
    else {
        cout << "FORA\n";
    }
}
