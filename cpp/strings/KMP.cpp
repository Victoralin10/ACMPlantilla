vector<int> F ;
string T ;
string P ;

void buildF() {
	F = vector<int> ( P.size() , 0 ) ;
	for( int itP = 1 , len = 0 ; itP < P.size() ; itP ++ ) {
		for( ; len != -1 && P[ itP ] != P[ len ] ; len = len ? F[ len - 1 ] : -1 ) ;
		F[ itP ] = ++ len ;
	}
}

vector<int> kmp() {
	vector<int> index ;
	buildF() ;
	for( int itT = 0 , itP = 0 ; itT < T.size() ; itT ++ ) {
		for( ; itP != -1 && T[ itT ] != P[ itP ] ; itP = itP ? F[ itP - 1 ] : -1 ) ;
		if( P.size() == ++ itP ) {
			index.push_back( itT - itP ) ;
			itP = F[ itP - 1 ] ;
		}
	}
	return index ;
}

// *borde: prefijo y sufijo a la vez de una cadena 
// *un borde no puede ser toda la cadena
// F[ i ] : longitud del borde mas largo de T[ 0 .. i ]