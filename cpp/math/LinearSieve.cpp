// tested on https://www.spoj.com/problems/FACTCG2/

// O(N)
// Comentarios generales :
// p[i] para 0 < i indica el valor del primo i-esimo 
//	Ejm : p[1] = 2 , p[2] = 3 ....
// A[i] indica que el menor factor primo de i es el primo A[i] - esimo 
//	Ejm: si 15 = 3*5 , entonces A[12] = 2 porque el menor factor primo de 12 es 3 y 3 es el 2do primo
const int MAXN = (int) 1e7 + 5;
int A[MAXN + 1], p[MAXN + 1], pc = 0;  
void sieve()  
{ 
    for(int i=2; i<=MAXN; i++){ 
        if(!A[i]) p[A[i] = ++pc] = i; 
        for(int j=1; j<=A[i] && (long long)i*p[j]<=MAXN; j++) 
            A[i*p[j]] = j; 
    } 
}

vector<int> primeFact(int n) { // O(log(n))
    vector<int> v;
    while (n != 1) {
        v.push_back(p[A[n]]);
        n /= p[A[n]];
    }
    return v;
}