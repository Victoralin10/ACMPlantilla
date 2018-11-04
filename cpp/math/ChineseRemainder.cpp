Dados k enteros positivos {ni}, tales que ni y nj son coprimos (i!=j).
Para cualquier {ai}, existe x tal que:

x % ni = ai

Todas las soluciones son congruentes modulo N = n1*n2*...*nk

r*ni + s*N/ni = 1 -> ei = s*N/ni   -> ei % nj = 0
                     r*ni + ei = 1 -> ei % ni = 1

x = a1*e1 + a2*e2 + ... + ak*ek

// ax = 1(mod n)
Long modular_inverse(Long a, Long n){
    EuclidReturn aux = Extended_Euclid(a,n);
    return ((aux.u/aux.d)%n+n)%n;
}

// rem y mod tienen el mismo numero de elementos
long long chinese_remainder(vector<Long> rem, vector<Long> mod){
    long long ans = rem[0],m = mod[0];
    int n = rem.size();
  
    for(int i=1;i<n;++i){
        int a = modular_inverse(m,mod[i]);
        int b = modular_inverse(mod[i],m);
        ans = (ans*b*mod[i]+rem[i]*a*m)%(m*mod[i]);
        m *= mod[i];
    }
  
    return ans;
}


Chinese Remainder Theorem: Strong Form 
======================================
(thanks to https://forthright48.com/2017/11/chinese-remainder-theorem-part-2-non-coprime-moduli.html)

Given two sequences of numbers A=[a1,a2,…,an] and M=[m1,m2,…,mn], a solution to x exists for the following n congrunce equations:

x≡a1(mod m1)
x≡a2(mod m2)
…
x≡an(mod mn)


if, ai≡aj (mod GCD(mi,mj)) and the solution will be unique modulo L=LCM(m1,m2,…,mn)

Implementation O(n * log(L)):

// tested on https://open.kattis.com/problems/generalchineseremainder

/**
    A CRT solver which works even when moduli are not pairwise coprime
    1. Add equations using addEquation() method
    2. Call solve() to get {x, N} pair, where x is the unique solution modulo N. (returns -1, -1 if no solution)
    Assumptions:
        1. LCM of all mods will fit into long long.
*/
class ChineseRemainderTheorem {
    typedef long long vlong;
    typedef pair<vlong,vlong> pll;
    typedef __int128 overflowtype;
    //typedef long long overflowtype;

    /** CRT Equations stored as pairs of vector. See addEquation()*/
    vector<pll> equations;

public:
    void clear() {
        equations.clear();
    }

    /** Add equation of the form x = r (mod m)*/
    void addEquation( vlong r, vlong m ) {
        equations.push_back({r, m});
    }
    pll solve() {
        if (equations.size() == 0) return {-1,-1}; /// No equations to solve

        vlong a1 = equations[0].first;
        vlong m1 = equations[0].second;
        a1 %= m1;
        /** Initially x = a_0 (mod m_0)*/

        /** Merge the solution with remaining equations */
        for ( int i = 1; i < equations.size(); i++ ) {
            vlong a2 = equations[i].first;
            vlong m2 = equations[i].second;

            EuclidReturn euclidReturn1 = Extended_Euclid(m1, m2);
            vlong g = euclidReturn1.d;
            if ( a1 % g != a2 % g ) return {-1,-1}; /// Conflict in equations

            /** Merge the two equations*/
            vlong p, q;
            EuclidReturn euclidReturn = Extended_Euclid(m1/g, m2/g);
            p = euclidReturn.u;
            q = euclidReturn.v;

            vlong mod = m1 / g * m2;
            vlong x = ( (overflowtype)a1 * (m2/g) % mod *q % mod + (overflowtype)a2 * (m1/g) % mod * p % mod ) % mod;

            /** Merged equation*/
            a1 = x;
            if ( a1 < 0 ) a1 += mod;
            m1 = mod;
        }
        return {a1, m1};
    }
};