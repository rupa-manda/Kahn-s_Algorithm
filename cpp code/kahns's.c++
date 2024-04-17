#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

void readGraph(const string& filename, vector<vector<int > >& adj, vector<int>& inDegree, int& numVertices) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file." << std::endl;
        exit(EXIT_FAILURE);
    }

    int u, v;
    file >> numVertices; 
    adj.resize(numVertices);
    inDegree.resize(numVertices, 0);

    while (file >> u >> v) {
        adj[u].push_back(v);
        ++inDegree[v];
    }

    file.close();
}

void topologicalSort(const vector<vector<int>>& adj, const vector<int>& inDegree, int numVertices) {
    queue<int> q;
    vector<int> sorted;
    for (int i = 0; i < numVertices; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        sorted.push_back(node);
        for (int neighbor : adj[node]) {
            int& degree = const_cast<int&>(inDegree[neighbor]); 
            if (--degree == 0) {
                q.push(neighbor);
            }
        }
    }

    if (sorted.size() != numVertices) {
        cout << "There is a cycle in the graph." << endl;
    } else {
        for (int vertex : sorted) {
            cout << vertex << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> adjacencyList;
    vector<int> inDegree;
    int numVertices;
    string filename = "graph.txt";

    readGraph(filename, adjacencyList, inDegree, numVertices);
    topologicalSort(adjacencyList, inDegree, numVertices);

    return 0;
}
