#ifndef TSP_HPP
#define TSP_HPP
#include <vector>
#include <chrono>
#include <climits>
#include <iostream>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>

using namespace std;

class TSP {

    public:
        void set_matrix(vector<vector<int>> matrix);
        pair<vector<int>, int> NN();
        void explore_paths(vector<int> path, int path_length, vector<int> Q, int current_node, int start_node, pair<vector<int>, int> &resultsNN);
        pair<vector<int>, int> start_DFS();
        pair<vector<int>, int> start_BFS();
        pair<vector<int>, int> start_LC();

    private:
        vector<vector<int>> matrix;
        pair<vector<int>, int> results;
        int min_value = INT_MAX;

        void DFS(int startV);
        void BFS(int startV);
        void LC(int startV);
        void set_min_val();
};

#endif