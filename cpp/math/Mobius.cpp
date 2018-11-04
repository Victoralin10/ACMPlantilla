// credits to Bryan

mobius(n) = 1 si n es libre de cuadrados y tiene un n˙mero par de factores primos distintos.
mobius(n) = -1 si n es libre de cuadrados y tiene un n˙mero impar de factores primos distintos.
mobius(n) = 0 si n es divisible por algún cuadrado.

/************************************/
int mobius( int num ) {
	int cantPrimes = fact( num ) ;
	if( cantPrimes == INF ) return 0 ; // INF is a flag for divisible by some square
	return (cantPrimes&1) ? -1 : 1 ;
}

/************************************/