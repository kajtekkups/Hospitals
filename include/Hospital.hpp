#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <vector>
#include <iostream>
#include <map>

class Hospital {
public:
    Hospital(int x, int y, std::vector<std::string> specialization, std::vector<int> value) : x_(x), y_(y) {
        for (int i = 0; i < specialization.size(); i++){
            specialization_.insert(std::make_pair(specialization[i], value[i]));
        }
    };
    int getHospitalLocationX(){return x_;}

    int getHospitalLocationY(){return y_;}

    std::map<std::string, int> getSpecializationList(){return specialization_;}

private:
    // hospital cordinates
    int x_;
    int y_;
    //list of specialization, hospital supports
    std::map<std::string, int> specialization_;
};

#endif //HOSPITAL_HPP