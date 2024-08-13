#include "tabu.hpp"
#include "GUI.hpp"
#include <queue>
#include <ctime>
#include <limits>

#define NOT_IN_TABU 0
#define IN_TABU 1

#define FIRST_NEIGH 0
#define SECOND_NEIGH 1
#define THIRD_NEIGH 2
#define FOURTH_NEIGH 3

#define NUMBER_OF_NEIGHBOURS 4

double cost = 0;
int iteration = 0;

std::vector<std::string> specializations = {
        "Ortopedia",
        "Okulistyka",
        "Neurologia",
        "Chirurgia",
        "Kardiologia",
        "Pediatria",
        "Endokrynologia",
        "Geriatria",
        "Ginekologia",
        "Urologia",
        "Psychiatria",
        "Oparzenia",
        "Gastroenterologia"};

//sprawdzilem swapa, get_best_hospital i objectivefunction - dzialaja poprawnie

std::vector<std::vector<int>> city {
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 2, 0, 0 ,0, 3, 0, 0, 0 ,0, 1, 0, 0, 0, 3 ,0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1 ,2, 0, 0, 0, 0},
        {1, 0, 1, 1, 0 ,0, 2, 0, 0, 0 ,0, 1, 0, 0, 0, 1 ,1, 0, 0, 0, 0 ,0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 2, 0, 0, 0 ,0, 1 ,1, 2, 2, 0, 0},
        {1, 0, 0, 1, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0 ,1, 2, 1, 1, 1 ,1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1 ,1, 1, 0, 0, 2 ,2, 1 ,0, 0, 1, 0, 0},
        {1, 0, 0, 2, 2 ,1, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0 ,2, 0, 0, 0, 0 ,0, 1, 0, 1, 1, 2, 2, 2, 2, 0, 0, 0, 1, 0, 2, 0, 0 ,0, 0, 0, 2, 2 ,0, 1 ,0, 0, 2, 1, 0},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 2, 0, 0 ,0, 0, 0, 2, 0 ,0, 1 ,0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 0, 0, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 2, 0, 0, 0},
        {1, 0, 0, 0, 0 ,0, 0, 1, 3, 0 ,0, 1, 0, 0, 0, 0 ,0, 1, 2, 2, 1 ,1, 1, 1, 2, 1, 2, 3, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 2, 2, 0, 0},
        {1, 3, 1, 0, 0 ,0, 0, 1, 0, 0 ,0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 3, 2, 3, 1 ,1, 1, 2, 2, 1 ,2, 1 ,0, 0, 2, 0, 0},
        {1, 0, 2, 0, 0 ,0, 0, 1, 1, 1 ,0, 1, 0, 0, 0, 0 ,0, 2, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 0, 1, 1, 1},
        {1, 0, 3, 0, 0 ,0, 0, 0, 0, 2 ,0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 2, 0, 0 ,0, 2, 0, 0, 0 ,0, 1, 0, 2, 0, 0 ,0, 1, 0, 2, 0 ,0, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 ,0, 0, 2, 0, 0 ,0, 1 ,0, 0, 0, 2, 0},
        {1, 0, 1, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 2, 0, 0 ,0, 2, 0, 2, 0 ,0, 1, 2, 1, 0, 0, 1, 0, 0, 0, 2, 0, 1, 0, 2, 0, 1 ,2, 1, 1, 0, 0 ,0, 1 ,0, 0, 0, 1, 0},
        {1, 0, 1, 2, 2 ,1, 1, 0, 0, 0 ,0, 1, 2, 1, 1, 1 ,2, 1, 2, 1, 1 ,1, 1, 0, 1, 0, 0, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2 ,0, 0, 2, 0, 0 ,0, 1 ,0, 0, 0, 1, 0},
        {1, 0, 0, 0, 1 ,0, 2, 0, 0, 0 ,0, 1, 0, 1, 0, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 1, 1, 1, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2 ,0, 0, 1, 1, 1 ,1, 1 ,1, 2, 2, 1, 0},
        {1, 0, 0, 0, 1 ,0, 2, 0, 0, 0 ,0, 1, 0, 2, 0, 0 ,0, 0, 0, 1, 0 ,0, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 ,0, 0, 1, 0, 0 ,0, 1 ,0, 0, 0, 2, 0},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1 ,0, 1, 0, 1, 0, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 1, 0, 2, 0, 0 ,1, 0, 0, 1, 0 ,0, 1 ,0, 2, 0, 0, 1},
        {1, 2, 1, 2, 0, 2, 0, 0, 0, 2 ,1, 1, 0, 2, 0, 0 ,0, 0, 0, 1, 0 ,0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 2, 0, 1, 0, 2, 0, 0 ,2, 1, 1, 2, 1 ,1, 1 ,0, 2, 0, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 2, 1, 1 ,2, 1, 1, 1, 2, 1 ,2, 1, 1, 2, 1 ,1, 1, 2, 2, 1, 0, 0, 0, 2, 1, 1, 2, 1, 1, 1, 2, 1 ,2, 0, 0, 0, 2 ,0, 1 ,1, 1, 2, 1, 2},
        {1, 0, 0, 1, 0 ,0, 2, 0, 0, 1 ,0, 1, 0, 0, 1, 0 ,0, 0, 0, 1, 0 ,0, 1, 0, 0, 1, 1, 2, 1, 2, 0, 0, 0, 1, 0, 1, 0, 0 ,1, 0, 0, 0, 2 ,0, 1 ,0, 2, 0, 0, 2},
        {1, 0, 0, 2, 0 ,0, 1, 0, 0, 2 ,0, 1, 0, 0, 2, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 0 ,2, 0, 0, 0, 1 ,0, 1 ,0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
};

