vector<int> Z ;
string T ;
string P ;

void zeta( string &U ) {
	Z = vector<int> ( U.size() , 0 ) ;
	for( int i = 1 , l = 0 , r = 0 ; i < U.size() ; i ++ ) {
		if( i <= r ) Z[ i ] = min( Z[ i - l ] , r - i + 1 ) ;
		for( ; i + Z[ i ] < U.size() && U[ Z[ i ] ] == U[ i + Z[ i ] ] ; Z[ i ] ++ ) ;
		if( r < i + Z[ i ] - 1) l = i , r = i + Z[ i ] - 1 ;
	}
}

vector<int> find() {
	string U = P ;
	U.insert( U.end() , T.begin() , T.end() ) ;
	zeta( U ) ;
	vector<int> index ;
	for( int i = P.size() ; i < U.size() ; i ++ ) {
		if( P.size() <= Z[ i ] ) {
			index.push_back( i - P.size() ) ;
		}
	}
	return index ;
}

// Z[ i ] : longitud de la subcadena mas larga que comienza en i y es tambien un prefijo.
// *Z[ 0 ] = 0
// *string = ax10 , Z[ 1 ] = 9 , Z[ 2 ] = 8 ...