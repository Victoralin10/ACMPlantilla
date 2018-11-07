
struct Pto {
    Long x=0, y=0;
    Pto(){}
    Pto(Long x, Long y): x(x), y(y){}
    Pto ort() { return Pto(-y, x); }
    Long mod2() { return x*x + y*y; }
    Pto operator +(const Pto &p) const { return Pto(x + p.x, y + p.y); }
    Pto operator -(const Pto &p) const { return Pto(x - p.x, y - p.y); }
    Pto operator *(Long k) const { return Pto(x*k, y*k); }
    Long operator *(const Pto &p) const { return x*p.x + y*p.y; }
    Long operator ^(const Pto &p) const { return x*p.y - y*p.x; }
    bool operator <(const Pto &p) const { return x==p.x?y<p.y:x<p.x; }
    bool operator ==(const Pto &p) const { return x==p.x && y==p.y; }
    bool operator !=(const Pto &p) const { return x!=p.x || y!=p.y; }
};

vector <Pto> chull(vector <Pto> &pts) {
    if (pts.size() < 3) {
        return pts;
    }

    Pto _ref = *min_element(all(pts), [](const Pto &a, const Pto &b) { 
        return a.y==b.y?a.x<b.x:a.y<b.y;
    });

    sort(all(pts), [_ref](const Pto &a, const Pto &b) {
        Pto ra = a - _ref, rb = b - _ref;
        Long ar = ra^rb;
        return ar==0?ra.mod2()<rb.mod2():ar>0;
    });

    vector <Pto> ans;
    int i = 0, s;
    while (i < SZ(pts)) {
        s = SZ(ans);
        if (s > 1 && ((pts[i] - ans[s-1])^(ans[s-2] - ans[s-1])) <= 0) ans.pop_back(); // < 0
        else ans.push_back(pts[i++]);
    }

    return ans;
}

bool isConvex(vector <Pto> &pts) {
    int cnt1 = 0, cnt2 = 0, n = SZ(pts);
    REP(i, n) {
        Pto &a = pts[i], &b = pts[(i+1)%n], &c = pts[(i+2)%n];
        Long ar=(c-b)^(a - b);
        if (ar < 0) cnt1++;
        else if (ar > 0) cnt2++;
    }
    return !cnt1 || !cnt2;
}

Long area(vector <Pto> &pts) {
    Long ans = 0;
    int n = SZ(pts);
    REPR(i, 1, n) {
        ans += pts[i]^pts[i-1];
    }
    return abs(ans);
}