//Funkcje
//lista wszsystkich szpitali, trzeba ja kiedys stworzyc
std::vector<Hospital*> hospital_list;

//lista wszystkich pacjentow
std::vector<Patient*> patients_list;

//lista wszystkich karetek
std::vector<Ambulance*> ambulance_list;

int apiration_usage_counter;

bool isValid(int x, int y, std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited) {
    return (x >= 0 && x < CITY_LENGTH && y >= 0 && y < CITY_HEIGTH && grid[x][y] && !visited[x][y]);
}

//Funkcja do znajdowania najkrotszej drogi miedzy punktami w miescie, miasto jako
//pionowe i poziome drogi (tam jakas wartosc np 1) miejsca nieosiagalne jako 0
int BFS(std::vector<std::vector<int>>& grid, const Point& start, const Point& end) {
    std::vector<std::vector<bool>> visited(CITY_LENGTH, std::vector<bool>(CITY_HEIGTH, false));
    std::queue<Point> q;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    q.push(start);
    visited[start.x][start.y] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y) {
            return current.distance; // Zwraca ilość kroków do celu
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, grid, visited)) {
                visited[newX][newY] = true;
                q.push({newX, newY, current.distance + grid[newX][newY]});
            }
        }
    }
    return -1; // Brak ścieżki
}


//funckja szukajaca odpowiedniego szpitala dla pacjenta, zwraca ten szpital
//najlepszy pod wzgledem czasu

Hospital* get_best_hospital(Patient *pat){
    std::vector<Hospital*> spec_hospital;
    std::map<std::string, int> patient_injuries = pat -> getInjuriesList();

    for (auto hospital : hospital_list){
        int correct = 1;
        std::map<std::string, int> spec = hospital->getSpecializationList();
        for (auto injurie : patient_injuries){
            if (spec[injurie.first] < patient_injuries[injurie.first]){
                correct = 0;
                break;
            }
        }
        if (correct == 1){
            spec_hospital.push_back(hospital);
        }
    }

    int min_time = 9999999;
    Hospital* besthospital = spec_hospital[0];

    for (auto hospital : spec_hospital){
        Point hosp_loc = Point{hospital->getHospitalLocationX(), hospital->getHospitalLocationY(), 0};
        Point patient_loc = Point{pat->getLocationX(), pat->getLocationY(), 0};
        int travel_time = BFS(city, patient_loc, hosp_loc);
        if (min_time > travel_time) {
            besthospital = hospital;
        }
    }
    return besthospital;
}

//Tabulist

