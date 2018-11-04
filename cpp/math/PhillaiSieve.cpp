// phill[n] = sum of (for i from 1 to n: gcd(i, n) )
// also : phill[n] = sum of (for d a divisor of n: d * phi(n / d) )
long long phill[ N ] ;

void sievePhillai( int n ) {
	for( int num = 1 ; num <= n ; num ++ ) {
		for( int mult = num ; mult <= n ; mult += num ) {
			phill[ mult ] += 1LL*num*phi[ mult/num ] ;
		}
	}
}