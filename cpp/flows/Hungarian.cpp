// tested on https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=&problem=1687&mosmsg=Submission+received+with+ID+22270778
// 10746 - Crime Wave - The Sequel
// para problemas rectangulares :  O (n ^ 2 * m)
struct HungarianAlgorithm {
    typedef Double costtype;
    const costtype INF = 1e10;
    
    // internals
    int n, m;
    vector<costtype> u, v;
    vector<int> p, way;
    
    HungarianAlgorithm() {}

    // returns the matches of the left set (of size n)
    // given the matrix of costs 'a' (n * m)
    vector<int> solve(vector<vector<costtype> > &a) {
        n = (int)a.size();
        if (n == 0) {
            return vector<int>(0); // empty
        }
        m = (int)a[0].size();

        u = vector<costtype>(n + 1);
        v = vector<costtype>(m + 1);
        p = way = vector<int>(m + 1);
        for (int i=1; i<=n; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<costtype> minv (m+1, INF);
            vector<char> used (m+1, false);
            do {
                used[j0] = true;
                int i0 = p[j0],  j1;
                costtype delta = INF;
                for (int j=1; j<=m; ++j)
                    if (!used[j]) {
                        costtype cur = a[i0 - 1][j - 1]-u[i0]-v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                for (int j=0; j<=m; ++j)
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        vector<int> ans (n);
        for (int j=1; j<=m; ++j) {
            if (p[j] == 0) { // j - th element (1-indexed) is not matched with anyone in left set
                ;
            } else {
                ans[p[j] - 1] = j - 1;
            }
        }
        return ans;
    }
}hung;

vector<vector<Double> > a;
int main(){
    int n, m;
    while (sc(n) == 1) {
        sc(m);
        if (!n) break;

        a = vector<vector<Double> >(n);
        REP (i, n) {
            a[i] = vector<Double>(m);
            REP (j, m) {
                cin >> a[i][j];
            }
        }
        auto ans = hung.solve(a);
        Double avg = 0;
        REP (i, n) {
            avg += a[i][ans[i]];
        }
        avg /= n;
        
		avg = floor(avg*100.0+0.5+1e-9)/100.0; // never trust printf rounding (do it yourself)
        printf("%.2lf\n", (double)avg);
    }
}