void TabuList::update_tabu(const std::map<Ambulance, swap_patient_index> &pairs){
    if (save_index >= tabu_list_size_-1){
        save_index = 0;
    }
    else{
        for (const auto& pair : pairs) {
            std::tuple<ambulance_id, patient_id, swap_patient_index> tabu_element(pair.first.getID(), pair.first.getPatientID(pair.second), pair.second);
            tabu_l[save_index] = (tabu_element);
            save_index = save_index + 1;
        }
    }
};

int TabuList::check_if_in_tabu(std::pair<Ambulance, swap_patient_index> const &pair1, std::pair<Ambulance, swap_patient_index> const &pair2){

    std::tuple<ambulance_id, patient_id, swap_patient_index> check_config_1(pair1.first.getID(), pair1.first.getPatientID(pair1.second), pair1.second);
    std::tuple<ambulance_id, patient_id, swap_patient_index> check_config_2(pair2.first.getID(), pair2.first.getPatientID(pair2.second), pair2.second);

    for(int i=0; i < save_index; i = i+2){
        if(tabu_l[i] == check_config_1 and tabu_l[i+1] == check_config_2) {
            return IN_TABU;
        }else if(tabu_l[i] == check_config_2 and tabu_l[i+1] == check_config_1) {
            return IN_TABU;
        }
    }
    return NOT_IN_TABU;

}

//Changes which Ambulance is responsible for which patients (in this case, swaps patients between ambulances)
void swapPatients(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx) {

    std::vector<Patient*> order1 = amb1.get_order();
    std::vector<Patient*> order2 = amb2.get_order();

    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;

    amb1.newOrder(order1);
    amb2.newOrder(order2);
}


/* Sasiedztwa  (przez dostępnych pacjentów rozumie sie ze nie ma ich w liscie tabu)
1 - wymiana zawsze pierwszych z wolnych pacjentow miedzy losowymi karetkami
2 - wymiana losowych dostępnych pacjentów między losowymi karetkami
3 - przerzucenie pacjenta
4 - co x iteracje przerzuca pacjenta, tak to zamienia losowo

*/

//funkcja celu
operation_cost ObjectiveFunction(std::vector<Ambulance*> const &solution){
    int final_cost = 0;

    for (auto ambulance : solution){
        Point ambulance_location = {ambulance->getAmbulanceLocationX(), ambulance->getAmbulanceLocationY(), 0};
        int sum_time = 0;

        for (auto patient : ambulance->get_order()){
            if (patient == nullptr){
                break;
            }

            int patient_time = patient->getTime();
            Point patient_location = {patient->getLocationX(), patient ->getLocationY(), 0};

            Hospital* best_hospital = get_best_hospital(patient); //chose hospital that would take care of patient
            Point hospital_location = {best_hospital->getHospitalLocationX(), best_hospital->getHospitalLocationY(), 0};

            //calculate costs of operations for current patient
            int amb_to_pat_time = BFS(city, ambulance_location, patient_location);
            int pat_to_hosp_time = BFS(city, patient_location, hospital_location);

            int patient_priority = patient->getPriority();
            final_cost = final_cost + patient_priority * (patient_time + amb_to_pat_time) + pat_to_hosp_time + sum_time;

            ambulance_location = hospital_location;
        }
    }
    return final_cost;
}

//chose 2 random ambulances and change random patients
std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> FirstNeighbour(TabuList Tabu, std::vector<Ambulance*>& solution, int* aspiration_on) {
    std::map<Ambulance, swap_patient_index> neigh_swaped;
    operation_cost first_neighbour_cost;

    //chose 2 random ambulances and change random patients
    srand(time(nullptr));
    int ambulance_idx1;
    int ambulance_idx2;
    int number_of_patients_idx1;
    int number_of_patients_idx2;
    int patient_idx1;
    int patient_idx2;

    while(true) {
        ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //chose random ambulance
        ambulance_idx2 = rand() % AMBULANCE_NUMBER;

        while (ambulance_idx2 == ambulance_idx1) {
            ambulance_idx2 = rand() % AMBULANCE_NUMBER;
        }

        number_of_patients_idx1 = solution[ambulance_idx1]->getPatientCount();  //liczba pacjentów dla wybranych losowo karetek
        number_of_patients_idx2 = solution[ambulance_idx2]->getPatientCount();

        patient_idx1 = rand() % number_of_patients_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
        patient_idx2 = rand() % number_of_patients_idx2;

        std::pair<Ambulance, swap_patient_index> pair1(*solution[ambulance_idx1], patient_idx1);
        std::pair<Ambulance, swap_patient_index> pair2(*solution[ambulance_idx2], patient_idx2);

        if(!Tabu.check_if_in_tabu(pair1, pair2)) {
            swapPatients(*solution[ambulance_idx1], *solution[ambulance_idx2], patient_idx1, patient_idx2);
            first_neighbour_cost = ObjectiveFunction(solution);
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx1],patient_idx1));
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx2],patient_idx2));
            break;
        } else if (-1) {
            // TODO: uzupelnic aspiration criteria
            //GUI::aspiration_criterion != 0
        }
    }

    return std::make_tuple(neigh_swaped, first_neighbour_cost);
}


