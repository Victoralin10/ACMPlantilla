/************************************/
struct Node {
	Node *child[26];
	string value;
	bool ed;
	Node() {
		ed = false;
		for (int i = 0; i < 26; i ++) {
			child[i] = NULL;
		}
	}
};

void add(Node *node, string &word, int it = 0) {
	if (it == word.size()) {
		node->value = word;
		node->ed = true;
		return;
	}
	int c = word[it] - 'a';
	if (!node->child[c]) {
		node->child[c] = new Node;
	}
	add(node->child[c], word, it + 1);
}

vector<string> words;

void search(Node *node, string &word, int it = 0) {
	if (it >= word.size() && node->ed) {
		words.push_back(node->value);
	}
	for (int c = 0; c < 26; c ++) {
		if (!node->child[c]) continue;
		if (it < word.size() && word[it] - 'a' != c) continue;
		search(node->child[c], word, it + 1);
	}
}

/************************************/
Node *trie = new Node;