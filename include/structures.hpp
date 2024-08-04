#ifndef HOSPITALS_STRUCTURES_HPP
#define HOSPITALS_STRUCTURES_HPP
#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <utility>

//do okreslenia jeszcze co do liczby length jako ROWS
#define CITY_LENGTH 25
#define CITY_HEIGTH 50

#define AMBULANCE_NUMBER 8
#define PATIENTS_NUMBER 20

//definicja struktur
struct Point {
    int x, y, distance;
};

class Hospital {
public:
    Hospital(int x, int y, std::vector<std::string> specialization, std::vector<int> value) : x_(x), y_(y) {
        for (int i = 0; i < specialization.size(); i++){
            specialization_.insert(std::make_pair(specialization[i], value[i]));
        }
    };
    int get_hosp_location_x(){return x_;}

    int get_hosp_location_y(){return y_;}

    std::map<std::string, int> get_spec_list(){return specialization_;}

private:
    int x_;
    int y_;
    std::map<std::string, int> specialization_;
};


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

//zwraca priorytet
    int get_priority(){return priority_;}

//zwraca czas obsługi
    int get_time(){return time_;}

    int get_location_x(){return x_;}

    int get_location_y(){return y_;}

    std::map<std::string, int> get_injuries_list(){return patient_injuries_;}

    int get_patient_id(){return id_;}

private:
    int id_;
    int x_;
    int y_;
    int time_;
    int priority_;
    std::map<std::string, int> patient_injuries_;
};

class Ambulance{
public:
    //unikalne id identyfikujace karetke
    static int amb_id;

    Ambulance(Hospital *actual_hospital): actual_hospital_(actual_hospital), id(amb_id){
        for (int i = 0; i < PATIENTS_NUMBER; i++){
            order_.push_back(nullptr);
        }
        amb_id++;
    }

    Ambulance(const Ambulance& other) : id(other.id), actual_hospital_(other.actual_hospital_), patient_count(other.patient_count){
        for(Patient* patient : other.order_){
            order_.push_back(patient);
        }
    }

    //dodanie operatorow porownania
    bool operator==(const Ambulance& other)const{
        return id == other.id;
    }
    bool operator<(const Ambulance& other)const{
        return id < other.id;
    }
    bool operator>(const Ambulance& other)const{
        return id > other.id;
    }

//dodaje pacjenta do karetki
    void add_patient(Patient* patient);

    std::vector<Patient*> get_order(){return order_;};

//zwraca ilosc pacjentów
    int get_patient_count(){return patient_count;};

    void new_order(std::vector<Patient*> ord){order_ = std::move(ord);}

    int get_amb_location_x(){return actual_hospital_ -> get_hosp_location_x();}

    int get_amb_location_y(){return actual_hospital_ -> get_hosp_location_y();}

    Hospital* get_actual_hospital(){return actual_hospital_;}

    void change_hospital(Hospital* new_hospital) {
        actual_hospital_ = new_hospital;
    }


private:
    int id;
    int patient_count = 0;
    //przedstawia liczbe zakolejkowanych pacjentow
    std::vector<Patient*> order_;
    Hospital* actual_hospital_;


};

#endif //HOSPITALS_STRUCTURES_HPP
