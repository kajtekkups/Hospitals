// ReSharper disable CppTooWideScopeInitStatement
// ReSharper disable CppParameterMayBeConstPtrOrRef
#include "tabu.hpp"
#include "GUI.hpp"
#include "Configuration_data.hpp"
#include <ctime>
#include <limits>
#include "city.hpp"

//Tabulist
void TabuList::updateTabu(const std::map<Ambulance, swap_patient_index> &pairs){
    if (save_index >= tabu_list_size_-1){
        save_index = 0;
    }
    else{
        for (const auto&[tabu_ambulance_id, patient_que_number] : pairs) {
            const std::tuple<ambulance_id, patient_id, swap_patient_index> tabu_element(tabu_ambulance_id.getID(), tabu_ambulance_id.getPatientID(patient_que_number), patient_que_number);
            tabu_l[save_index] = (tabu_element);
            save_index = save_index + 1;
        }
    }
};

int TabuList::checkIfInTabu(std::pair<Ambulance, swap_patient_index> const &pair1, std::pair<Ambulance, swap_patient_index> const &pair2) const {

    const std::tuple<ambulance_id, patient_id, swap_patient_index> check_config_1(pair1.first.getID(), pair1.first.getPatientID(pair1.second), pair1.second);
    const std::tuple<ambulance_id, patient_id, swap_patient_index> check_config_2(pair2.first.getID(), pair2.first.getPatientID(pair2.second), pair2.second);

    for(int i=0; i < save_index; i = i+2){
        if((tabu_l[i] == check_config_1 and tabu_l[i+1] == check_config_2) or (tabu_l[i] == check_config_2 and tabu_l[i+1] == check_config_1))
            return IN_TABU;
    }
    return NOT_IN_TABU;
}


//Changes which Ambulance is responsible for which patients (in this case, swaps patients between ambulances)
void TabuSearch::swapPatients(Ambulance &amb1, Ambulance &amb2, const int patient1_idx, const int patient2_idx) {

    std::vector<Patient*> order1 = amb1.getOrder();
    std::vector<Patient*> order2 = amb2.getOrder();

    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;

    amb1.newOrder(order1);
    amb2.newOrder(order2);
}


operation_cost TabuSearch::ObjectiveFunction(std::vector<Ambulance*> const &solution){
    int final_cost = 0;

    for (const auto ambulance : solution){
        Point ambulance_location = {ambulance->getAmbulanceLocationX(), ambulance->getAmbulanceLocationY(), 0};

        for (const auto patient : ambulance->getOrder()){
            if (patient == nullptr){
                break;
            }

            const int patient_time = patient->getTime();
            Point patient_location = {patient->getLocationX(), patient ->getLocationY(), 0};

            const Hospital* best_hospital = get_best_hospital(patient); //chose hospital that would take care of patient
            Point hospital_location = {best_hospital->getHospitalLocationX(), best_hospital->getHospitalLocationY(), 0};

            //calculate costs of operations for current patient
            const int amb_to_pat_time = BFS(city, ambulance_location, patient_location);
            const int pat_to_hosp_time = BFS(city, patient_location, hospital_location);

            const int patient_priority = patient->getPriority();
            final_cost = final_cost + patient_priority * (patient_time + amb_to_pat_time) + pat_to_hosp_time;

            ambulance_location = hospital_location;
        }
    }
    return final_cost;
}

