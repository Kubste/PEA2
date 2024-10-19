#include "TSP.hpp"

#include <utility>

void TSP::set_matrix(vector<vector<int>> matrix) {
    this -> matrix = std::move(matrix);
}

pair<vector<int>, int> TSP::start_DFS() {

    results.second = INT_MAX;
    for(int i = 0; i < matrix.size(); i++) DFS(i);

    return results;
}

void TSP::DFS(int startV) {
    stack<tuple<int, int, set<int>, vector<int>>> stack; // {currentV, path_length, visitedV, path}
    set<int> visitedV;
    vector<int> path;

    stack.emplace(startV, 0, visitedV, path);

    while(!stack.empty()) {
        auto[currentV, path_length, visited, currentPath] = stack.top();
        stack.pop();

        visited.insert(currentV);
        currentPath.push_back(currentV);

        if(visited.size() == matrix.size()) {
            if(matrix[currentV][startV] != -1) {
                path_length = path_length + matrix[currentV][startV];
                if(path_length < results.second) {
                    currentPath.push_back(startV);
                    results.first = currentPath;
                    results.second = path_length;
                }
            }
        } else{
            for(int i = 0; i < matrix.size(); i++) {
                if(matrix[currentV][i] != -1 && visited.find(i) == visited.end()) {
                    if(path_length + matrix[currentV][i] + matrix.size() - visited.size() + 1 < results.second)
                        stack.emplace(i, path_length + matrix[currentV][i], visited, currentPath);
                }
            }
        }
    }
}

pair<vector<int>, int> TSP::NN() {
    pair<vector<int>, int> resultsNN;
    resultsNN.second = INT_MAX;
    vector<int> path;
    vector<int> Q;

    for(int j = 0; j < matrix.size(); j++) {

        path.push_back(j);

        for(int i = 0; i < matrix.size(); i++) if(i != j) Q.push_back(i);
        explore_paths(path, 0, Q, j, j, resultsNN);

        path.clear();
        Q.clear();
    }
    return resultsNN;
}

void TSP::explore_paths(vector<int> path, int path_length, vector<int> Q, int current_node, int start_node,
                        pair<vector<int>, int> &resultsNN) {
    vector<pair<int, int>> min_edges;
    int min_edge_value = INT_MAX;
    vector<int> new_path;
    vector<int> new_Q;
    int next_node;
    int edge_length;

    if(Q.empty()) {
        if(matrix[current_node][start_node] != -1) {
            path_length += matrix[current_node][start_node];
            path.push_back(start_node);

            if(path_length < resultsNN.second) {
                resultsNN.first = path;
                resultsNN.second = path_length;
            }
        }
        return;
    }

    for(int i = 0; i < matrix.size(); i++) {
        if(matrix[current_node][i] != -1 && find(Q.begin(), Q.end(), i) != Q.end()) {
            if(matrix[current_node][i] < min_edge_value) {
                min_edges.clear();
                min_edge_value = matrix[current_node][i];
                min_edges.emplace_back(i, matrix[current_node][i]);
            } else if(matrix[current_node][i] == min_edge_value) min_edges.emplace_back(i, matrix[current_node][i]);
        }
    }

    for(int i = 0; i < min_edges.size(); i++) {
        next_node = min_edges[i].first;
        edge_length = min_edges[i].second;

        new_path = path;
        new_path.push_back(next_node);
        new_Q = Q;
        new_Q.erase(remove(new_Q.begin(), new_Q.end(), next_node), new_Q.end());

        explore_paths(new_path, path_length + edge_length, new_Q, next_node, start_node, resultsNN);
    }
}