// move patient from one ambulance to another
std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> SecondNeighbour(TabuList Tabu, std::vector<Ambulance*>& solution, int* aspiration_on) {
    std::map<Ambulance, swap_patient_index> neigh_swaped;
    operation_cost second_neighbour_cost;

    //chose 2 random ambulances and change random patients
    srand(time(nullptr));
    int ambulance_idx1;
    int ambulance_idx2;
    int number_of_patients_idx1;
    int number_of_patients_idx2;
    int patient_idx1;
    int patient_idx2;

    while(true) {
        ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //chose random ambulance
        ambulance_idx2 = rand() % AMBULANCE_NUMBER;

        while (ambulance_idx2 == ambulance_idx1) {
            ambulance_idx2 = rand() % AMBULANCE_NUMBER;
        }

        if(solution[ambulance_idx1]->getPatientCount() == 1 or solution[ambulance_idx1]->getPatientCount() == 1) continue;

        number_of_patients_idx1 = solution[ambulance_idx1]->getPatientCount();  //liczba pacjentów dla wybranych losowo karetek

        patient_idx1 = rand() % number_of_patients_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek

        std::pair<Ambulance, swap_patient_index> pair1(*solution[ambulance_idx1], -1);
        std::pair<Ambulance, swap_patient_index> pair2(*solution[ambulance_idx2], 0);

        if(!Tabu.check_if_in_tabu(pair1, pair2)) {
            Patient* deleted_patient;
            deleted_patient = solution[ambulance_idx1]->delete_patient(patient_idx1);
            solution[ambulance_idx2]->add_patient(deleted_patient);

            second_neighbour_cost = ObjectiveFunction(solution);
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx1],-1));
            neigh_swaped.insert(std::make_pair(*solution[ambulance_idx2],0));
            break;
        } else if (-1) {
            // TODO: uzupelnic aspiration criteria
            //GUI::aspiration_criterion != 0
        }
    }

    return std::make_tuple(neigh_swaped, second_neighbour_cost);
}


//trzeba uzyc kilku sasiedztw naraz
NeighbourSelectResult NeighbourSelect(TabuList Tabu, std::array<std::vector<Ambulance*>, NUMBER_OF_NEIGHBOURS>& solutions, int* aspiration_on) {
    std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> chosen_neighbour;
    std::tuple<std::map<Ambulance, swap_patient_index>, operation_cost> temporary_neighbour;
    best_result_solution index;

    //1. neighbour
    if(GUI::neighborhood_selection_method[FIRST_NEIGH]) {
        chosen_neighbour = FirstNeighbour(Tabu, solutions[FIRST_NEIGH], aspiration_on);
        index = FIRST_NEIGH;
    }

    //2. neighbour
    if(GUI::neighborhood_selection_method[SECOND_NEIGH]) {
        temporary_neighbour = FirstNeighbour(Tabu, solutions[SECOND_NEIGH], aspiration_on);
        if(std::get<1>(chosen_neighbour) > std::get<1>(temporary_neighbour)) {
            chosen_neighbour = temporary_neighbour;
            index = SECOND_NEIGH;
        }
    }

    //3. Neighbour
    if(GUI::neighborhood_selection_method[THIRD_NEIGH]) {
        temporary_neighbour = SecondNeighbour(Tabu, solutions[THIRD_NEIGH], aspiration_on);
        if(std::get<1>(chosen_neighbour) > std::get<1>(temporary_neighbour)) {
            chosen_neighbour = temporary_neighbour;
            index = THIRD_NEIGH;
        }
    }

    if(GUI::neighborhood_selection_method[FOURTH_NEIGH]) {
        temporary_neighbour = SecondNeighbour(Tabu, solutions[FOURTH_NEIGH], aspiration_on);
        if(std::get<1>(chosen_neighbour) > std::get<1>(temporary_neighbour)) {
            chosen_neighbour = temporary_neighbour;
            index = FOURTH_NEIGH;
        }
    }

    return {std::get<0>(chosen_neighbour), std::get<1>(chosen_neighbour), index};
}


