#include "GUI.hpp"
#include "city.hpp"
#include <iostream>
#include <tabu.hpp>
#include <chrono>

//pamietac o zmianie AMBULANCE_NUMBER


int AMBULANCE_NUMBER = 8;

int main(){
    GUI::loadData();
    GUI::loadHospitals();
    // Początkowy czas
    auto start = std::chrono::high_resolution_clock::now();


    Ambulance *new_ambulance1 = new Ambulance(hospital_list[0]);
    Ambulance *new_ambulance2 = new Ambulance(hospital_list[1]);
    Ambulance *new_ambulance3 = new Ambulance(hospital_list[2]);
    Ambulance *new_ambulance4 = new Ambulance(hospital_list[0]);
    Ambulance *new_ambulance5 = new Ambulance(hospital_list[1]);
    Ambulance *new_ambulance6 = new Ambulance(hospital_list[2]);
    Ambulance *new_ambulance7 = new Ambulance(hospital_list[0]);
    Ambulance *new_ambulance8 = new Ambulance(hospital_list[1]);
    ambulance_list.push_back(new_ambulance1);
    ambulance_list.push_back(new_ambulance2);
    ambulance_list.push_back(new_ambulance3);
    ambulance_list.push_back(new_ambulance4);
    ambulance_list.push_back(new_ambulance5);
    ambulance_list.push_back(new_ambulance6);
    ambulance_list.push_back(new_ambulance7);
    ambulance_list.push_back(new_ambulance8);

    Patient pat_1(0,6,10,2, GUI::specializations,std::vector<int>{6,0,0,0,0,0,4,0,0,0,0,0,0});
    Patient pat_2(1,1,30,2, GUI::specializations,std::vector<int>{0,0,4,0,0,0,0,0,0,0,0,1,0});
    Patient pat_3(0,4,20,5, GUI::specializations,std::vector<int>{0,0,0,5,0,0,0,0,0,0,9,0,0});
    Patient pat_4(0,3,10,3, GUI::specializations,std::vector<int>{0,5,0,0,0,0,0,0,0,0,0,0,0});
    Patient pat_5(1,4,5,2, GUI::specializations,std::vector<int>{0,0,0,0,6,0,9,0,0,0,0,0,0});
    Patient pat_6(0,6,30,6, GUI::specializations,std::vector<int>{0,0,0,0,0,0,6,0,0,3,0,0,0});
    Patient pat_7(1,1,30,4, GUI::specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,6,0,0});
    Patient pat_8(0,4,20,2, GUI::specializations,std::vector<int>{0,0,0,0,8,8,0,0,0,0,0,0,0});
    Patient pat_9(0,3,25,4, GUI::specializations,std::vector<int>{0,4,0,0,0,0,0,4,0,0,0,0,0});
    Patient pat_10(1,4,5,1, GUI::specializations,std::vector<int>{6,0,0,0,0,0,0,0,6,0,0,0,0});
    Patient pat_11(0,6,17,5, GUI::specializations,std::vector<int>{0,0,4,4,0,0,0,0,0,0,0,0,0});
    Patient pat_12(1,1,23,4, GUI::specializations,std::vector<int>{7,0,0,0,0,0,0,0,0,7,0,0,0});
    Patient pat_13(0,4,6,1, GUI::specializations,std::vector<int>{0,0,0,5,0,0,0,2,0,0,0,0,0});
    Patient pat_14(0,3,51,8, GUI::specializations,std::vector<int>{0,0,9,0,0,0,9,0,0,0,0,0,0});
    Patient pat_15(1,4,50,8, GUI::specializations,std::vector<int>{0,9,0,0,0,9,0,0,0,0,0,0,0});
    Patient pat_16(0,6,21,4, GUI::specializations,std::vector<int>{0,0,6,0,6,0,0,0,0,6,0,0,0});
    Patient pat_17(1,1,41,3, GUI::specializations,std::vector<int>{0,0,0,0,4,4,0,0,0,0,0,0,0});
    Patient pat_18(0,4,21,7, GUI::specializations,std::vector<int>{0,0,5,0,0,4,0,0,8,0,0,0,0});
    Patient pat_19(0,3,16,4, GUI::specializations,std::vector<int>{0,0,2,0,0,0,2,0,0,0,0,0,0});
    Patient pat_20(1,4,19,6, GUI::specializations,std::vector<int>{0,0,0,0,0,0,0,0,0,0,0,0,9});


    patients_list.push_back(&pat_1);
    patients_list.push_back(&pat_2);
    patients_list.push_back(&pat_3);
    patients_list.push_back(&pat_4);
    patients_list.push_back(&pat_5);
    patients_list.push_back(&pat_6);
    patients_list.push_back(&pat_7);
    patients_list.push_back(&pat_8);
    patients_list.push_back(&pat_9);
    patients_list.push_back(&pat_10);
    patients_list.push_back(&pat_11);
    patients_list.push_back(&pat_12);
    patients_list.push_back(&pat_13);
    patients_list.push_back(&pat_14);
    patients_list.push_back(&pat_15);
    patients_list.push_back(&pat_16);
    patients_list.push_back(&pat_17);
    patients_list.push_back(&pat_18);
    patients_list.push_back(&pat_19);
    patients_list.push_back(&pat_20);

    TabuSearch Tabu_object;
    std::vector<Ambulance*> wynik = Tabu_object.TabuSearchAlghoritm();

    int index_ambulansu = 1;
    for(auto karetka: wynik){
        for(auto pacjent: karetka->getOrder()){
            if (pacjent == nullptr){
                break;
            }
            std::cout << "Ambulans " << index_ambulansu << " Pacjent: " << pacjent->getPatientId() << std::endl;
        }
        index_ambulansu++;
    }

    // Końcowy czas
    auto end = std::chrono::high_resolution_clock::now();
    // Obliczenie różnicy czasu
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    GUI::execution_time = (int)duration.count();

    GUI::saveData();

    return 0;
}