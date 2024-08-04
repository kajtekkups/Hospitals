#include "tabu.hpp"
#include <queue>
#include <iostream>

#define NOT_IN_TABU 0
#define IN_TABU 1

#define FIRST_NEIGH 1
#define SECOND_NEIGH 2
#define THIRD_NEIGH 3
#define FOURTH_NEIGH 4


double cost = 0;
int iteration = 0;
int aspiration_on = 0;

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
    std::map<std::string, int> patient_injuries = pat -> get_injuries_list();

    for (auto hospital : hospital_list){
        int correct = 1;
        std::map<std::string, int> spec = hospital->get_spec_list();
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
        Point hosp_loc = Point{hospital->get_hosp_location_x(), hospital->get_hosp_location_y(), 0};
        Point patient_loc = Point{pat->get_location_x(), pat->get_location_y(), 0};
        int travel_time = BFS(city, patient_loc, hosp_loc);
        if (min_time > travel_time) {
            besthospital = hospital;
        }
    }
    return besthospital;
}

//Tabulist

void TabuList::update_tabu(std::map<Ambulance, int> const &pair1, std::map<Ambulance, int> const &pair2){
    if (size_ >= save_index){
        tabu_l.push_back(pair1);
        tabu_l.push_back(pair2);
        save_index = save_index + 2;
    }
    else{
        int index = save_index % size_;
        tabu_l[index] = pair1;
        tabu_l[index + 1] = pair2;
        save_index = save_index + 2;
    }
};

//dla parzystych indeksow sprawdza sasiada z prawej, dla nieparzystych z lewej
//

int TabuList::check_if_in_tabu(std::map<Ambulance, int> const &pair1, std::map<Ambulance, int> const &pair2){
    if (size_ >= save_index && save_index == 0){
        return NOT_IN_TABU;
    }
    else{
        int i = 0;
        for(auto &pair_in_tabu : tabu_l){
            if(pair_in_tabu == pair1){
                if (i % 2 == 1){
                    if (tabu_l[i - 1] == pair2) {
                        return IN_TABU;
                    }
                }
                if (i % 2 == 0){
                    if (tabu_l[i + 1] == pair2){
                        return IN_TABU;
                    }
                }
            }
            i++;
        }
        return NOT_IN_TABU;
    }
}

//zamienia ze soba miejsca w wektorze order na indeksach wektora
void swap(Ambulance &amb1, Ambulance &amb2, int patient1_idx, int patient2_idx) {

    std::vector<Patient*> order1 = amb1.get_order();
    std::vector<Patient*> order2 = amb2.get_order();

    Patient* patient_temp = order1[patient1_idx];
    order1[patient1_idx] = order2[patient2_idx];
    order2[patient2_idx] = patient_temp;

    amb1.new_order(order1);
    amb2.new_order(order2);
}


/* Sasiedztwa  (przez dostępnych pacjentów rozumie sie ze nie ma ich w liscie tabu)
1 - wymiana zawsze pierwszych z wolnych pacjentow miedzy losowymi karetkami
2 - wymiana losowych dostępnych pacjentów między losowymi karetkami
3 - przerzucenie pacjenta
4 - co x iteracje przerzuca pacjenta, tak to zamienia losowo

*/

//funkcja celu
double ObjectiveFunction(std::vector<Ambulance*> const &solution){
    double cost;
    for (auto ambulance : solution){
        Hospital* primaty_hospital = ambulance -> get_actual_hospital();
        int sum_time = 0;
        for (auto patient : ambulance->get_order()){
            if (patient == nullptr){
                break;
            }
//uwzglednic jeszcze czas jaki pacjent czeka
            int p_time = patient->get_time();
            Point pat_loc = {patient->get_location_x(), patient ->get_location_y(), 0};
            Point amb_loc = {ambulance->get_amb_location_x(), ambulance->get_amb_location_y(), 0};
            int amb_to_pat_time = BFS(city, amb_loc, pat_loc);
            Hospital* best_hospital = get_best_hospital(patient);
            Point hos_loc = {best_hospital->get_hosp_location_x(), best_hospital->get_hosp_location_y(), 0};
            int pat_to_hosp_time = BFS(city, pat_loc, hos_loc);
            int patient_priority = patient->get_priority();
            cost = cost + patient_priority * (p_time + amb_to_pat_time) + pat_to_hosp_time + sum_time;
            ambulance->change_hospital(best_hospital);
            sum_time = p_time + amb_to_pat_time + pat_to_hosp_time;
        }
        ambulance->change_hospital(primaty_hospital);
    }
    return cost;
}

