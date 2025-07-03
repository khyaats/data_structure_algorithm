#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX_K = 50;
vector<long long> lengthsOfString(MAX_K + 1);

void calculateStringLength() {
    lengthsOfString[1] = 3; // "ABC"
    for (int i = 2; i <= MAX_K; i++)
        lengthsOfString[i] = 2 * lengthsOfString[i - 1] + 3;
}

// Get the character at position position in Sk
char getChar(int k, long long position) {
    if (k == 1) {
        string baseString = "ABC";
        return baseString[position - 1];
    }

    position--;

    if (position == 0) return 'A';
    position--;

    if (position < lengthsOfString[k - 1])
        return getChar(k - 1, position + 1);

    position -= lengthsOfString[k - 1];

    if (position == 0) return 'B';
    position--;

    if (position < lengthsOfString[k - 1])
        return getChar(k - 1, position + 1);

    position -= lengthsOfString[k - 1];

    if (position == 0) return 'C';

    return '\n';
}

int main() {
    calculateStringLength();

    int t;
    cin >> t;

    while (t--) {
        int k;
        long long l, r;
        cin >> k >> l >> r;

        string answer = "";
        for (long long i = l; i <= r; i++)
            answer += getChar(k, i);
        cout << answer << '\n';
    }

    return 0;
}