void create_first_solution(){
    int counter = 0;
    for (auto patient : patients_list){
        ambulance_list[counter]->add_patient(patient);
        counter++;
        if (counter == ambulance_list.size()){
            counter = 0;
        }
}}

void copy_ambulance_vector(std::vector<Ambulance*> orginal, std::vector<Ambulance*>& to_delete){
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


//algorytm tabu
std::vector<Ambulance*> TabuSearch() {
    //tworzenie tabu listy
    TabuList tabu_l = TabuList(GUI::tabu_list_length);
    //Inicjalizowanie pierwszego rozwiązania
    create_first_solution();
    //tu trzeba bedzie sprawdzic czy kopiuje czy bedzie sie zmienial razem z ambulacne list
    std::vector<Ambulance*> global_solution;
    copy_ambulance_vector(ambulance_list, global_solution);
    // tworzymy tyle rozwiazan, ile mamy opcji wyboru sasiedztwa
    std::array<std::vector<Ambulance*>, NUMBER_OF_NEIGHBOURS>  potential_solutions;

    //liczba iteracji bez poprawy wyniku
    int iterations_without_improvement = 0;

    for (int i = 0; i < GUI::max_iteration; i++){
        GUI::iterations_number++;

        int aspiration_on[NUMBER_OF_NEIGHBOURS] = {0};
        int final_aspiration = 0;


        // 1. stworz kopie ostatniego najlepszego rozwiazania
        for(int i = 0; i < NUMBER_OF_NEIGHBOURS; i++) {
            copy_ambulance_vector(global_solution, potential_solutions[i]);
        }

        // 2. stworz nowe rozwiazania
        //wybierz nowe sasiedztwa
        NeighbourSelectResult best_temporary_solution = NeighbourSelect(tabu_l, potential_solutions, aspiration_on);


        // 3. oblicz wartosci funkcji celu
        int cost_temp_solution[NUMBER_OF_NEIGHBOURS];
        for(int i = 0; i < NUMBER_OF_NEIGHBOURS; i++) {
            cost_temp_solution[i] = ObjectiveFunction(potential_solutions[i]);
        }

        // 4. wyeliminuj rozwiazania sasiedztw nie branych pod uwage
        //    (moglo by to byc bardziej optymalne, ale jest to tymczasowe rozwiazanie oszczedzajace czas)
        for(int i = 0; i < NUMBER_OF_NEIGHBOURS; i++) {
            if(!GUI::neighborhood_selection_method[i]){
                cost_temp_solution[i] = std::numeric_limits<int>::max();
            }
        }



        // 5. wybierz najlepsze rozwiazanie w danej iteracji
        operation_cost iteration_best_result = best_temporary_solution.cost;
        copy_ambulance_vector(potential_solutions[best_temporary_solution.solution_index], global_solution);


        // 6. jezeli jest to najlepsze rozwiazanie, zapisz je do wyniku algorytmu
        if(GUI::best_result > iteration_best_result){
            copy_ambulance_vector(global_solution, ambulance_list);
            //na potrzeby GUI
            GUI::best_result = iteration_best_result;
            GUI::best_result_iteration = GUI::iterations_number;
        }



        //7. aktualizuj liste tabu
        tabu_l.update_tabu(best_temporary_solution.swap_patient);

        // 7. zapisz dane na potrzeby GUI
        GUI::single_results[GUI::iterations_number-1] = (int)iteration_best_result;


        // 8. sprawdz czy przez ostatnie x iteracji byla poprawa (czy algorytm utknal?)
        if(GUI::best_result == iteration_best_result){
            iterations_without_improvement++;
        }
        if(iterations_without_improvement == 100){
            return global_solution;
        }

        }

        return global_solution;
    }