//chose 2 random ambulances and change random patients
// ReSharper disable once CppParameterMayBeConstPtrOrRef
std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> TabuSearch::FirstNeighbour(std::vector<Ambulance*>& solution, int* aspiration_on) {
    std::map<Ambulance, swap_patient_index> neigh_swaped;
    operation_cost first_neighbour_cost;

    //chose 2 random ambulances and change random patients
    srand(time(nullptr));

    while(true) {
        const int ambulance_idx1 = rand() % Config_Data::ambulance_number;   //chose random ambulance
        int ambulance_idx2 = rand() % Config_Data::ambulance_number;

        while (ambulance_idx2 == ambulance_idx1) {
            ambulance_idx2 = rand() % Config_Data::ambulance_number;
        }

        const int number_of_patients_idx1 = solution[ambulance_idx1]->getPatientCount();  //liczba pacjentów dla wybranych losowo karetek
        const int number_of_patients_idx2 = solution[ambulance_idx2]->getPatientCount();

        const int patient_idx1 = rand() % number_of_patients_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
        const int patient_idx2 = rand() % number_of_patients_idx2;

        std::pair<Ambulance, swap_patient_index> pair1(*solution[ambulance_idx1], patient_idx1);
        std::pair<Ambulance, swap_patient_index> pair2(*solution[ambulance_idx2], patient_idx2);

        if(!Tabu.checkIfInTabu(pair1, pair2)) {
            swapPatients(*solution[ambulance_idx1], *solution[ambulance_idx2], patient_idx1, patient_idx2);
            first_neighbour_cost = ObjectiveFunction(solution);
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx1],patient_idx1));
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx2],patient_idx2));
            break;
        } else if constexpr (false) {
            // TODO: uzupelnic aspiration criteria
            //GUI::aspiration_criterion != 0
        }
    }

    return std::make_tuple(neigh_swaped, first_neighbour_cost);
}


// move patient from one ambulance to another
std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> TabuSearch::SecondNeighbour(std::vector<Ambulance*>& solution, int* aspiration_on) {
    std::map<Ambulance, swap_patient_index> neigh_swaped;
    operation_cost second_neighbour_cost;

    //chose 2 random ambulances and change random patients
    srand(time(nullptr));

    while(true) {
        const int ambulance_idx1 = rand() % Config_Data::ambulance_number;   //chose random ambulance
        int ambulance_idx2 = rand() % Config_Data::ambulance_number;

        while (ambulance_idx2 == ambulance_idx1) {
            ambulance_idx2 = rand() % Config_Data::ambulance_number;
        }

        if(solution[ambulance_idx1]->getPatientCount() == 1 or solution[ambulance_idx1]->getPatientCount() == 1) continue;

        const int number_of_patients_idx1 = solution[ambulance_idx1]->getPatientCount();  //liczba pacjentów dla wybranych losowo karetek

        const int patient_idx1 = rand() % number_of_patients_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek

        std::pair<Ambulance, swap_patient_index> pair1(*solution[ambulance_idx1], -1);
        std::pair<Ambulance, swap_patient_index> pair2(*solution[ambulance_idx2], 0);

        if(!Tabu.checkIfInTabu(pair1, pair2)) {
            Patient* deleted_patient = solution[ambulance_idx1]->deletePatient(patient_idx1);
            solution[ambulance_idx2]->add_patient(deleted_patient);

            second_neighbour_cost = ObjectiveFunction(solution);
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx1],-1));
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx2],0));
            break;
        } else if constexpr (false) {
            // TODO: uzupelnic aspiration criteria
            //GUI::aspiration_criterion != 0
        }
    }

    return std::make_tuple(neigh_swaped, second_neighbour_cost);
}


