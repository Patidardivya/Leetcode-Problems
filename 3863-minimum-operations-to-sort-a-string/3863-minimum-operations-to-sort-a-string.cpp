class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int min_c = 0, max_c = 0;

        if(is_sorted(s.begin(), s.end())) return 0;
        if(n==2) return -1;

        for(int i=0 ; i<n ; ++i){
            if(s[i] < s[min_c])
                min_c = i;
            if(s[i] >= s[max_c])
                max_c = i;
        }
        if(min_c == 0 || max_c == n-1)
            return 1;
        return (min_c == (n-1) && max_c == 0) ? 3 : 2;
    }
};