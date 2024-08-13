#ifndef HOSPITALS_WINDOW_HPP
#define HOSPITALS_WINDOW_HPP

#include "Patient.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

#define MAX_RESULTS_NUMBER 10000

namespace GUI {
    //data base paths
    const std::string data_file_path = "../GUI/dane.json";
    const std::string results_file_path = "../GUI/wyniki.json";
    const std::string inital_setting_path = "../GUI/initial_setting.json";

    extern specializations_vector specializations;


    //GUI input data
    extern int max_iteration;
    extern int aspiration_criterion;
    extern int tabu_list_length;
    extern std::vector<int> neighborhood_selection_method;

    //GUI output data
    extern int iterations_number;
    extern int aspiration_criterion_use_number;
    extern int execution_time;
    extern int best_result_iteration;
    extern int single_results[MAX_RESULTS_NUMBER];
    extern double best_result;

    int loadData();

    void loadHospitals();

    int saveData();
} //GUI
#endif //HOSPITALS_WINDOW_HPP
