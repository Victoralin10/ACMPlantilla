REP( i , n ) id[i] = i ; // init
int Find( int x ){ return id[ x ] = (id[ x ] == x ? x : Find( id[ x ] ) );}
void Union(int x, int y) {id[Find(x)] = Find(y);} // Find( x ) != Find( y )
//  with path compression
REP( i , SZ ) parent[i] = i , rank[i] = 1;
void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);
	if(pa != pb)
	{
		if(rank[pa] < rank[pb]) parent[pa] = pb;
		else if(rank[pa] > rank[pb]) parent[pb] = pa;
		else
		{
			parent[pb] = pa;
			rank[pa]++;
		}
	}
}