// Minimum Queue
//

struct MinQueue {
    stack<pair<int,int>> s1, s2;

    void push(int val) {
        int mn = s1.empty() ? val : min(val, s1.top().second);
        s1.push({val, mn});
    }

    void pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                int val = s1.top().first;
                s1.pop();
                int mn = s2.empty() ? val : min(val, s2.top().second);
                s2.push({val, mn});
            }
        }
        int rm = s2.top().first;
        s2.pop();
    }

    int getMin() {
        if (s1.empty() || s2.empty()) {
            return s1.empty() ? s2.top().second : s1.top().second;
        } else {
            return min(s1.top().second, s2.top().second);
        }
    }
};