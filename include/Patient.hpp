#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <vector>
#include <iostream>
#include <map>

typedef int patient_id;
typedef std::string specialization_type;
typedef std::vector<specialization_type> specializations_vector;
class Patient{
public:
    patient_id static pat_id;

    Patient(const int x, const int y, const int time, const float priority, std::vector<std::string> specialization, std::vector<int> value) :id_(pat_id), x_(x), y_(y), time_(time), priority_(priority){
        for (int i = 0; i < static_cast<int>(specialization.size()); i++){
            patient_injuries_.insert(std::make_pair(specialization[i], value[i]));
        }
        pat_id++;
    }

    [[nodiscard]] float getPriority() const {return priority_;}

    [[nodiscard]] int getTime() const {return time_;}

    [[nodiscard]] int getLocationX() const {return x_;}

    [[nodiscard]] int getLocationY() const {return y_;}

    std::map<std::string, int> getInjuriesList(){return patient_injuries_;}

    [[nodiscard]] patient_id getPatientId() const {return id_;}

private:
    patient_id id_;
    int x_;
    int y_;
    int time_;
    float priority_;
    std::map<std::string, int> patient_injuries_;
};



#endif //PATIENT_HPP