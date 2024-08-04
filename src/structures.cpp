#include "structures.hpp"

//AMBULACE

void Ambulance::add_patient(Patient* patient) {
    order_[patient_count] = patient;
    patient_count++;
}
