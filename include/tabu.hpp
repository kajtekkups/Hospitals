#ifndef HOSPITALS_TABU_HPP
#define HOSPITALS_TABU_HPP


#include "hospital.hpp"
#include "Ambulance.hpp"
#include "Patient.hpp"
#include "GUI.hpp"
#include <map>
#include <vector>

#define CITY_LENGTH 25
#define CITY_HEIGTH 50
#define AMBULANCE_NUMBER 8  //how many ambulances are in town

typedef int swap_patient_index;  //identifies patient of particular ambulance, that is going to be swapt
typedef int operation_cost;
typedef int best_result_solution;

struct Point {
    int x, y, distance;
};

struct NeighbourSelectResult {
    std::map<Ambulance, swap_patient_index> swap_patient;
    operation_cost cost;
    best_result_solution solution_index;
};


/***************************************
 * TabuList is a list, that holds
 ************************************/
class TabuList{
public:
    explicit TabuList(int size): tabu_list_size_(size * 2), tabu_l(size*2){
        // for (int i = 0; i < (size*2); i++) {
        //     Ambulance amb(-1);
        //     tabu_l.emplace_back(amb, -1, -1);
        // }
    }

//dodaje dwie pary do listy tabu, jesli jest zapelniona dodaje od poczatku
    void update_tabu(const std::map<Ambulance, swap_patient_index> &pairs);

    int check_if_in_tabu(std::pair<Ambulance, swap_patient_index> const &pair1, std::pair<Ambulance, swap_patient_index> const &pair2);

private:
    int tabu_list_size_;
    std::vector<std::tuple<ambulance_id, patient_id, swap_patient_index>> tabu_l;
    int save_index = 0;
};


void copy_ambulance_vector(std::vector<Ambulance*> orginal, std::vector<Ambulance*>& to_delete);

std::vector<Ambulance*> TabuSearch();

void test_zmiennych_z_gui();


//lista wszsystkich szpitali, trzeba ja kiedys stworzyc
extern std::vector<Hospital*> hospital_list;

//lista wszystkich pacjentow
extern std::vector<Patient*> patients_list;

//lista wszystkich karetek
extern std::vector<Ambulance*> ambulance_list;

//Map of the city: higher the number is, overall time is slower, 0 means no passage
extern std::vector<std::vector<int>> city;


#endif //HOSPITALS_TABU_HPP



