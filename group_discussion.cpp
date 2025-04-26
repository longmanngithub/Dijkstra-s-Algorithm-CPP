#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj;

public:
    void add_edge(const string &u, const string &v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight)); // For undirected edges
    }

    // Dijkstra's algorithm to find the shortest distances
    unordered_map<string, int> dijkstra(const string &src, unordered_map<string, string> &prev) {
        unordered_map<string, int> distances;   
        
        // Initialize all distances to infinity
        for (const auto &pair : adj) {
            distances[pair.first] = INT_MAX;
        }
        distances[src] = 0; // Distance from source to source is 0

        // Min-heap priority queue
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push(make_pair(0, src)); // Push the source node with distance 0

        while (!pq.empty()) {
            int currDist = pq.top().first;
            string currNode = pq.top().second;
            pq.pop();   // Remove duplicates

            // If the current distance is greater than the distance to the current node
            if (currDist > distances[currNode]) {
                continue;   // Skip the current node
            }

            // Traverse the neighbors of the current node
            for (const auto &neighbor : adj[currNode]) {
                string nextNode = neighbor.first;   // Get the neighbor node
                int weight = neighbor.second;       // Get the weight of the edge
                int distance = currDist + weight;   // Calculate the new distance

                // If the new distance is less than the current distance
                if (distance < distances[nextNode]) {
                    distances[nextNode] = distance;         // Update the distance
                    prev[nextNode] = currNode;              // Track the previous node
                    pq.push(make_pair(distance, nextNode)); // Add the node to the priority queue
                }
            }
        }
        return distances;
    }

    // Function to print the graph
    void print_graph() {
        for (const auto &pair : adj) {
            cout << "- " << pair.first << " -> ";
            for (const auto &neighbor : pair.second) {
                cout << "[" << neighbor.first << "] ";
            }
            cout << "\n";
        }
    }

    // Function to reconstruct and print the path from source to destination
    void print_path(const unordered_map<string, string> &prev, const string &dest) {
        // If the destination is the source
        if (prev.find(dest) == prev.end()) {
            cout << dest;
            return;
        }
        print_path(prev, prev.at(dest));
        cout << " -> " << dest;
    }

    // Function to print distances and paths
    void print_distances(const unordered_map<string, int> &distances, const unordered_map<string, string> &prev) {
        for (const auto &pair : distances) {
            cout << "Distance from Phnom Penh to " << pair.first << ": " << pair.second << " km\n";
            cout << "Path: ";
            print_path(prev, pair.first);
            cout << "\n\n";
        }
    }
};

int main() {
    Graph graph;

    // Add edges to the graph
    graph.add_edge("Phnom Penh", "Kandal", 11);
    graph.add_edge("Kandal", "Kampong Speu", 37);
    graph.add_edge("Kandal", "Takeo", 67);
    graph.add_edge("Kandal", "Kampong Chhnang", 83);
    graph.add_edge("Kandal", "Kampong Cham", 113);
    graph.add_edge("Kandal", "Prey Veng", 83);
    graph.add_edge("Kampong Speu", "Pursat", 203);
    graph.add_edge("Kampong Speu", "Kampong Chhnang", 107);
    graph.add_edge("Kampong Speu", "Takeo", 78);
    graph.add_edge("Kampong Speu", "Kampot", 118);
    graph.add_edge("Kampong Speu", "Koh Kong", 223);
    graph.add_edge("Kampong Speu", "Sihanoukville", 179);
    graph.add_edge("Kampong Chhnang", "Kampong Thom", 195);
    graph.add_edge("Kampong Chhnang", "Kampong Cham", 151);
    graph.add_edge("Kampong Chhnang", "Pursat", 95);
    graph.add_edge("Kampong Cham", "Kampong Thom", 66);
    graph.add_edge("Kampong Cham", "Kratie", 176);
    graph.add_edge("Kampong Cham", "Tboung Khmum", 60);
    graph.add_edge("Kampong Cham", "Prey Veng", 77);
    graph.add_edge("Prey Veng", "Tboung Khmum", 50);
    graph.add_edge("Prey Veng", "Svay Rieng", 52);
    graph.add_edge("Takeo", "Kampot", 72);
    graph.add_edge("Pursat", "Battambang", 95);
    graph.add_edge("Pursat", "Koh Kong", 261);
    graph.add_edge("Kampot", "Koh Kong", 243);
    graph.add_edge("Kampot", "Kep", 26);
    graph.add_edge("Kampot", "Sihanoukville", 100);
    graph.add_edge("Koh Kong", "Sihanoukville", 234);
    graph.add_edge("Kampong Thom", "Siem Reap", 136);
    graph.add_edge("Kampong Thom", "Preah Vihear", 120);
    graph.add_edge("Kampong Thom", "Stung Treng", 274);
    graph.add_edge("Kampong Thom", "Kratie", 239);
    graph.add_edge("Pursat", "Battambang", 107);
    graph.add_edge("Pursat", "Koh Kong", 261);
    graph.add_edge("Kratie", "Stung Treng", 151);
    graph.add_edge("Kratie", "Mondulkiri", 123);
    graph.add_edge("Tboung Khmum", "Kratie", 110);
    graph.add_edge("Battambang", "Banteay Meanchey", 67);
    graph.add_edge("Battambang", "Siem Reap", 163);
    graph.add_edge("Battambang", "Pailin", 84);
    graph.add_edge("Siem Reap", "Oddar Meanchey", 131);
    graph.add_edge("Siem Reap", "Preah Vihear", 158);
    graph.add_edge("Siem Reap", "Banteay Meanchey", 105);
    graph.add_edge("Preah Vihear", "Oddar Meanchey", 236);
    graph.add_edge("Preah Vihear", "Stung Treng", 139);
    graph.add_edge("Stung Treng", "Ratanakiri", 141);
    graph.add_edge("Stung Treng", "Mondulkiri", 302);
    graph.add_edge("Mondulkiri", "Ratanakiri", 182);
    graph.add_edge("Banteay Meanchey", "Oddar Meanchey", 127);

    string startCity = "Phnom Penh";
    cout << "Adjacency List of All the Connections from Phnom Penh to All Provinces in Cambodia:\n";
    graph.print_graph();
    cout << "---------------------------------------------------------------------------------------------------" << endl;

    // To store the previous node for each province
    unordered_map<string, string> prev;

    auto distances = graph.dijkstra(startCity, prev);

    graph.print_distances(distances, prev);

    return 0;
}