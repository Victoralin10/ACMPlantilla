Matrix powers:
If A is the adjacency matrix of the directed or undirected graph G, 
then the matrix A^n (i.e., the matrix product of n copies of A) has an interesting interpretation: 
the element (i, j) gives the number of (directed or undirected) walks of length n from vertex i to vertex j. 
If n is the smallest nonnegative integer, such that for some i, j, the element (i, j) of A^n is positive, 
then n is the distance between vertex i and vertex j. 
This implies, for example, that the number of triangles in an undirected graph G is exactly the trace of A^3 
divided by 6.