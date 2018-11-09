map<int,int> comp;
int orig[N + 2];
set<int> nums;

void compress() {
	int y = 0;
	for (int x: nums) {
		comp[x] = y;
		orig[u] = x;
		y ++;
	}
}