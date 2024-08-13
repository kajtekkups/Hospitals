#ifndef AMBULANCE_HPP
#define AMBULANCE_HPP

#include "Hospital.hpp"
#include "Patient.hpp"

#define MAX_PATIENTS_NUMBER 20

typedef int ambulance_id;

class Ambulance{
public:
    //unikalne id identyfikujace karetke
    static int amb_id;

    Ambulance(Hospital *actual_hospital): id(amb_id), actual_hospital_(actual_hospital){
        for (int i = 0; i < MAX_PATIENTS_NUMBER; i++){
            order_.push_back(nullptr);
        }
        amb_id++;
    }

    Ambulance(const Ambulance& other): id(other.id), actual_hospital_(other.actual_hospital_), patient_count(other.patient_count){
        for(Patient* patient: other.order_){
            order_.push_back(patient);
        }
    }

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

    ambulance_id getID() const {return id; };
    std::vector<Patient*> get_order(){return order_;};

    //zwraca ilosc pacjentów
    int getPatientCount(){return patient_count;};

    patient_id getPatientID(int patient_index) const {return order_[patient_index]->getPatientId();}

    void newOrder(std::vector<Patient*> ord){order_ = std::move(ord);}

    int getAmbulanceLocationX(){return actual_hospital_ -> getHospitalLocationX();}

    int getAmbulanceLocationY(){return actual_hospital_ -> getHospitalLocationY();}

    Hospital* getActualHospital(){return actual_hospital_;}

    void changeHospital(Hospital* new_hospital) {
        actual_hospital_ = new_hospital;
    }


private:
    int id;
    int patient_count = 0; //Patients in a que
    std::vector<Patient*> order_;
    Hospital* actual_hospital_;


};


#endif //AMBULANCE_HPP