//trzeba uzyc kilku sasiedztw naraz
std::map<Ambulance*, int> NeighbourSelect(TabuList Tabu, std::vector<Ambulance*> solutions, int choose_neigh){
    aspiration_on = 0;
    std::map<Ambulance*, int> neigh_to_swap;
    switch(choose_neigh) {
        case FIRST_NEIGH: {
            srand(time(nullptr));
            int swap_amp1_idx = 0;   // indeksy dla listy order_ poczatkowo rowne 0
            int swap_amp2_idx = 0;

            int ambulance_idx1 = rand() % AMBULANCE_NUMBER;  //wybor losowych karetek
            int ambulance_idx2 = rand() % AMBULANCE_NUMBER;

            while (ambulance_idx2 == ambulance_idx1){
                ambulance_idx2 = rand() % AMBULANCE_NUMBER;
            }

            std::vector<Patient*> order1 = solutions[ambulance_idx1]->get_order();
            std::vector<Patient*> order2 = solutions[ambulance_idx2]->get_order();

            int pat1_id;
            int pat2_id;
            try{
                pat1_id = order1[swap_amp1_idx] -> get_patient_id();
            } catch (const std::exception& e) {
                pat1_id = 0;
            }
            try{
                pat2_id = order2[swap_amp2_idx] -> get_patient_id();
            } catch (const std::exception& e) {
                pat2_id = 0;
            }

            std::map<Ambulance, int> pair1 = {{*solutions[ambulance_idx1], pat1_id}};
            std::map<Ambulance, int> pair2 = {{*solutions[ambulance_idx2], pat2_id}};

            while (Tabu.check_if_in_tabu(pair1, pair2)){
                if (kryterium_aspiracji != 0){
                    swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], swap_amp1_idx, swap_amp2_idx);
                    if (cost - ObjectiveFunction(solutions) >  kryterium_aspiracji){
                        apiration_usage_counter++;
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], swap_amp1_idx, swap_amp2_idx);
                        neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],swap_amp1_idx));
                        neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],swap_amp2_idx));
                        aspiration_on = 1;
                        break;
                    }
                    else{
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], swap_amp1_idx, swap_amp2_idx);
                    }}
                if (order1[swap_amp1_idx + 1] != nullptr){
                    swap_amp1_idx++;
                    pat1_id = order1[swap_amp1_idx] -> get_patient_id();
                    pair1 = {{*solutions[ambulance_idx1], pat1_id}};

                }
                else if (order2[swap_amp2_idx + 1] != nullptr){
                    swap_amp2_idx++;
                    pat2_id = order2[swap_amp2_idx] -> get_patient_id();
                    pair2 = {{*solutions[ambulance_idx2], pat2_id}};
                }
            }

            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],swap_amp1_idx));
            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],swap_amp2_idx));
            break;
        }

        case SECOND_NEIGH: {
            srand(time(nullptr));
            int ambulance_idx1;
            int ambulance_idx2;

            int numb_of_pat_idx1;  //liczba pacjentów dla wybranych losowo karetek
            int numb_of_pat_idx2;

            int pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
            int pat_idx2;

            std::map<Ambulance, int> pair1;
            std::map<Ambulance, int> pair2;

            while(true){
                ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //wybór losowych karetek
                ambulance_idx2 = rand() % AMBULANCE_NUMBER;

                while (ambulance_idx2 == ambulance_idx1) {
                    ambulance_idx2 = rand() % AMBULANCE_NUMBER;
                }

                numb_of_pat_idx1 = solutions[ambulance_idx1]->get_patient_count();  //liczba pacjentów dla wybranych losowo karetek
                numb_of_pat_idx2 = solutions[ambulance_idx2]->get_patient_count();

                pat_idx1 = rand() % numb_of_pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
                pat_idx2 = rand() % numb_of_pat_idx2;

                std::map<Ambulance, int> pair1 = {{*solutions[ambulance_idx1], pat_idx1}};
                std::map<Ambulance, int> pair2 = {{*solutions[ambulance_idx2], pat_idx2}};

                if (kryterium_aspiracji != 0){
                    swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                    if (Tabu.check_if_in_tabu(pair1, pair2) && (cost - ObjectiveFunction(solutions)) > kryterium_aspiracji){
                        apiration_usage_counter++;
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                        neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
                        neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
                        aspiration_on = 1;
                        break;
                    }
                    else{
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                    }}
                if(!Tabu.check_if_in_tabu(pair1, pair2)){
                    swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                    break;
                }
            }

            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
            break;
        }


        case THIRD_NEIGH:{
            srand(time(nullptr));
            int ambulance_idx1;
            int ambulance_idx2;

            int pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
            int pat_idx2;

            std::map<Ambulance, int> pair1;
            std::map<Ambulance, int> pair2;

            while(true){
                ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //wybór losowych karetek
                ambulance_idx2 = rand() % AMBULANCE_NUMBER;

                while (ambulance_idx2 == ambulance_idx1) {
                    ambulance_idx2 = rand() % AMBULANCE_NUMBER;
                }


                pat_idx1 = solutions[ambulance_idx1]->get_patient_count() - 1;
                pat_idx2 = solutions[ambulance_idx2]->get_patient_count();

                std::map<Ambulance, int> pair1 = {{*solutions[ambulance_idx1], pat_idx1}};
                std::map<Ambulance, int> pair2 = {{*solutions[ambulance_idx2], pat_idx2}};

                if (kryterium_aspiracji != 0){
                    swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                    if (Tabu.check_if_in_tabu(pair1, pair2) && (cost - ObjectiveFunction(solutions)) > kryterium_aspiracji){
                        apiration_usage_counter++;
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                        neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
                        neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
                        aspiration_on = 1;
                        break;
                    }
                    else{
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                    }}
                if(!Tabu.check_if_in_tabu(pair1, pair2)){

                    break;
                }
            }
            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
            break;
        }
        case FOURTH_NEIGH:{
            if (iteration % 20 == 0){
                srand(time(nullptr));
                int ambulance_idx1;
                int ambulance_idx2;

                int numb_of_pat_idx1;  //liczba pacjentów dla wybranych losowo karetek
                int numb_of_pat_idx2;

                int pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
                int pat_idx2;

                std::map<Ambulance, int> pair1;
                std::map<Ambulance, int> pair2;

                while(true){
                    ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //wybór losowych karetek
                    ambulance_idx2 = rand() % AMBULANCE_NUMBER;

                    while (ambulance_idx2 == ambulance_idx1) {
                        ambulance_idx2 = rand() % AMBULANCE_NUMBER;
                    }

                    numb_of_pat_idx1 = solutions[ambulance_idx1]->get_patient_count();  //liczba pacjentów dla wybranych losowo karetek
                    numb_of_pat_idx2 = solutions[ambulance_idx2]->get_patient_count();

                    pat_idx1 = rand() % numb_of_pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
                    pat_idx2 = rand() % numb_of_pat_idx2;

                    std::map<Ambulance, int> pair1 = {{*solutions[ambulance_idx1], pat_idx1}};
                    std::map<Ambulance, int> pair2 = {{*solutions[ambulance_idx2], pat_idx2}};

                    if (kryterium_aspiracji != 0){
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                        if (Tabu.check_if_in_tabu(pair1, pair2) && (cost - ObjectiveFunction(solutions)) > kryterium_aspiracji){
                            apiration_usage_counter++;
                            swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
                            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
                            aspiration_on = 1;
                            break;
                        }
                        else{
                            swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                        }}
                    if(!Tabu.check_if_in_tabu(pair1, pair2)){

                        break;
                    }
                }
                neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
                neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
            }
            else{
                srand(time(nullptr));
                int ambulance_idx1;
                int ambulance_idx2;

                int pat_idx1;  //wybór losowych pacjentów dla wybranych losowo karetek
                int pat_idx2;

                std::map<Ambulance, int> pair1;
                std::map<Ambulance, int> pair2;

                while(true){
                    ambulance_idx1 = rand() % AMBULANCE_NUMBER;   //wybór losowych karetek
                    ambulance_idx2 = rand() % AMBULANCE_NUMBER;

                    while (ambulance_idx2 == ambulance_idx1) {
                        ambulance_idx2 = rand() % AMBULANCE_NUMBER;
                    }


                    pat_idx1 = solutions[ambulance_idx1]->get_patient_count() - 1;
                    pat_idx2 = solutions[ambulance_idx2]->get_patient_count();

                    std::map<Ambulance, int> pair1 = {{*solutions[ambulance_idx1], pat_idx1}};
                    std::map<Ambulance, int> pair2 = {{*solutions[ambulance_idx2], pat_idx2}};

                    if (kryterium_aspiracji != 0){
                        swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                        if (Tabu.check_if_in_tabu(pair1, pair2) && (cost - ObjectiveFunction(solutions)) > kryterium_aspiracji){
                            apiration_usage_counter++;
                            swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
                            neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
                            aspiration_on = 1;
                            break;
                        }
                        else{
                            swap(*solutions[ambulance_idx1], *solutions[ambulance_idx2], pat_idx1, pat_idx2);
                        }}
                    if(!Tabu.check_if_in_tabu(pair1, pair2)){
                        break;
                    }
                }
                neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx1],pat_idx1));
                neigh_to_swap.insert(std::make_pair(solutions[ambulance_idx2],pat_idx2));
            }
            break;
        }
        default:
            break;
    }

    return neigh_to_swap;
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

