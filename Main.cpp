#include "Main.hpp"
#include <iostream>

using namespace std;

void Main::run() {
    pair<vector<int>, int> results;
    vector<chrono::duration<double, micro>> times;
    pair<vector<vector<int>>, int> data;
    chrono::duration<double, micro> time{};

    assign_parameters(file_manager.read_config_file(config_path));
    data = file_manager.read_data_file(data_path);
    matrix = data.first;
    optimal_value = data.second;

    if(progress_indicator == 0) print_info();

    tsp.set_matrix(matrix);
    for(int i = 0; i < repetitions; i++) {
        if(method == 1) results = tsp.start_DFS();
        else if(method == 2) results = tsp.start_BFS();
        else if(method == 3) results = tsp.start_LC();

        print_partial_info(results, i + 1);
    }

    if(progress_indicator) print_info();
}

void Main::assign_parameters(pair<vector<std::string>, vector<int>> parameters) {
    data_path = parameters.first[0];
    result_path = parameters.first[1];
    method = parameters.second[0];
    if(parameters.second[1] == -1) minutesD = INT_MAX;
    else minutesD = parameters.second[1];
    if(parameters.second[2] == -1) minutesB = INT_MAX;
    else minutesB = parameters.second[2];
    if(parameters.second[3] == -1) minutesL = INT_MAX;
    else minutesL = parameters.second[3];
    repetitions = parameters.second[4];
    progress_indicator = parameters.second[5];
}

void Main::print_info() {

    size_t position = data_path.find_last_of('/');
    cout << endl << "Plik zawierajacy dane problemu: " << data_path.substr(position + 1) << endl;
    cout << "Wynik optymalny: " << optimal_value << endl;
    cout << "Wybrana metoda: ";
    if(method == 1) cout << "DFS" << endl;
    else if(method == 2) cout << "BFS" << endl;
    else if(method == 3) cout << "low cost" << endl;
    cout << "Liczba powtorzen przeszukania: " << repetitions << endl;
    if(method == 1 && minutesD != INT_MAX) cout << "Maksymalny czas przeszukania: " << minutesD << " min" << endl;
    else if(method == 1) cout << "Brak ograniczenia czasowego" << endl;
    else if(method == 2 && minutesB != INT_MAX) cout << "Maksymalny czas przeszukania: " << minutesB << " min" << endl;
    else if(method == 2) cout << "Brak ograniczenia czasowego" << endl;
    else if(method == 3 && minutesL != INT_MAX) cout << "Maksymalny czas przeszukania: " << minutesL << " min" << endl;
    else if(method == 3) cout << "Brak ograniczenia czasowego" << endl;
    cout << endl;
}

void Main::print_partial_info(pair<vector<int>, int> results, int repetition) {

    cout << "Wykonano " << repetition << " przeszukanie" << endl;
    cout << "Otrzymana najkrotsza sciezka: ";
    for(int i = 0; i < results.first.size() - 1; i++) cout << results.first[i] << " -> ";
    cout << results.first.back() << endl;
    cout << "Dlugosc otrzymanej sciezki: " << results.second << endl;
    cout << endl;
}

int main() {
    Main main_obj{};
    main_obj.run();
    system("pause");

    return 0;
}