class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        
        // Build adjacency list
        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        // dist[node][count] = minimum cost
        vector<vector<long long>> dist(n, vector<long long>(k + 1, LLONG_MAX));

        // {cost, node, consecutive count}
        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > pq;

        // Starting node has count = 1
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, cnt] = pq.top();
            pq.pop();

            // Ignore outdated states
            if (cost != dist[u][cnt]) {
                continue;
            }

            // Destination reached
            if (u == n - 1) {
                return (int)cost;
            }

            for (auto &[v, w] : adj[u]) {

                int newCnt;

                if (labels[u] == labels[v]) {
                    newCnt = cnt + 1;
                } 
                else {
                    newCnt = 1;
                }

                // More than k consecutive characters is invalid
                if (newCnt > k) {
                    continue;
                }

                long long newCost = cost + w;

                if (newCost < dist[v][newCnt]) {
                    dist[v][newCnt] = newCost;
                    pq.push({newCost, v, newCnt});
                }
            }
        }

        return -1;
    }
};