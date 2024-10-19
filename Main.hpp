#ifndef MAIN_HPP
#define MAIN_HPP
#include "File_manager.hpp"
#include "TSP.hpp"
#include <string>
#include <climits>

using namespace std;

class Main {

public:
    void run();

private:
    string config_path = R"(files/config.txt)";
    string data_path;
    string result_path;
    int method;
    int minutesD;
    int minutesB;
    int minutesL;
    int optimal_value;
    int progress_indicator;
    int repetitions;
    File_manager file_manager;
    vector<vector<int>> matrix;
    TSP tsp;
    chrono::duration<double, micro> total_time{};
    float total_absolute_error;
    float total_relative_error;
    vector<chrono::duration<double, micro>> total_times;
    int time_measurements = 0;

    void assign_parameters(pair<vector<string>, vector<int>> parameters);
    void print_info();
    void print_partial_info(pair<vector<int>, int> results, int repetition);

};

#endif