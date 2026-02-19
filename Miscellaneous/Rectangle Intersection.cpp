// Intersecao de Retangulos

#include <bits/stdc++.h>

using namespace std;

struct Rect {
    int x1, y1, x2, y2;
    int area(){
        return (y2 - y1) * (x2 - x1);
    }
};

int intersect(Rect p, Rect q){
    int xOverlap = max(0, min(p.x2, q.x2) - max(p.x1, q.x1));
	int yOverlap = max(0, min(p.y2, q.y2) - max(p.y1, q.y1));
	return xOverlap * yOverlap;
}