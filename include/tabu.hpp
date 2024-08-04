#ifndef HOSPITALS_TABU_HPP
#define HOSPITALS_TABU_HPP

#include "structures.hpp"
#include <map>
#include <utility>
#include <vector>
#include <cfloat>

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

//zmienne uzywane w tabu
extern int max_liczba_iteracji;
extern int kryterium_aspiracji;
extern int dlugosc_listy_tabu;
extern std::vector<int> dobor_sasiedztwa;

extern int act_liczba_iteracji;
extern int liczba_uzyc_kryterium_aspiracji;
extern int iteracja_z_najlepszym_wynikiem;
extern double najlepszy_wynik;
extern int wartosci_funkcji[10000];

//lista wszsystkich szpitali, trzeba ja kiedys stworzyc
extern std::vector<Hospital*> hospital_list;

//lista wszystkich pacjentow
extern std::vector<Patient*> patients_list;

//lista wszystkich karetek
extern std::vector<Ambulance*> ambulance_list;


#endif //HOSPITALS_TABU_HPP



