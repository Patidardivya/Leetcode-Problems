class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, len = 0;

        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < 2; j++) {
                int l = i, r = i + j;

                while (l >= 0 && r < s.size() && s[l] == s[r]) {
                    if (r - l + 1 > len) {
                        start = l;
                        len = r - l + 1;
                    }
                    l--;
                    r++;
                }
            }
        }
        return s.substr(start, len);
    }
};
