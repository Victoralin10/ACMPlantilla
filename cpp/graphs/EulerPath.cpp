// Plan-ChotaV2, tested on Codeforces Round #288 (Div. 2)D. Tanya and Password

//Eulerian path reconstruction in directed graph O( E + V )
// same idea is for undirected graph
int next[ MAXE + 5 ] , to[ MAXE + 5 ] , last[ N + 5 ] , E;

void add( int u , int v ){
    next[ E ] = last[ u ] , to[ E ] = v , last[ u ] = E++;
}
bool vis_edge[ MAXE + 5 ];
int res[ MAXE + 5 ] , len;

void solve( int u ){
    for( int e = last[ u ] ; e != -1 ; e = next[ e ] ){
        int v = to[ e ];
        last[ u ] = next[ e ];
        if( vis_edge[ e ] ) break;
        vis_edge[ e ] = true;

        solve( v );
        res[ len++ ] = v;    
    }
} 

bool vis[ N + 5 ];
int in[ N + 5 ] , out[ N + 5 ] , cant;

void dfs( int u ){
    if( vis[ u ] ) return;
    vis[ u ] = 1;

    cant++;
    for( int e = last[ u ] ; e != -1; e = next[ e ] ) dfs( to[ e ] );
}
int used[ N + 5 ];
int main(){
	ios_base :: sync_with_stdio( 0 );
    int n;
    while( cin >> n ){
    	vi nodes ;
        clr( last , -1 );
        E = 0;
		clr( used , 0 );
        REP( i , n ){
        	string s;
            cin >> s;
            int u = s[ 0 ] * 300 + s[ 1 ];
            int v = s[ 1 ] * 300 + s[ 2 ];
            
            add( u , v );
            if( !used[ u ] ) nodes.pb( u ) , used[ u ] = 1;
            if( !used[ v ] ) nodes.pb( v ) , used[ v ] = 1;
            
            in[ v ]++;
            out[ u ]++;
        }
        
        int ip = 0 , ini = -1;
        
        REP( i , SZ( nodes ) ){
            int u = nodes[ i ];
            if( abs( in[ u ] - out[ u ] ) == 1 ) ip++;
            else if( in[ u ] != out[ u ] ) ip = 100; 
            
            if( in[ u ] - out[ u ] == -1 ) ini = u;
            else if( ini == -1 && in[ u ] == out[ u ] ) ini = u;     
        }
        
        cant = 0;
        clr( vis , 0 );
		if( ini != -1 ) dfs( ini );
        if( cant == SZ( nodes ) && ip <= 2 ){
            cout << "YES\n"; 
            len = 0;
            clr( vis_edge , 0 );
            solve( ini );
            
            cout << char( ini / 300 );
            cout << char( ini % 300 );
            for(int i = n - 1; i >= 0; i--) cout << char( res[ i ] % 300 );
            cout << '\n';
        }
        else cout << "NO\n";
    }
}