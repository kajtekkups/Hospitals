#ifndef CITY_HPP
#define CITY_HPP

#include "Hospital.hpp"
#include "Ambulance.hpp"
#include "Patient.hpp"
#include <queue>

#define CITY_LENGTH 25
#define CITY_HEIGTH 50


struct Point {
    int x, y, distance;
};


//lista wszsystkich szpitali, trzeba ja kiedys stworzyc
extern std::vector<Hospital*> hospital_list;

//lista wszystkich pacjentow
extern std::vector<Patient*> patients_list;

//lista wszystkich karetek
extern std::vector<Ambulance*> ambulance_list;

//Map of the city: higher the number is, overall time is slower, 0 means no passage
extern std::vector<std::vector<int>> city;


int BFS(std::vector<std::vector<int>>& grid, const Point& start, const Point& end);

Hospital* get_best_hospital(Patient *pat);

#endif //CITY_HPP