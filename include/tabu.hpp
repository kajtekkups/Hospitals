#ifndef HOSPITALS_TABU_HPP
#define HOSPITALS_TABU_HPP

#include "GUI.hpp"
#include "hospital.hpp"
#include "Ambulance.hpp"
#include "Patient.hpp"
#include <map>
#include <utility>
#include <vector>
#include <cfloat>

#define CITY_LENGTH 25
#define CITY_HEIGTH 50
#define AMBULANCE_NUMBER 8  //how many ambulances are in town

struct Point {
    int x, y, distance;
};

//wektor, ktory ma swoja dlugosc, po przekroczeniu dlugosci zaczyna nadpisywac
//elementy zaczynajac od poczatku, wektor ma dlugosc dwa razy wieksza niz podana
//w tabu, przy jednej iteracji dodaje dwie pary do listy:
// {karetka1, index1_przeniesionego_pacjenta}, {karetka2, index2_przeniesionego_pacjenta}

class TabuList{
public:
    TabuList(int size): size_(size * 2){}

//dodaje dwie pary do listy tabu, jesli jest zapelniona dodaje od poczatku
    void update_tabu(std::map<Ambulance, int> const &pair1, std::map<Ambulance, int> const &pair2);

    int check_if_in_tabu(std::map<Ambulance, int> const &pair1, std::map<Ambulance, int> const &pair2);

private:
    int size_;
    std::vector<std::map<Ambulance, int>> tabu_l;
    int save_index = 0;
};

void copy_ambulance_vector(std::vector<Ambulance*> orginal, std::vector<Ambulance*>& copy);

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



