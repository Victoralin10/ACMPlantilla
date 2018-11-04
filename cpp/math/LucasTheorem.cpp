// Generalized lucas theorem
// tested on http://codeforces.com/gym/100637/problem/D
//http://codeforces.com/blog/entry/10271

struct EuclidReturn{
    Long u , v , d;
    EuclidReturn( Long u , Long v, Long d ) : u( u ) , v( v ) , d( d ) {}
};
    
EuclidReturn Extended_Euclid( Long a , Long b){
    if( b == 0 ) return EuclidReturn( 1 , 0 , a );
    EuclidReturn aux = Extended_Euclid( b , a%b );
    Long v = aux.u - (a/b)*aux.v;
    return EuclidReturn( aux.v , v , aux.d );
}

// ax = 1(mod n)
Long modular_inverse( Long a , Long n ){
    EuclidReturn aux = Extended_Euclid( a , n );
    return ((aux.u/aux.d)%n+n)%n;
}

Long chinese_remainder( vector<Long> &rem, vector<Long> &mod ){
	Long ans = rem[ 0 ] , m = mod[ 0 ];
    for( int i = 1 ; i < SZ(rem) ; ++i ){
        int a = modular_inverse( m , mod[ i ] );
        int b = modular_inverse( mod[ i ] , m );
        ans = ( ans * b * mod[ i ] + rem[ i ] * a * m)%( m*mod[ i ] );
        m *= mod[i];
    }
    return ans;
}


void primefact( int n , vector<Long> &p , vector<Long> &e , vector<Long> &pe ){
	for( int i = 2 ; i * i <= n ; ++i ){
		if( n % i == 0 ){
			int exp = 0 , pot = 1;
			while( n % i == 0 ){
				n /= i;
				exp ++;
				pot *= i;
			}
			p.push_back( i ) , e.push_back( exp ) , pe.push_back( pot );
		}
	}
	if( n > 1 ) p.push_back( n ) , e.push_back( 1 ) , pe.push_back( n );
}

Long pow( Long a , Long b , Long c ){
	Long ans = 1;
	while( b ){
		if( b & 1 ) ans = (ans * a)%c;
		a = (a * a)%c;
		b >>= 1;
	}
	return ans;
}
Long factmod( Long n , Long p , Long pe ){
	if( n == 0 ) return 1;
	Long cpa = 1;
    Long ost = 1;
    for( Long i = 1; i <= pe; i++ ){
        if( i % p != 0 ) cpa = (cpa * i) % pe;
        if( i == (n % pe) ) ost = cpa;
    }
    cpa = pow(cpa, n / pe, pe);
    cpa = (cpa * ost) % pe;
    ost = factmod(n / p, p, pe);
    cpa = (cpa * ost) % pe;
    return cpa;
}
Long factst( Long a , Long b ){
	Long ans = 0;
	while( a ){
		ans += a / b;
		a /= b;
	}
	return ans;
}

Long solve( Long n , Long k , Long p , Long e , Long pe ){
	Long np = factmod( n , p , pe );
	Long kp = factmod( k , p , pe );
	Long nkp = factmod( n - k , p , pe );
	Long cnt = factst( n , p ) - factst( k , p ) - factst( n - k , p );
	if( cnt >= e ) return 0;
	Long r = ((np * modular_inverse( kp , pe ))% pe);
	r = (r * modular_inverse( nkp , pe ))%pe;
	REP( i , cnt ) r = (r * p) % pe;
	return r;
}

int main(){
	Long n , k , mod;
	while( cin >> n >> k >> mod ){
		vector<Long> p , e , pe;// pe = p ^ e
		primefact( mod , p , e , pe );
		vector<Long> rem;
		REP( i , SZ( p ) ) rem.push_back( solve( n , k , p[ i ] , e[ i ] , pe[ i ] ) );
		cout << chinese_remainder( rem ,  pe ) << '\n';
	}
}