void copy_ambulance_vector(std::vector<Ambulance*> orginal, std::vector<Ambulance*>& copy){
    // wyczysc wektor do ktorego kopiujemy
    for (auto & del : copy){
        delete del;
    }
    copy.clear();

    // skoopiuj wartosci
    for (Ambulance *ambulance: orginal) {
        Ambulance *clonedAmbulance = new Ambulance(*ambulance);
        copy.push_back(clonedAmbulance);
    }
}

//algorytm tabu
std::vector<Ambulance*> TabuSearch(){
    //tworzenie tabu listy
    TabuList tabu_l = TabuList(dlugosc_listy_tabu);
    //Inicjalizowanie pierwszego rozwiązania
    create_first_solution();
    //tu trzeba bedzie sprawdzic czy kopiuje czy bedzie sie zmienial razem z ambulacne list
    std::vector<Ambulance*> global_solution;
    copy_ambulance_vector(ambulance_list, global_solution);
    // tworzymy tyle rozwiazan, ile mamy opcji wyboru sasiedztwa
    std::vector<Ambulance*> solution1, solution2, solution3, solution4;

    //liczba iteracji bez poprawy wyniku
    int max_iteration = 0;

    for (int i = 0; i < max_liczba_iteracji; i++){
        act_liczba_iteracji++;

        int aspiration_on1 = 0;
        int aspiration_on2 = 0;
        int aspiration_on3 = 0;
        int aspiration_on4 = 0;
        int final_aspiration;
        std::vector<int> pat_idx_to_swap1;
        std::vector<Ambulance*> amb_to_swap1;
        std::vector<int> pat_idx_to_swap2;
        std::vector<Ambulance*> amb_to_swap2;
        std::vector<int> pat_idx_to_swap3;
        std::vector<Ambulance*> amb_to_swap3;
        std::vector<int> pat_idx_to_swap4;
        std::vector<Ambulance*> amb_to_swap4;

        // 1. stworz kopie ostatniego najlepszego rozwiazania
        copy_ambulance_vector(global_solution, solution1);
        copy_ambulance_vector(global_solution, solution2);
        copy_ambulance_vector(global_solution, solution3);
        copy_ambulance_vector(global_solution, solution4);

        // 2. stworz nowe rozwiazania
        std::map<Ambulance*, int> swap_1 = NeighbourSelect(tabu_l, solution1, FIRST_NEIGH);
        aspiration_on1 = aspiration_on;
        std::map<Ambulance*, int> swap_2 = NeighbourSelect(tabu_l, solution2, SECOND_NEIGH);
        aspiration_on2 = aspiration_on;
        std::map<Ambulance*, int> swap_3 = NeighbourSelect(tabu_l, solution3, THIRD_NEIGH);
        aspiration_on3 = aspiration_on;
        std::map<Ambulance*, int> swap_4 = NeighbourSelect(tabu_l, solution4, FOURTH_NEIGH);
        aspiration_on4 = aspiration_on;

        for(auto & it : swap_1){
            amb_to_swap1.push_back(it.first);
            pat_idx_to_swap1.push_back(it.second);
        }

        for(auto & it : swap_2){
            amb_to_swap2.push_back(it.first);
            pat_idx_to_swap2.push_back(it.second);
        }

        for(auto & it : swap_3){
            amb_to_swap3.push_back(it.first);
            pat_idx_to_swap3.push_back(it.second);
        }

        for(auto & it : swap_4){
            amb_to_swap4.push_back(it.first);
            pat_idx_to_swap4.push_back(it.second);
        }

        swap(*amb_to_swap1[0], *amb_to_swap1[1], pat_idx_to_swap1[0], pat_idx_to_swap1[1]);
        swap(*amb_to_swap2[0], *amb_to_swap2[1], pat_idx_to_swap2[0], pat_idx_to_swap2[1]);
        swap(*amb_to_swap3[0], *amb_to_swap3[1], pat_idx_to_swap3[0], pat_idx_to_swap3[1]);
        swap(*amb_to_swap4[0], *amb_to_swap4[1], pat_idx_to_swap4[0], pat_idx_to_swap4[1]);

        // 3. oblicz wartosci funkcji celu
        double cost_temp_solution1 = ObjectiveFunction(solution1);
        double cost_temp_solution2 = ObjectiveFunction(solution2);
        double cost_temp_solution3 = ObjectiveFunction(solution3);
        double cost_temp_solution4 = ObjectiveFunction(solution4);

        // 4. wyeliminuj rozwiazania sasiedztw nie branych pod uwage
        //    (moglo by to byc bardziej optymalne, ale jest to tymczasowe rozwiazanie oszczedzajace czas)
        if(!dobor_sasiedztwa[0]){
            cost_temp_solution1 = DBL_MAX;
        }
        if(!dobor_sasiedztwa[1]){
            cost_temp_solution2 = DBL_MAX;
        }
        if(!dobor_sasiedztwa[2]){
            cost_temp_solution3 = DBL_MAX;
        }
        if(!dobor_sasiedztwa[3]){
            cost_temp_solution4 = DBL_MAX;
        }
        
        // 5. wybierz najlepsze rozwiazanie w danej iteracji
        double najlniejsza_wartosc_funkcji = cost_temp_solution1;
        copy_ambulance_vector(solution1, global_solution);
        final_aspiration = aspiration_on1;

        if (cost_temp_solution2 < najlniejsza_wartosc_funkcji) {
            najlniejsza_wartosc_funkcji = cost_temp_solution2;
            copy_ambulance_vector(solution2, global_solution);
            final_aspiration = aspiration_on2;
        }

        if (cost_temp_solution3 < najlniejsza_wartosc_funkcji) {
            najlniejsza_wartosc_funkcji = cost_temp_solution3;
            copy_ambulance_vector(solution3, global_solution);
            final_aspiration = aspiration_on3;
        }

        if (cost_temp_solution4 < najlniejsza_wartosc_funkcji) {
            najlniejsza_wartosc_funkcji = cost_temp_solution4;
            copy_ambulance_vector(solution4, global_solution);
            final_aspiration = aspiration_on4;
        }

        if (final_aspiration == 1){
            liczba_uzyc_kryterium_aspiracji++;
        }

        // 6. jezeli jest to najlepsze rozwiazanie, zapisz je do wyniku algorytmu
        if(najlepszy_wynik > najlniejsza_wartosc_funkcji){
            copy_ambulance_vector(global_solution, ambulance_list);
            //na potrzeby GUI
            najlepszy_wynik = najlniejsza_wartosc_funkcji;
            iteracja_z_najlepszym_wynikiem = act_liczba_iteracji;
        }

        // 7. zapisz dane na potrzeby GUI
        wartosci_funkcji[act_liczba_iteracji-1] = (int)najlniejsza_wartosc_funkcji;


        // 8. sprawdz czy przez ostatnie x iteracji byla poprawa (czy algorytm utknal?)
        if(najlepszy_wynik == najlniejsza_wartosc_funkcji){
            max_iteration++;
        }
        if(max_iteration == 1000){
            return global_solution;
        }

    }

    return global_solution;
}