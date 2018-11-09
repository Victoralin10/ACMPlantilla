/************************************/
double ts() {
	double l = -INF, r = INF;
	int nroIter = 2*(log2((r - l)/p) + 5);
	for (int i = 0; i < nroIter; i ++) {
		double me1 = l + (r - l)/3;
		double me2 = r - (r - l)/3;
		if (f(me1) < f(me2)) r = me2;
		else l = me1;
	}
	return f(l) ;
}
/************************************/
int ts() {
	int l = -INF;
	int r = INF;
	while (l < r) {
		int me1 = l + (r - l)/3;
		int me2 = r - (r - l)/3;
		if (f(me1) < f(me2)) r = me2 - 1;
		else l = me1 + 1;
	}
	return f(l) ;
}
/************************************/
// funcion cuadratica ++++++ (-) ++++++
// hallar f( x ) minimo 
//		if( f( me1 ) < f( me2 ) ) r = me2 - 1 ;

// funcion cuadratica ------ (+) ------
// hallar f( x ) maximo 
//		if( f( me1 ) < f( me2 ) ) l = me1 + 1 ;