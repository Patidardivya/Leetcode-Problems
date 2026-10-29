
class Solution {
public:
    int n, timer;
    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth;
    vector<int> bit;
    string s;
    int LOG;

    void updateBIT(int idx, int val) {
        while (idx <= n) {
            bit[idx] ^= val;
            idx += idx & -idx;
        }
    }

    int queryBIT(int idx) {
        int ans = 0;
        while (idx > 0) {
            ans ^= bit[idx];
            idx -= idx & -idx;
        }
        return ans;
    }

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[u][0] = p;

        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }

        tout[u] = timer;
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;

        for (int j = LOG - 1; j >= 0; j--) {
            if (!isAncestor(up[u][j], v)) {
                u = up[u][j];
            }
        }
        return up[u][0];
    }

    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                               string s, vector<string>& queries) {
        this->n = n;
        this->s = s;
        timer = 0;

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        adj.assign(n, {});
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        tin.resize(n);
        tout.resize(n);
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, 0));
        bit.assign(n + 1, 0);

        dfs(0, 0);

        // Each character is represented by one bit.
        // XOR over a subtree's Euler interval supports path queries.
        for (int u = 0; u < n; u++) {
            int mask = 1 << (s[u] - 'a');
            updateBIT(tin[u], mask);
            updateBIT(tout[u] + 1, mask);
        }

        vector<bool> ans;

        for (string &q : queries) {
            stringstream ss(q);
            string type;
            int u, v;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                updateBIT(tin[u], 1 << (s[u] - 'a'));
                updateBIT(tout[u] + 1, 1 << (s[u] - 'a'));

                s[u] = c;

                updateBIT(tin[u], 1 << (s[u] - 'a'));
                updateBIT(tout[u] + 1, 1 << (s[u] - 'a'));
            } 
            else {
                ss >> v;
                int w = lca(u, v);

                int mask = queryBIT(tin[u]) ^
                           queryBIT(tin[v]) ^
                           (1 << (s[w] - 'a'));

                ans.push_back(__builtin_popcount((unsigned int)mask) <= 1);
            }
        }

        return ans;
    }
};
