#include "Ambulance.hpp"

int Ambulance::amb_id = 0;

void Ambulance::add_patient(Patient* patient) {
    order_[patient_count] = patient;
    patient_count++;
}

Patient* Ambulance::deletePatient(int patient_que_index) {
    Patient* return_patient = order_[patient_que_index];

    for (int i = patient_que_index; i < MAX_PATIENTS_NUMBER - 1; i++) {
        order_[i] = order_[i+1];
        if (order_[i] == nullptr){
            break;
        }
    }
    patient_count--;

    return return_patient;
}


patient_id Ambulance::getPatientID(int patient_index) const{
    if (patient_index == -1){
        return -1;
    }
    return order_[patient_index]->getPatientId();
}