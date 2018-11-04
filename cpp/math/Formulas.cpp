
// Series conocidas 
// A000217 	 Triangular numbers: a(n) = C(n+1,2) = n(n+1)/2 = 0+1+2+...+n. 0, 1, 3, 6, 10, 15, 21, 28 ...( 0 , 0 + 1 , 0 + 1 + 2 ,...) 
// f* = (-1+sqrt( 8*x + 1 ))/2
// A000292 Tetrahedral (or triangular pyramidal) numbers: a(n) = C(n+2,3) = n*(n+1)*(n+2)/6. 0, 1, 4, 10, 20, 35, 56, 84, 120.... ( 0 , 0 + 1 , 0 + 1 + 3 , 0 + 1 + 3 + 6 , ..)
// A000010 Euler totient function phi(n): count numbers <= n and prime to n.  1, 1, 2, 2, 4, 2, 6, 4, 6, 4, 10, 4, 12, 6, 8, 8, 16, 6, 18, 8, 12, 10, 22, 8, 20, 12, 18, 12, 28, 8, 30, 16, 20, 16, 24, 12, 36, 18, 24, 16, 40, 12, 42, 20, 24, 22, 46, 16, 42, 20, 32, 24, 52, 18, 40, 24, 36, 28, 58, 16, 60, 30, 36, 32, 48, 20, 66, 32, 44
// binomial = combination
// A000108	Catalan numbers: C(n) = binomial(2n,n)/(n+1) = (2n)!/(n!(n+1)!). Also called Segner numbers.1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420, 24466267020, 91482563640, 343059613650, 1289904147324, 4861946401452, 18367353072152, 69533550916004, 263747951750360, 1002242216651368, 3814986502092304
/**

Let Cn be Catalan number of n:
Cn = binomial(2n, n)  - binomial(2n, n + 1)
* Cn is the number of Dyck words of length 2n. A Dyck word is a string consisting of n X's and n Y's such that no initial 
segment of the string has more Y's than X's. For example, the following are the Dyck words of length 6:
XXXYYY     XYXXYY     XYXYXY     XXYYXY     XXYXYY.
* Re-interpreting the symbol X as an open parenthesis and Y as a close parenthesis, Cn counts the number of expressions containing n pairs of parentheses which are correctly matched:
((()))     ()(())     ()()()     (())()     (()())
* Cn is the number of different ways n + 1 factors can be completely parenthesized (or the number of ways of associating n applications of a binary operator). For n = 3, for example, we have the following five different parenthesizations of four factors:
((ab)c)d     (a(bc))d     (ab)(cd)     a((bc)d)     a(b(cd))

* Successive applications of a binary operator can be represented in terms of a full binary tree. (A rooted binary tree is full if every vertex has either two children or no children.) It follows that Cn is the number of full binary trees with n + 1 leaves
* Cn is the number of monotonic lattice paths along the edges of a grid with n × n square cells, which do not pass above the diagonal. A monotonic path is one which starts in the lower left corner, finishes in the upper right corner, and consists entirely of edges pointing rightwards or upwards. Counting such paths is equivalent to counting Dyck words: X stands for "move right" and Y stands for "move up".
* A convex polygon with n + 2 sides can be cut into triangles by connecting vertices with non-crossing line segments (a form of polygon triangulation). The number of triangles formed is n and the number of different ways that this can be achieved is Cn. The following hexagons illustrate the case n = 4:
* Cn is the number of stack-sortable permutations of {1, ..., n}. A permutation w is called stack-sortable if S(w) = (1, ..., n), where S(w) is defined recursively as follows: write w = unv where n is the largest element in w and u and v are shorter sequences, and set S(w) = S(u)S(v)n, with S being the identity for one-element sequences.
* Cn is the number of permutations of {1, ..., n} that avoid the permutation pattern 123 (or, alternatively, any of the other patterns of length 3); that is, the number of permutations with no three-term increasing subsequence. For n = 3, these permutations are 132, 213, 231, 312 and 321. For n = 4, they are 1432, 2143, 2413, 2431, 3142, 3214, 3241, 3412, 3421, 4132, 4213, 4231, 4312 and 4321.
* Cn is the number of noncrossing partitions of the set {1, ..., n}. A fortiori, Cn never exceeds the nth Bell number. Cn is also the number of noncrossing partitions of the set {1, ..., 2n} in which every block is of size 2. The conjunction of these two facts may be used in a proof by mathematical induction that all of the free cumulants of degree more than 2 of the Wigner semicircle law are zero. This law is important in free probability theory and the theory of random matrices.
* Cn is the number of ways to tile a stairstep shape of height n with n rectangles.
* Cn is the number of ways that the vertices of a convex 2n-gon can be paired so that the line segments joining paired vertices do not intersect. This is precisely the condition that guarantees that the paired edges can be identified (sewn together) to form a closed surface of genus zero (a topological 2-sphere).


*/


// A000169  Number of labeled rooted trees with n nodes: n^(n-1).       1, 2, 9, 64, 625, 7776, 117649, 2097152, 43046721, 1000000000, 25937424601, 743008370688, 23298085122481, 793714773254144, 29192926025390625, 1152921504606846976, 48661191875666868481, 2185911559738696531968, 104127350297911241532841, 5242880000000000000000000
// A006717  Number of toroidal semi-queens on a (2n+1) X (2n+1) board.  1, 3, 15, 133, 2025, 37851, 1030367, 36362925, 1606008513, 87656896891, 5778121715415, 452794797220965, 41609568918940625

//Derangement In combinatorial mathematics, a derangement is a permutation of the elements of a set such that none of the elements appear in their original position.
// http://en.wikipedia.org/wiki/Derangement
// DP[ n ] = ( n - 1 ) * ( DP[ n - 1 ] + DP[ n - 2 ] ) , DP[ 0 ] = 1 , DP[ 1 ] = 0;   11282_UVA