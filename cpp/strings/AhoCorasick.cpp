// Plan-chotaV2.cpp
// with adyancency list
// tested on https://www.spoj.com/problems/SUB_PROB/

const int ND = (int)2e6 + 6; // number of nodes
vector<int> V[ ND ]; // V[i] is the list of id's of words in the node i
vector< pair< char , int > > trie[ND];
int T[ ND ] , Node ; // T is the fallback table

inline int getNode( int node , char c )
{
	for (auto o : trie[node] )
		if( o.first == c )return o.second;
	return 0;	
}
void add( char *s , int id )
{
	int ns = strlen( s ) , p = 0 ;
	REP( i , ns )
	{
		int v = getNode( p , s[i] );
		if( !v )
		{
			trie[p].push_back( make_pair( s[i] , Node ) );
			p = Node++;
		}
		else p = v;
	}
	V[ p ].push_back( id );
}

void aho()
{
	queue< int >Q;
	for (auto o : trie[0] ) {
		Q.push( o.second ) , T[ o.second ] = 0;
    }
	while( !Q.empty() )
	{
		int u = Q.front();
		Q.pop();
        for (auto o : trie[u]) {
			int v = o.second;
			char c = o.first;
			int p = T[u];
			while( p && getNode( p , c ) == 0 )p = T[p];
			p = getNode( p , c );
			T[ v ] = p;
			Q.push( v );
            for (auto q : V[ T[v] ]) {
                V[ v ].push_back( q );
            }
		}
	}
}

const int M = 1000 + 3; // number of words (patterns to search for)
const int N = 100000 + 5; // number of chars in the haystack
bool ans[ M ];

int main()
{
	char s[ N ] , t[ M ];
	int n;
	scanf( "%s%d" , s , &n );
	Node = 1;
	REP( i , n ) scanf( "%s" , t ) , add( t , i );
	int ns = strlen( s );
	aho();
	int p = 0;
	REP( i , ns )
	{
		char c = s[i];
		while( p && getNode( p , c ) == 0 ) p = T[p];
		p = getNode( p , c );

        for (auto o : V[p]) {
            ans[o] = 1;
        }
	}
	REP( i , n )puts( (ans[i]?"Y":"N") );
}