int trie[N][26];
bool ed[N];
int szTrie = 1;

void add(int node, string &word, int it = 0) {
	if (it == word.size()) {
		ed[node] = true;
		return;
	}
	int c = word[it] - 'a';
	if (!trie[node][c]) {
		trie[node][c] = szTrie ++;
	}
	add(trie[node][c], word, it + 1);
}

/************************************/

int main() {
	string word = "hello" ;
	add( 0 , word , 0 ) ;
	// node 0 is root
}
//N: suma total de caracteres en el diccionario