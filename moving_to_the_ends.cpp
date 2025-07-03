#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int array;
    cin >> array;
    while (array--) {
        int size;
        cin >> size;

        vector<int> arr(size);
        unordered_map<int, int> position;
        for (int i = 0; i < size; ++i) {
            cin >> arr[i];
            position[arr[i]] = i;  // to store position of each value
        }

        int max_length = 1;
        int curr_length = 1;

        for (int i = 2; i <= size; ++i) {
            if (position[i] > position[i - 1]) {
                curr_length++;
                max_length = max(max_length, curr_length);
            }
            else {
                curr_length = 1;
            }
        }

        cout << size - max_length << '\size';
    }

    return 0;
}