#include "GUI.hpp"
#include "Configuration_data.hpp"
#include "city.hpp"
#include <iostream>
#include <tabu.hpp>
#include <chrono>


int main(){
    GUI::loadData();
    Config_Data::loadConfigData();

    //Start Time
    const auto start = std::chrono::high_resolution_clock::now();

    TabuSearch Tabu_object;
    std::vector<Ambulance*> wynik = Tabu_object.TabuSearchAlghoritm();

    int index_ambulansu = 1;
    for(const auto karetka: wynik){
        for(const auto pacjent: karetka->getOrder()){
            if (pacjent == nullptr){
                break;
            }
            std::cout << "Ambulans " << index_ambulansu << " Pacjent: " << pacjent->getPatientId() << std::endl;
        }
        index_ambulansu++;
    }

    //End Time
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);


    GUI::execution_time = static_cast<int>(duration.count());
    GUI::saveData();

    return 0;
}