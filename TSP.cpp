#include "TSP.hpp"

void TSP::set_matrix(vector<vector<int>> matrix) {
    this -> matrix = std::move(matrix);
    set_min_val();
}

void TSP::set_min_val() {
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) if(matrix[i][j] < min_value && matrix[i][j] >= 0) min_value = matrix[i][j];
    }
}

pair<vector<int>, int> TSP::start_DFS(int minutes, int upper_bound) {

    results.second = INT_MAX;
    if(upper_bound) results = NN();
    DFS(0, minutes, chrono::steady_clock::now());

    return results;
}

void TSP::DFS(int startV, int minutes, chrono::time_point<chrono::steady_clock> start) {
    stack<tuple<int, int, vector<int>>> stack; // {currentV, path_length, path}
    vector<int> path;

    stack.emplace(startV, 0, path);

    while(!stack.empty() && chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now() - start).count() < minutes) {
        auto[currentV, path_length, currentPath] = stack.top();
        stack.pop();

        currentPath.push_back(currentV);

        if(currentPath.size() == matrix.size()) {
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
                if(matrix[currentV][i] != -1 && find(currentPath.begin(), currentPath.end(), i) == currentPath.end()) {
                    if(path_length + matrix[currentV][i] + (matrix.size() - currentPath.size() - 1) * min_value < results.second)
                        stack.emplace(i, path_length + matrix[currentV][i], currentPath);
                }
            }
        }
    }
}

pair<vector<int>, int> TSP::start_BFS(int minutes, int upper_bound) {

    results.second = INT_MAX;
    if(upper_bound) results = NN();
    BFS(0, minutes, chrono::steady_clock::now());

    return results;
}

void TSP::BFS(int startV, int minutes, chrono::time_point<chrono::steady_clock> start) {
    queue<tuple<int, int, vector<int>>> queue; // {currentV, path_length, path}
    vector<int> path;

    queue.emplace(startV, 0, path);

    while(!queue.empty() && chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now() - start).count() < minutes) {
        auto[currentV, path_length, current_path] = queue.front();
        queue.pop();

        current_path.push_back(currentV);

        if(current_path.size() == matrix.size()) {
            if(matrix[currentV][startV] != -1) {
                path_length = path_length + matrix[currentV][startV];
                if(path_length < results.second) {
                    current_path.push_back(startV);
                    results.first = current_path;
                    results.second = path_length;
                }
            }
        } else{
            for(int i = 0; i < matrix.size(); i++) {
                if(matrix[currentV][i] != -1 && find(current_path.begin(), current_path.end(), i) == current_path.end()) {
                    if(path_length + matrix[currentV][i] + (matrix.size() - current_path.size() - 1) * min_value < results.second)
                        queue.emplace(i, path_length + matrix[currentV][i], current_path);
                }
            }
        }
    }
}

pair<vector<int>, int> TSP::start_LC(int minutes, int upper_bound) {

    results.second = INT_MAX;
    if(upper_bound) results = NN();
    LC(0, minutes, chrono::steady_clock::now());

    return results;
}

void TSP::LC(int startV, int minutes, chrono::time_point<chrono::steady_clock> start) {
    priority_queue<tuple<int, int, vector<int>>, vector<tuple<int, int, vector<int>>>, greater<>> priority_queue; // { path_length, currentV, path}
    vector<int> path;

    priority_queue.emplace(0, startV, path);

    while(!priority_queue.empty() && chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now() - start).count() < minutes) {
        auto [path_length, currentV, current_path] = priority_queue.top();
        priority_queue.pop();

        current_path.push_back(currentV);

        if(current_path.size() == matrix.size()) {
            if(matrix[currentV][startV] != -1) {
                path_length = path_length + matrix[currentV][startV];
                if(path_length < results.second) {
                    current_path.push_back(startV);
                    results.first = current_path;
                    results.second = path_length;
                }
            }
            continue;
        }

        for(int i = 0; i < matrix[currentV].size(); i++) {
            if(matrix[currentV][i] != -1 && find(current_path.begin(), current_path.end(), i) == current_path.end()) {
                if(path_length + matrix[currentV][i] + (matrix.size() - current_path.size() - 1) * min_value < results.second)
                priority_queue.emplace(path_length + matrix[currentV][i], i, current_path);
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