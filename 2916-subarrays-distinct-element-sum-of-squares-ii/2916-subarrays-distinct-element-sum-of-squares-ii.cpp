class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();

        vector<long long> sum(4 * n), sq(4 * n), lazy(4 * n);
        unordered_map<int, int> last;
        long long ans = 0;

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr) -> void {
            if (ql > r || qr < l) return;

            if (ql <= l && r <= qr) {
                long long len = r - l + 1;
                sq[node] = (sq[node] + 2 * lazy[node] * sum[node] % MOD
                          + len * lazy[node] % MOD * lazy[node]) % MOD;
                sum[node] = (sum[node] + len * lazy[node]) % MOD;
                lazy[node] = 0;
                return;
            }

            int mid = (l + r) / 2;
            self(self, node * 2, l, mid, ql, qr);
            self(self, node * 2 + 1, mid + 1, r, ql, qr);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        auto add = [&](auto&& self, int node, int l, int r,
                       int ql, int qr, long long val) -> void {
            if (ql > r || qr < l) return;

            if (ql <= l && r <= qr) {
                long long len = r - l + 1;
                sq[node] = (sq[node] + 2 * val % MOD * sum[node] % MOD
                          + len * val % MOD * val) % MOD;
                sum[node] = (sum[node] + len * val) % MOD;
                lazy[node] = (lazy[node] + val) % MOD;
                return;
            }

            int mid = (l + r) / 2;

            if (lazy[node]) {
                self(self, node * 2, l, mid, l, mid, lazy[node]);
                self(self, node * 2 + 1, mid + 1, r, mid + 1, r, lazy[node]);
                lazy[node] = 0;
            }

            self(self, node * 2, l, mid, ql, qr, val);
            self(self, node * 2 + 1, mid + 1, r, ql, qr, val);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        for (int i = 0; i < n; i++) {
            int p = last.count(nums[i]) ? last[nums[i]] : -1;

            add(add, 1, 0, n - 1, p + 1, i, 1);
            last[nums[i]] = i;

            ans = (ans + sq[1]) % MOD;
        }

        return ans;
    }
};