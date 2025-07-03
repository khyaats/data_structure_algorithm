#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;

struct Student {
    ll position;
    ll candies;
};

int n;
vector<Student> students;

bool isPossible(ll m) {
    vector<ll> current(n);
    for (int i = 0; i < n; ++i)
        current[i] = students[i].candies;

    // Distribute surplus from left to right
    for (int i = 0; i < n - 1; ++i) {
        ll surplus = current[i] - m;
        if (surplus > 0) {
            ll distance = students[i + 1].position - students[i].position;
            ll transferable = max(0LL, surplus - distance);  // amount that actually arrives
            current[i + 1] += transferable;
        }
        else if (surplus < 0) {
            ll distance = students[i + 1].position - students[i].position;
            current[i + 1] += surplus - distance;  // need to borrow more to make up deficit and cost
        }
    }
    return current[n - 1] >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    students.resize(n);
    ll total = 0;

    for (int i = 0; i < n; ++i) {
        cin >> students[i].position >> students[i].candies;
        total += students[i].candies;
    }

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.position < b.position;
        });

    ll low = 0, high = total, result = 0;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (isPossible(mid)) {
            result = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    std::cout << result << '\n';
    return 0;
}
