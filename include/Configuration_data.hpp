#ifndef CONFIGURATION_DATA_HPP
#define CONFIGURATION_DATA_HPP


#include "Patient.hpp"
#include <nlohmann/json.hpp>

namespace Config_Data {

extern int ambulance_number;  //how many ambulances are in town

const std::string inital_setting_path = "../GUI/initial_setting.json";

extern specializations_vector specializations;


void loadConfigData();


} //Config_Data

#endif //CONFIGURATION_DATA_HPP