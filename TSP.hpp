#ifndef TSP_HPP
#define TSP_HPP
#include <vector>
#include <chrono>
#include <climits>
#include <iostream>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

class TSP {

    public:
    void set_matrix(vector<vector<int>> matrix);
    pair<vector<int>, int> NN();
    void explore_paths(vector<int> path, int path_length, vector<int> Q, int current_node, int start_node, pair<vector<int>, int> &resultsNN);
    pair<vector<int>, int> start_DFS();

    private:
        vector<vector<int>> matrix;
        pair<vector<int>, int> results;

        void DFS(int startV);
};

#endif