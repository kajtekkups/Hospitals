#include "structures.hpp"

//AMBULACE

int Ambulance::amb_id = 0;

void Ambulance::add_patient(Patient* patient) {
    order_[patient_count] = patient;
    patient_count++;
}

//PATIENTS
int Patient::pat_id = 0;
