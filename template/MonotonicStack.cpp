#include <bits/stdc++.h>
using namespace std;
template <class T, class F>
vector<int> nearestLeft(const vector<T>& A, F good) {
    int n = A.size();
    vector<int> res(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && !good(A[st.back()], A[i])) {
            st.pop();
        }

        if (!st.empty()) {
            res[i] = st.top();
        }

        st.push(i);
    }

    return res;
}

template <class T, class F>
vector<int> nearestRight(const vector<T>& A, F good) {
    int n = A.size();
    vector<int> res(n, n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && !good(A[st.back()], A[i])) {
            st.pop();
        }

        if (!st.empty()) {
            res[i] = st.top();
        }

        st.push(i);
    }

    return res;
}
/*
use:
    A = [5,2,3,5,9]
    auto pgA = nearestLeft(A, greater<int>());   // 左邊最近 A[j] > A[i] => [-1, 0, 0, -1, -1]
    auto ngA = nearestRight(A, greater<int>());  // 右邊最近 A[j] > A[i] => [4, 2, 3, 4, 5]
    B = [5,2,3,5,9]
    auto plB = nearestLeft(B, less<int>());      // 左邊最近 B[j] < B[i] => [-1, -1, 1, 2, 3]
    auto nlB = nearestRight(B, less<int>());     // 右邊最近 B[j] < B[i] => [1, 5, 5, 5, 5]
*/ 
