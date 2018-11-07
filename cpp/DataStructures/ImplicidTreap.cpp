
typedef struct Nd * pnd;
struct Nd {
    int cnt, pri, val;
    pnd l, r;
    bool rev;
    Nd(int val, int pri):cnt(1),pri(pri),val(val),l(NULL),r(NULL),rev(false){}
};


inline int cnt(pnd t) { return t?t->cnt:0; }
inline void upd_cnt(pnd t) { if (t)t->cnt=1+cnt(t->l)+cnt(t->r); }

inline void rev(pnd t) {
    if (t) {
        t->rev = !t->rev;
    }
}

inline void push(pnd t) {
    if (t && t->rev) {
        t->rev=false;
        rev(t->l), rev(t->r);
        swap(t->l, t->r);
    }
}

void print(pnd t, bool end=true) {
    if (t) {
        push(t);
        print(t->l, false);
        if (t->l)cout<<" ";
        cout<<t->val;
        if(t->r)cout<<" ";
        print(t->r, false);
    }
    if (end) cout << endl;
}

void merge(pnd &t, pnd l, pnd r) {
    if (!l || !r) return void(t=l?l:r);
    push(l), push(r);
    if (l->pri > r->pri) merge(l->r, l->r, r), t=l;
    else merge(r->l, l, r->l), t=r;
    upd_cnt(t);
}

void split(pnd t, int i, pnd &l, pnd &r) {
    if (!t) return void(l=r=NULL);
    push(t);
    if (cnt(t->l) < i) split(t->r,i - cnt(t->l) -1, t->r, r),l=t;
    else split(t->l, i, l, t->l), r=t;
    upd_cnt(l), upd_cnt(r);
}

void rev(pnd &t, int i, int j) {
    pnd a, b, c;
    split(t, j+1, b, c);
    split(b, i, a, b);
    rev(b);
    merge(t, a, b);
    merge(t, t, c);
}