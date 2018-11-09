pair<string,int> Roman[13] = {{"I", 1}, {"IV", 4}, {"V", 5}, {"IX", 9}, {"X", 10}, {"XL", 40}, {"L", 50}, {"XC", 90}, {"C", 100}, {"CD", 400}, {"D", 500}, {"CM", 900}, {"M", 1000}};

string DecToRoman(int num) {
	string ans = "";
	for ( int pos = 12; num; num -= Roman[pos].second) {
		for( ; Roman[pos].second > num; pos --);
		ans += Roman[pos].first;
	}
	return ans;
}

int RomanToDec(string &num) {
	int ans = 0;
	for (int i = 12, pos = 0; i >= 0 && pos != num.size(); ) {
		for ( ; Roman[i].first != num.substr(pos, Roman[i].first.size()); i --);
		ans += Roman[i].second;
		pos += Roman[i].first.size();
	}
	return ans;
}