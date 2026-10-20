class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        long long ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;

            for (int i = 0; i < n && ok; i += k) {
                int descents = 0;

                for (int j = 0; j < k; j++) {
                    int a = nums[i + j];
                    int b = nums[i + (j + 1) % k];

                    if (a > b) descents++;
                }

                // A cyclic rotation can sort a block only if
                // its elements match the sorted block as a rotation.
                vector<int> block(nums.begin() + i,
                                  nums.begin() + i + k);
                vector<int> target(sorted.begin() + i,
                                   sorted.begin() + i + k);

                sort(block.begin(), block.end());

                if (block != target) {
                    ok = false;
                    break;
                }

                if (descents > 1) {
                    ok = false;
                    break;
                }
            }

            if (ok) ans += k;
        }

        return ans;
    }
};