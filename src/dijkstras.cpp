#include "dijkstras.h"
#include <algorithm> 
#include <iterator> 
#include <queue>


//
// dijkstra_shortest_path
// 

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> dist(G.numVertices, INF); dist[source] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq; pq.push({0, source});
    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost > dist[u]) continue;
        for (auto& e : G[u]) {
            int nd = dist[u] + e.weight;
            if (nd < dist[e.dst]) dist[e.dst] = nd, previous[e.dst] = u, pq.push({nd, e.dst});
        }
    }
    return dist;
}

//
// extract_shortest_path
//

vector<int> extract_shortest_path(const vector<int>&, const vector<int>& previous, int destination) {
    vector<int> path;

    if (destination != 0 && distances[destination] == 0) {
        return path;
    }

    while (destination != -1) {
        path.push_back(destination);
        destination = previous[destination];
    }
    reverse(path.begin(), path.end());
    return path;
}

//
// print_path
//

void print_path(const vector<int>& v, int total) {
    for (int i = 0; i < (int)v.size(); i++) 
        cout << v[i] << " ";
    
    cout << endl << "Total cost is " << total << endl;
}
