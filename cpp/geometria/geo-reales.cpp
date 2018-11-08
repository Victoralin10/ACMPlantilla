#include<bits/stdc++.h>
#define REP(i,n) for (int i = 0; i < (n); i++)
#define FOR(i,ini,n) for (int i = (ini); i < (n); i++)
#define SZ(a) ((int)a.size())
#define endl "\n"
#define CLR(a, v) memset(a, v, sizeof(a))
#define ALL(v) v.begin(),v.end()
#define sc(x) scanf("%d", &(x))
using namespace std;

typedef long long Long;
typedef long double Double;
const Double EPS = 1e-8;

struct Pto {
    Double x=0, y=0;
    Pto(){}
    Pto(Double x, Double y): x(x), y(y){}

    Double mod2() { return x*x + y*y; }
    Double mod() { return sqrt(mod2()); }
    Pto ort() { return Pto(-y, x); }
    Pto unit() { Double k = mod(); return Pto(x/k, y/k); }
    Pto operator +(const Pto &p) const { return Pto(x + p.x, y + p.y); }
    Pto operator -(const Pto &p) const { return Pto(x - p.x, y - p.y); }
    Pto operator *(Double k) const { return Pto(x*k, y*k); }
    Pto operator /(Double k) const { return Pto(x/k, y/k); }
    Double operator *(const Pto &p) const { return x*p.x + y*p.y; }
    Double operator ^(const Pto &p) const { return x*p.y - y*p.x; }
    bool operator <(const Pto &p) const { return fabs(x-p.x)<EPS?y<p.y:x<p.x; }
    bool operator ==(const Pto &p) const { return fabs(x-p.x)<EPS && fabs(y-p.y)<EPS; }
    bool operator !=(const Pto &p) const { return fabs(x-p.x)>EPS || fabs(y-p.y)>EPS; }
};

// Positivo si anti-horario
Double area(vector <Pto> &pts) {
    Double ans = 0;
    int n = SZ(pts);
    FOR(i,1,n) {
        ans += pts[i]^pts[i-1];
    }
    return abs(ans);
}

// a,b,c
Double area(const Pto &a, const Pto &b, const Pto &c) {
    return (c - b)^(a - b);
}

bool isConvex(vector <Pto> &pts) {
    int cnt1 = 0, cnt2 = 0, n = SZ(pts);
    REP(i, n) {
        Pto &a = pts[i], &b = pts[(i+1)%n], &c = pts[(i+2)%n];
        Double ar = area(a,b,c);
        if (ar < -EPS) cnt1++;
        else if (ar > EPS) cnt2++;
    }
    return !cnt1 || !cnt2;
}

struct Segm {
    Pto s, e;
    Segm(){}
    Segm(Pto s, Pto e):s(s), e(e){}
    Double len() { return (e-s).mod(); }
    Pto dir() const { return e-s; }
};

bool areParallel(const Segm &a, const Segm &b) {
    return fabs(a.dir()^b.dir()) < EPS;
}

Pto lineIntersect(const Segm &a, const Segm &b) {
    assert(!areParallel(a, b));
    Pto bort = b.dir().ort();
    double r = ((b.s - a.s)*bort)/(b.dir()*bort);
    return a.s + a.dir()*r;
}

bool onLine(const Segm &a, const Pto &b) {
    return fabs((a.s - b)^(a.e - b)) < EPS;
}

bool onSegment(const Segm &a, const Pto &b) {
    if (!onLine(a, b)) return false;
    return (a.s - b)*(a.e - b) < EPS;
}

bool segmIntersect(const Segm &a, const Segm &b) {
    if (areParallel(a, b)) return false;
    Pto I = lineIntersect(a, b);
    return onSegment(a, I) && onSegment(b, I);
}

// Proyeccion de un punto sobre una recta
Pto proy(const Segm &a, const Pto &b) {
    if (onLine(a, b)) return b;
    Pto se = a.dir();
    Double r = ((b - a.s)*se)/(se*se);
    return a.s + se*r;
}

// Reflexion de un punto respecto a una recta
Pto reflect(const Segm &a, const Pto &b) {
    if (onLine(a, b)) return b;
    Pto py = proy(a, b);
    return py*2 - b;
}

// Poligono convexo, en sentido antihorario
bool isInPoligon(vector <Pto> &pol, Pto p) {
    int hi = SZ(pol)-1, lo=1, mid;
    Pto pp0 = p - pol[0];
    if ((pp0^(pol[lo] - pol[0])) > EPS
        || ((pol[hi] - pol[0])^pp0) > EPS) return false;

    while (hi - lo > 1) {
        mid = (hi + lo)>>1;
        if ((pp0^(pol[mid] - pol[0])) > EPS) hi = mid;
        else lo = hi;
    }

    return ((pol[hi] - pol[lo])^(p - pol[0])) > EPS;
}

vector <Pto> chull(vector <Pto> &pts) {
    if (pts.size() < 3) {
        return pts;
    }

    Pto _ref = *min_element(ALL(pts), [](const Pto &a, const Pto &b) { 
        return abs(a.y-b.y)<EPS?a.x<b.x:a.y<b.y;
    });

    sort(ALL(pts), [_ref](const Pto &a, const Pto &b) {
        Pto ra = a - _ref, rb = b - _ref;
        Long ar = ra^rb;
        return abs(ar)<EPS?ra.mod2()<rb.mod2():ar>0;
    });
    
    vector <Pto> ans;
    int i = 0, s;
    while (i < SZ(pts)) {
        s = SZ(ans);
        if (s > 1 && ((pts[i] - ans[s-1])^(ans[s-2] - ans[s-1])) <= EPS) ans.pop_back(); // < -EPS
        else ans.push_back(pts[i++]);
    }
    return ans;
}
