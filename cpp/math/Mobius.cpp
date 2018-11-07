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

//By marioyc
int N = 15;
int mu[N+1];

void mobius() {
    CLR(mu, 0);
    mu[1] = 1;

    for(int i = 1;i <= N;++i)
        for(int j = 2*i;j <= N;j += i)
            mu[j] -= mu[i];
}
