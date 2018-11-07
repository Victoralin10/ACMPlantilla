// tested on http://codeforces.com/contest/718/submission/34911387
typedef pair<int, int> Pair;

const int MAXN = (int)1e5 + 5;
const int MAXSIZE = 2;
const Long MOD = (Long)1e9 + 7;

const int size = 2;

vector<Long> ar;

struct Matrix
{
	Long X[MAXSIZE][MAXSIZE];

	Matrix ()
	{
        memset(X, 0, sizeof(X));
	}
	Matrix (int k)
	{
		memset(X, 0, sizeof(X));

		for(int i=0; i<size; i++)
			X[i][i] = k;
	}
	void show ()
	{
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << X[i][j] << " ";
			}
			puts("");
		}
	}
} MA;

Matrix operator *(Matrix &A, Matrix &B)
{
	Matrix M;

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			long long tmp = 0;
			for(int k=0; k<size; k++)
				tmp = (tmp + ((A.X[i][k] * B.X[k][j])%MOD))%MOD;
			M.X[i][j] = tmp;
		}
	}

	return M;
}

void mulInplace(Matrix &A, Matrix &B)
{
	Matrix M;

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			long long tmp = 0;
			for(int k=0; k<size; k++)
				tmp = (tmp + ((A.X[i][k] * B.X[k][j])%MOD))%MOD;
			M.X[i][j] = tmp;
		}
	}

    A = M;
}

Matrix pows[64];
bool haspow[64];

Matrix pow(Matrix x, long long n)
{
	Matrix P(1);
    int cnt = 0;
	while(n)
	{
        if (haspow[cnt]) {
            if (n & 1) mulInplace(P, pows[cnt]);
        } else {
            haspow[cnt] = 1;
            if (cnt == 0) pows[cnt] = x;
            else pows[cnt] = pows[cnt - 1] * pows[cnt - 1];

            if (n & 1) mulInplace(P, pows[cnt]);
        }
		n >>= 1;
        cnt++;
	}

	return P;
}

void initA() {
    Matrix m;
    m.X[0][0] = 1;
    m.X[0][1] = 1;
    m.X[1][0] = 1;
    m.X[1][1] = 0;
    MA = m;
}

struct LazyNode{
    //contiene la informacion para actualizar Node
    Matrix m;
	LazyNode()
	{
		//elemento neutro:
        m = Matrix(1);
	}
	void operator +=(LazyNode &ln)
	{
        mulInplace(m, ln.m);
	}
};
void m42(Matrix &m, pair<Long, Long> &f) {
    Long f0 = f.first;
    Long f1 = f.second;
    Long nf0 = (((m.X[0][0]*f0)%MOD) + ((m.X[0][1]*f1)%MOD))%MOD;
    Long nf1 = (((m.X[1][0]*f0)%MOD) + ((m.X[1][1]*f1)%MOD))%MOD;
    f.first = nf0;
    f.second = nf1;
}

struct Node{
    pair<Long, Long> f;
    Node(){
        //elemento neutro:
        f.first = 0;
        f.second = 0;
    }
	void operator +=(LazyNode &ln)
	{
        m42(ln.m, f);
	}
	Node operator+( const Node &a) const {
	    Node c;
		c.f.first = (f.first + a.f.first)%MOD;
		c.f.second = (f.second + a.f.second)%MOD;
	    return c;
	}
};
struct ST{
    Node T[ MAXN * 4 ];
    LazyNode LazyT[ MAXN * 4 ];
    int n;
    ST(){}
    ST( int tam ){
        n = tam;
        build_tree( 0 , 0 , n - 1 );
    }
    // for reusing this structure
    void setSizeAndBuild( int tam ){
        n = tam;
        build_tree( 0 , 0 , n - 1 );
    }
    void build_tree( int node , int a , int b ){
        if( a == b ){
            LazyT[ node ] = LazyNode();
            
            //inicializando el elemento 'a'
            Long po = ar[a];
            pair<Long, Long> ini = make_pair(1, 0);

            Matrix m = pow(MA, po - 1);
            m42(m, ini);
            T[ node ].f = ini;
            return;
        }
        build_tree( ((node<<1) + 1) , a , ((a+b)>>1) ) , build_tree( ((node<<1) + 2) , ((a+b)>>1) + 1  , b );
        T[ node ] = T[ ((node<<1) + 1) ] + T[ ((node<<1) + 2) ];
        LazyT[ node ] = LazyNode();
    }
    void push( int node , int a , int b ){
        T[ node ] += LazyT[ node ];
        if( a != b ){
            LazyT[ node*2 + 1 ] += LazyT[ node ];
			LazyT[ node*2 + 2 ] += LazyT[ node ];
        }

        LazyT[ node ] = LazyNode();
    }
    Node query( int node , int a , int b , int lo , int hi ){
        push( node , a , b );
        if( lo > b || a > hi ) return Node();
        if( a >= lo && hi >= b ) return T[ node ];
        return query( ((node<<1) + 1) , a , ((a+b)>>1) , lo , hi ) + query( ((node<<1) + 2) , ((a+b)>>1) + 1  , b , lo , hi );
    }
    void update( int node , int a , int b , int lo , int hi, const LazyNode& val){
        push( node , a , b );
        if( lo > b || a > hi ) return ;
        if( a >= lo && hi >= b ) {
            LazyT[ node ] = val;
            push( node , a , b );
            return;
        }
        update( ((node<<1) + 1) , a , ((a+b)>>1) , lo , hi , val);
        update( ((node<<1) + 2) , ((a+b)>>1) + 1  , b , lo , hi , val);
        T[ node ] = T[ ((node<<1) + 1) ] + T[ ((node<<1) + 2) ] ;
    }
    Node query( int lo , int hi ){
        return query( 0 , 0 , n - 1 , lo , hi );

    }
    void update( int lo , int hi ,const LazyNode& val){
        update( 0 , 0 , n - 1 , lo , hi , val );
    }
}st;

int main() {
    initA();

    int n, m;
    scanf("%d%d", &n, &m);
    REP (i, n) {
        int x;
        scanf("%d", &x);      
        ar.push_back(x);
    }
	st.setSizeAndBuild(n);

    REP (i, m) {
        int tp, l, r, x;
        scanf("%d%d%d", &tp, &l, &r);
        l--;r--;
        if (tp == 1) {
            scanf("%d", &x);      
            LazyNode ln;
            ln.m = pow(MA, x);
            st.update(l, r , ln);
        } else {
            Node node = st.query(l, r);
            printf("%d\n", (int)node.f.first);
        }
    }
}