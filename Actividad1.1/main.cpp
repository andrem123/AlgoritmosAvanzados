#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

static void mergeDesc(vector<double>& a, vector<double>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i] >= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];

    for (int idx = left; idx <= right; idx++) a[idx] = temp[idx];
}

static void mergeSortDesc(vector<double>& a, vector<double>& temp, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortDesc(a, temp, left, mid);
    mergeSortDesc(a, temp, mid + 1, right);
    mergeDesc(a, temp, left, mid, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<double> a;
    a.reserve(N);

    for (int i = 0; i < N; i++) {
        double x;
        cin >> x;
        a.push_back(x);
    }

    if (N > 1) {
        vector<double> temp(N);
        mergeSortDesc(a, temp, 0, N - 1);
    }

    cout << setprecision(10);
    for (int i = 0; i < N; i++) {
        cout << a[i] << "\n";
    }

    return 0;
}
