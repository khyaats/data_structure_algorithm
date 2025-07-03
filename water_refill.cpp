#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int noOfStudents, noOfFaucets;
    cin >> noOfStudents >> noOfFaucets;

    vector<int> waterCapacity(noOfStudents);
    for (int i = 0; i < noOfStudents; ++i)
        cin >> waterCapacity[i];

    priority_queue<long long, vector<long long>, greater<>> queueOfStudents;

    // First n number of students start immediately
    for (int i = 0; i < min(noOfStudents, noOfFaucets); ++i)
        queueOfStudents.push(waterCapacity[i]);

    // Remaining students wait for a faucet
    for (int i = noOfFaucets; i < noOfStudents; ++i) {
        long long earliestFinish = queueOfStudents.top(); queueOfStudents.pop();
        queueOfStudents.push(earliestFinish + waterCapacity[i]);
    }

    long long maximumTimeRequired = 0;
    while (!queueOfStudents.empty()) {
        maximumTimeRequired = max(maximumTimeRequired, queueOfStudents.top());
        queueOfStudents.pop();
    }

    cout << maximumTimeRequired << "\n";
    return 0;
}