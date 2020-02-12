#include <bits/stdc++.h>

using namespace std;

const char FROM = '.';
const char TO = ',';

int main() {
    freopen("new_captions.srt", "r", stdin);
    freopen("new_pope.srt", "w", stdout);

    string s;
    while (getline(cin, s)) {
        for (int i = 0; i < s.size(); ++i) {
            if (i && s[i] == FROM && ('0' <= s[i - 1] && s[i - 1] <= '9')) {
                s[i] = TO;
            }
        }

        cout << s << '\n';
    }
}
