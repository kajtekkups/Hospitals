#include "GUI.hpp"
#include <cfloat>
#include <iostream>

namespace GUI {

    //GUI input data
    int max_iteration;
    int aspiration_criterion;
    int tabu_list_length;
    std::vector<int> neighborhood_selection_method = {1, 1, 1, 1};

    //GUI output data
    int iterations_number = 0;
    int aspiration_criterion_use_number = 0;
    int execution_time = 0;
    int best_result_iteration;  //number of iteration with best result
    double best_result = DBL_MAX;
    int single_results[MAX_RESULTS_NUMBER];

    int loadData(){

        //load JSON file
        std::ifstream configuration_file(data_file_path);

        if (!configuration_file.is_open()) {
            std::cerr << "Could not open file " << data_file_path << std::endl;
            return 1;
        }

        //parse JSON data
        nlohmann::json configuration_data;
        configuration_file >> configuration_data;

        try {
            max_iteration = configuration_data["max_iteration"];
            aspiration_criterion = configuration_data["aspiration_criterion"];
            tabu_list_length = configuration_data["tabu_list_length"];
            const std::vector<int> neighborhood_table = configuration_data["neighborhood_selection_method"].get<std::vector<int>>();
            for(int i = 0; i <  static_cast<int>(neighborhood_selection_method.size()); i++) {
                neighborhood_selection_method[i] = neighborhood_table[i];
            }
        }
        catch (const std::exception& e) {
            std::cout << "incorrect input data" << std::endl;
        }

        //close file
        configuration_file.close();

        return 0;
    }


    int saveData(){
        nlohmann::json data_to_save;

        //save data to JSON object
        data_to_save["iterations_number"] = iterations_number;
        data_to_save["aspiration_criterion_use_number"] = aspiration_criterion_use_number;
        data_to_save["execution_time"] = execution_time;
        data_to_save["best_result_iteration"] =  best_result_iteration;
        data_to_save["best_result"] =  static_cast<int>(best_result);
        data_to_save["single_results"] = single_results;

        //prepere for saving data
        std::ofstream result_file(results_file_path);

        if (result_file.is_open()) {
            result_file << data_to_save.dump(4); // dump(4) means 4 additional spaces
            result_file.close();
            std::cout << "Data saved." << std::endl;
        } else {
            std::cerr << "Could not save data" << std::endl;
        }

        return 0;
    }
} //GUI