//trzeba uzyc kilku sasiedztw naraz
NeighbourSelectResult TabuSearch::NeighbourSelect(std::array<std::vector<Ambulance*>, NUMBER_OF_NEIGHBOURS>& solutions, int* aspiration_on) {
    std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> chosen_neighbour;
    std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> temporary_neighbour;
    best_result_solution index;

    //1. neighbour
    if(GUI::neighborhood_selection_method[FIRST_NEIGH]) {
        chosen_neighbour = FirstNeighbour(solutions[FIRST_NEIGH], aspiration_on);
        index = FIRST_NEIGH;
    }

    //2. neighbour
    if(GUI::neighborhood_selection_method[SECOND_NEIGH]) {
        temporary_neighbour = FirstNeighbour(solutions[SECOND_NEIGH], aspiration_on);
        if(std::get<1>(chosen_neighbour) > std::get<1>(temporary_neighbour)) {
            chosen_neighbour = temporary_neighbour;
            index = SECOND_NEIGH;
        }
    }

    //3. Neighbour
    if(GUI::neighborhood_selection_method[THIRD_NEIGH]) {
        temporary_neighbour = SecondNeighbour(solutions[THIRD_NEIGH], aspiration_on);
        if(std::get<1>(chosen_neighbour) > std::get<1>(temporary_neighbour)) {
            chosen_neighbour = temporary_neighbour;
            index = THIRD_NEIGH;
        }
    }

    if(GUI::neighborhood_selection_method[FOURTH_NEIGH]) {
        temporary_neighbour = SecondNeighbour(solutions[FOURTH_NEIGH], aspiration_on);
        if(std::get<1>(chosen_neighbour) > std::get<1>(temporary_neighbour)) {
            chosen_neighbour = temporary_neighbour;
            index = FOURTH_NEIGH;
        }
    }

    return {std::get<0>(chosen_neighbour), std::get<1>(chosen_neighbour), index};
}


void TabuSearch::createFirstSolution(){
    int counter = 0;
    for (auto patient : patients_list){
        ambulance_list[counter]->add_patient(patient);
        counter++;
        if (counter == static_cast<int>(ambulance_list.size())){
            counter = 0;
        }
}}

void TabuSearch::copyAmbulanceVector(const std::vector<Ambulance*>& orginal, std::vector<Ambulance*>& to_delete){
    // wyczysc wektor do ktorego kopiujemy
    for (auto & del : to_delete){
        delete del;
    }
    to_delete.clear();

    // skoopiuj wartosci
    for (Ambulance *ambulance: orginal) {
        Ambulance *clonedAmbulance = new Ambulance(*ambulance);
        to_delete.push_back(clonedAmbulance);
    }
}


std::vector<Ambulance*> TabuSearch::TabuSearchAlghoritm() {
    //Initialize
    createFirstSolution();

    std::vector<Ambulance*> iterations_best_solution;
    copyAmbulanceVector(ambulance_list, iterations_best_solution);
    std::array<std::vector<Ambulance*>, NUMBER_OF_NEIGHBOURS>  potential_solutions; //create containers for all possible solutions

    int iterations_without_improvement = 0;

    for (int i = 0; i < GUI::max_iteration; i++){
        GUI::iterations_number++;

        int aspiration_on[NUMBER_OF_NEIGHBOURS] = {0};


        // 1. set best result to all containers
        for(int j = 0; j < NUMBER_OF_NEIGHBOURS; j++) {
            copyAmbulanceVector(iterations_best_solution, potential_solutions[j]);
        }

        // 2. find new solutions
        NeighbourSelectResult best_temporary_solution = NeighbourSelect(potential_solutions, aspiration_on);


        // 3. chose best solutions in this iteration
        const operation_cost iteration_best_result = best_temporary_solution.cost;
        copyAmbulanceVector(potential_solutions[best_temporary_solution.solution_index], iterations_best_solution);


        // 4. if it is best solution of all time, update the results
        if(GUI::best_result > iteration_best_result){
            copyAmbulanceVector(iterations_best_solution, ambulance_list);
            GUI::best_result = iteration_best_result;
            GUI::best_result_iteration = GUI::iterations_number;
        }

        //5. update tabu list
        Tabu.updateTabu(best_temporary_solution.swap_patient);

        //6. save GUI data
        GUI::single_results[GUI::iterations_number-1] = static_cast<int>(iteration_best_result);


        if(GUI::best_result == iteration_best_result){
            iterations_without_improvement++;
        }
        if(iterations_without_improvement == 100){
            return iterations_best_solution;
        }
    }

    return iterations_best_solution;
}
