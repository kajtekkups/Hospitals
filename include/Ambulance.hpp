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

    explicit Ambulance(Hospital *actual_hospital): id(amb_id), actual_hospital_(actual_hospital), patient_count(0){
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

    void add_patient(Patient* patient);

    [[nodiscard]] Patient* deletePatient(int que_index);

    [[nodiscard]] ambulance_id getID() const {return id; };

    std::vector<Patient*> getOrder(){return order_;};

    [[nodiscard]] int getPatientCount() const {return patient_count;};

    [[nodiscard]] patient_id getPatientID(int patient_index) const;

    void newOrder(std::vector<Patient*> ord){order_ = std::move(ord);}

    [[nodiscard]] int getAmbulanceLocationX() const {return actual_hospital_ -> getHospitalLocationX();}

    [[nodiscard]] int getAmbulanceLocationY() const {return actual_hospital_ -> getHospitalLocationY();}

    [[nodiscard]] Hospital* getActualHospital() const {return actual_hospital_;}

    void changeHospital(Hospital* new_hospital) {
        actual_hospital_ = new_hospital;
    }


private:
    int id;
    Hospital* actual_hospital_;
    int patient_count; //Patients in a que
    std::vector<Patient*> order_;

};


#endif //AMBULANCE_HPP