#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <vector>
#include <iostream>
#include <map>

class Hospital {
public:
    Hospital(const int x, const int y, std::vector<std::string> specialization, std::vector<int> value) : x_(x), y_(y) {
        for (int i = 0; i < static_cast<int>(specialization.size()); i++){
            specialization_.insert(std::make_pair(specialization[i], value[i]));
        }
    };
    [[nodiscard]] int getHospitalLocationX() const {return x_;}

    [[nodiscard]] int getHospitalLocationY() const {return y_;}

    std::map<std::string, int> getSpecializationList(){return specialization_;}

private:
    // hospital cordinates
    const int x_;
    const int y_;
    //list of specialization, hospital supports
    std::map<std::string, int> specialization_;
};

#endif //HOSPITAL_HPP