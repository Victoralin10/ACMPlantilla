#include<bits/stdc++.h>
using namespace std ;

const int N = 2e5 + 2 ;
const int logN = log2( N ) + 2 ;
const int INF = 1e9 + 7 ;

/************************************/
int n , len ;
string s ;
int Rank[ N ] ;
int sa[ N ] ;

inline bool sufCmp( int i , int j ) {
	return Rank[ i + len ] < Rank[ j + len ] ;
}

void fixRank( int l , int r ) {
	int lastP = Rank[ sa[ l ] + len ] ;
	for( int i = l , cnt = l ; i < r ; i ++ ) {
		int curP = Rank[ sa[ i ] + len ] ;
		if( lastP != curP && !( l <= lastP && curP < r ) ) {
			lastP = curP ;
			cnt = i ;
		}
		Rank[ sa[ i ] ] = cnt ;
	}
}

void buildSA() {
	n = s.size() ;
	Rank[ n ] = -1 ;
	int i , j , abc[ 256 ] ;
	for( i = 0 ; i < 256 ; i ++ ) abc[ i ] = 0 ;
	for( i = 0 ; i < n ; i ++ ) abc[ int( s[ i ] ) ] ++ ;
	for( i = 1 ; i < 256 ; i ++ ) abc[ i ] += abc[ i - 1 ] ;
	for( i = 0 ; i < n; i ++ ) sa[ -- abc[ int( s[ i ] ) ] ] = i ;
	for( i = n - 1 ; i >= 0 ; i -- ) Rank[ i ] = abc[ int( s[ i ] ) ] ;
	for( len = 1 ; len < n ; len <<= 1 ) {
   		for( int i = 0 , j = 1 ; i < n ; i = j ++ ) {
   			for( ; j < n && Rank[ sa[ i ] ] == Rank[ sa[ j ] ] ; j ++ ) ;
			if( i + 1 == j ) continue ;
			sort( sa + i , sa + j , sufCmp ) ;
			fixRank( i , j ) ;
		}
	}
}

/************************************/
int L[ N ] ;

void buildL() {
	memset( L , 0 , sizeof L ) ;
	for( int i = 0 , len = 0 ; i < n ; i ++ ) {
		if( Rank[ i ] == 0 ) continue ;
		int j = sa[ Rank[ i ] - 1 ] ;
		for( ; s[ i + len ] == s[ j + len ] ; len ++ ) ;
		L[ Rank[ i ] - 1 ] = len ;
		if( len ) len -- ;
	}
}

/************************************/
int st[ N ][ logN ] ;

void buildST() {
	for( int i = 0 ; i < n ; i ++ ) {
		st[ i ][ 0 ] = L[ i ] ;
	}
	for( int loglen = 1 , len = 2 ; len <= n ; loglen ++ , len <<= 1 ) {
		for( int i = 0 ; i + len <= n ; i ++ ) {
			st[ i ][ loglen ] = min( st[ i ][ loglen - 1 ] , st[ i + len/2 ][ loglen - 1 ] ) ;
		}
	}
}

int query( int i , int j ) {
	if( i == j ) return n - sa[ i ] ;
	j -- ;
	int nroLen = log2( j - i + 1 ) ;
	int len = 1 << nroLen ;
	return min( st[ i ][ nroLen ] , st[ j - len + 1 ][ nroLen ] ) ;
}

/************************************/
int posId[ 12 ] ;
int Id[ N ] ;
int k ;

void Read() {
	string word ;
	cin >> k ;
	for( int i = 0 ; i < k ; i ++ ) {
		cin >> word ;
		int m = word.size() ;
		for( int it = 0 ; it < m ; it ++ ) {
			Id[ n + it ] = i ;
		}
		s += word ;
		s += '+' ;
		n = s.size() ;
	}
}

/************************************/
void Clear() {
	memset( posId , -1 , sizeof posId ) ;
	s.clear() ;
	n = 0 ;
}

int main() {
	int t ;
	cin >> t ;
	while( t -- ) {
		Clear() ;
		Read() ;
		buildSA() ; /* construccion Suffix Array */
		buildL() ; /* construccion LCP */
		buildST() ;
		int ans = 0 ;
		for( int i = k ; i < n ; i ++ ) {
			posId[ Id[ sa[ i ] ] ] = i ;
			int last = INF ;
			for( int id = 0 ; id < k ; id ++ ) {
				last = min( last , posId[ id ] ) ;
			}
			if( last == -1 ) continue ;
			ans = max( ans , query( last , i ) ) ;
		}
		cout << ans << '\n' ;
	}
	
	return 0 ;
}

// * sa[ i^th ] => index
// * Rank[ index ] => i^th
// * L[ ith ] = LCP( ith , ith + 1 )
// * LCP( i , j ) = min( L[ ith ] , L[ ith + 1 ] ,... , L[ jth - 1 ] )
// * Nro de Substring distintos : n*( n + 1 )/2 - Sum[i:1->n]( L[ i ] )