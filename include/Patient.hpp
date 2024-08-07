#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <vector>
#include <iostream>
#include <map>

class Patient{
public:
    int static pat_id;

    //injuries jako lista liczb, jesli dana specjalizacja jest potrzebna to wpisujemy jej wymagany poziom,
    //jesli nie to 0,lista o stalym rozmiarze, x, y to wspolrzedne macierzy miasta
    //time to czas obsługi wypadku i na sorze
    Patient(int x, int y, int time, int priority, std::vector<std::string> specialization, std::vector<int> value) : x_(x), y_(y), time_(time), priority_(priority), id_(pat_id){
        for (int i = 0; i < specialization.size(); i++){
            patient_injuries_.insert(std::make_pair(specialization[i], value[i]));
        }
        pat_id++;
    }

    //patient handling time
    int getPriority(){return priority_;}

    //return
    int getTime(){return time_;}

    int getLocationX(){return x_;}

    int getLocationY(){return y_;}

    std::map<std::string, int> getInjuriesList(){return patient_injuries_;}

    int getPatientId(){return id_;}

private:
    int id_;
    int x_;
    int y_;
    int time_;
    int priority_;
    std::map<std::string, int> patient_injuries_;
};



#endif //PATIENT_HPP