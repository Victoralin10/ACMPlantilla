/************************************/
const long long isQuery = -(1LL<<62);

struct Line {
	long long m, b;
	
	mutable multiset<Line>::iterator it, end;
	const Line* Next(multiset<Line>::iterator it) const {
		return (++it == end ? NULL: &*it);
	}
	bool operator < (const Line &curr) const {
		if(curr.b != isQuery) {
			return m < curr.m;
		}
		long long X = curr.m;
		const Line *nxt = Next(it);
		return (!nxt) ? false : b - nxt->b < (nxt->m - m)*X;
	}
};

struct HullDynamic: public multiset<Line> {
	bool bad(iterator curr) {
		iterator nxt = next(curr);
		if(curr == begin()) {
			if(nxt == end()) {
				return false;
			}
			return (curr->m == nxt->m) && (curr->b <= nxt->b);
		}
		iterator prv = prev(curr);
		if(nxt == end()) {
			return (prv->m == curr->m) && (curr->b <= prv->b);
		}
		return 1.0L*(prv->b - curr->b)*(nxt->m - curr->m) >= 1.0L*(curr->m - prv->m)*(curr->b - nxt->b); // (b1 - b2)/(m2 - m1) = x (coordenada x de la interseccion de L1 y L2)
	}
	void add(long long m, long long b) {
		iterator curr = insert((Line){m, b});
		curr->it = curr;
		curr->end = end();
		if(bad(curr)) {
			erase(curr);
			return;
		}
		for( ; next(curr) != end() && bad(next(curr)); erase(next(curr)));
		for( ; prev(curr) != begin() && bad(prev(curr)); erase(prev(curr)));
	}
	long long f(long long x) {
		Line L = *lower_bound((Line){x, isQuery});
		return L.m*x + L.b;
	}
};

/************************************/