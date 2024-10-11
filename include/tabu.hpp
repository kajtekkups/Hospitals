#ifndef HOSPITALS_TABU_HPP
#define HOSPITALS_TABU_HPP


#include "Ambulance.hpp"
#include "Patient.hpp"
#include "GUI.hpp"
#include <map>
#include <vector>

#define NOT_IN_TABU 0
#define IN_TABU 1

#define FIRST_NEIGH 0
#define SECOND_NEIGH 1
#define THIRD_NEIGH 2
#define FOURTH_NEIGH 3

#define NUMBER_OF_NEIGHBOURS 4


typedef int swap_patient_index;  //identifies patient of particular ambulance, that is going to be swapt
typedef int operation_cost;
typedef int best_result_solution;


struct NeighbourSelectResult {
    std::map<Ambulance, swap_patient_index> swap_patient;
    operation_cost cost;
    best_result_solution solution_index;
};


class TabuList{
public:
    explicit TabuList(const int size): tabu_list_size_(size * 2), tabu_l(size*2){
        // for (int i = 0; i < (size*2); i++) {
        //     Ambulance amb(-1);
        //     tabu_l.emplace_back(amb, -1, -1);
        // }
    }

//dodaje dwie pary do listy tabu, jesli jest zapelniona dodaje od poczatku
    void updateTabu(const std::map<Ambulance, swap_patient_index> &pairs);

    [[nodiscard]] int checkIfInTabu(std::pair<Ambulance, swap_patient_index> const &pair1, std::pair<Ambulance, swap_patient_index> const &pair2) const;

private:
    int tabu_list_size_;
    std::vector<std::tuple<ambulance_id, patient_id, swap_patient_index>> tabu_l;
    int save_index = 0;
};


class TabuSearch {
public:
    TabuSearch(): Tabu(GUI::tabu_list_length){}

    static void swapPatients(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx);

    static operation_cost ObjectiveFunction(std::vector<Ambulance*> const &solution);

    std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> FirstNeighbour(std::vector<Ambulance*>& solution);

    std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> SecondNeighbour(std::vector<Ambulance*>& solution);

    NeighbourSelectResult NeighbourSelect(std::array<std::vector<Ambulance*>, NUMBER_OF_NEIGHBOURS>& solutions);

    static void createFirstSolution();

    static void copyAmbulanceVector(const std::vector<Ambulance*>& orginal, std::vector<Ambulance*>& to_delete);

    std::vector<Ambulance*> TabuSearchAlghoritm();

private:
    TabuList Tabu;
};








#endif //HOSPITALS_TABU_HPP



