
// tested on https://www.spoj.com/problems/POLYMUL/
// multiply two polynomials (use the multiply function) O(n * log(n))
//CDC_MOREFB
#define MOD 99991LL

typedef long double ld;
typedef vector< ld > vld;
typedef vector< vld > vvld;
typedef long long ll;
typedef pair< int , int > pii;
typedef vector< int > vi;
typedef vector< vi > vvi;

ld PI = acos( (ld)(-1.0) );
ll pow( ll a , ll b , ll c ){
	ll ans = 1;
	while( b ){
		if( b & 1 ) ans = (ans * a)%c;
		a = (a * a)%c;
		b >>= 1;
	}
	return ans;
}
ll mod_inv( ll a , ll p ){ return pow(a , p - 2 , p);}

typedef complex<ld> base;
 
void fix( base &x ){
	if(abs(x.imag()) < 1e-16 ){
		x = base( (((ll)round(x.real()))%MOD + MOD)%MOD , 0);
	}
}
void fft (vector<base> & a, bool invert) {
	int n = (int) a.size();
 
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
 
	for (int len=2; len<=n; len<<=1) {
		ld ang = 2.0 * PI /len * (invert ? -1 : 1);
		base wlen (cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w (1);
			for (int j=0; j<len/2; ++j) {
				base u = a[i+j],  v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}
void multiply (const vector<ld> & a, const vector<ld> & b, vector<ld> & res) {
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
 
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	
	fft (fa, true);
 
	res.resize (n);
	for (size_t i=0; i<n; ++i){
		// res[i] = (((ll)round( fa[i].real() ))%MOD + MOD)%MOD;
        res[i] = ((ll)round( fa[i].real() ));
	}
}

void impr( vi &x ){
	REP( i , SZ(x) ) printf( "%d%c" , x[ i ] , (i + 1 == SZ(x)) ? 10 : 32 );
}

vld rec( vvld &T , int lo , int hi ){
	if( lo == hi ) return T[ lo ];
	int mid = (lo + hi) >> 1;
	vld L = rec( T , lo , mid );
	vld R = rec( T , mid + 1 , hi );
	vld X;
	multiply( L , R , X );
	return X;
}
ll solve( ll base , vi &x , int n , int k ){
	// p( x ) = (x + base^v[0]) * ( x + base ^ v[1] ) ....
	vvld T( n );
	REP( i , n )
		T[ i ] = { (ld)pow(base , x[ i ] , MOD) , (ld)1.0 };

	vld v = rec( T , 0 , n - 1 ); 
	ld target = v[ n - k ];

	ll num = (((ll)round( target ))%MOD + MOD)%MOD;
	return num;
}

int main(){
	ll A = 55048LL , B = 44944LL , C = 22019LL;
	//f( n ) = C(A^n - B^n)
	int n , K;
	while( sc( n ) == 1 ){
		sc( K );
		vi x( n );
		REP( i , n ) sc( x[ i ] );
		
		ll SA = solve( A , x , n , K );
		ll SB = solve( B , x , n , K );
		printf( "%lld\n" , (C * (SA - SB + MOD)%MOD)%MOD );
	}
}