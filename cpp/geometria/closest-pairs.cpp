

Double closestPair(vector <Pto> &pts) {
    if (SZ(pts) < 2) {
        return 0;
    }

    Double ans = INF;

    sort(ALL(pts));
    set<pair<Double, Double>> stY;

    deque <Pto> deq;
    for (Pto &p: pts) {
        while (SZ(deq) > 0 && p.x - deq.front().x >= ans) {
            stY.erase({deq.front().y, deq.front().x});
            deq.pop_front();
        }

        auto it = stY.lower_bound({p.y - ans, -INF});
        while (it != stY.end() && it->first < p.y + ans) {
            ans = min(ans, (Pto(it->second, it->first) - p).mod());
            it++;
        }

        deq.push_back(p);
        stY.insert({p.y, p.x});
    }
    return ans;
}