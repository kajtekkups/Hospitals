#include "Configuration_data.hpp"
#include "Hospital.hpp"
#include "city.hpp"
#include <fstream>

namespace Config_Data {

int ambulance_number;

specializations_vector specializations= {
    "Ortopedia",
    "Okulistyka",
    "Neurologia",
    "Chirurgia",
    "Kardiologia",
    "Pediatria",
    "Endokrynologia",
    "Geriatria",
    "Ginekologia",
    "Urologia",
    "Psychiatria",
    "Oparzenia",
    "Gastroenterologia"};

void loadConfigData() {
    //load JSON file
    std::ifstream configuration_file(inital_setting_path);
    if (!configuration_file.is_open()) {
        std::cerr << "Could not open file " << inital_setting_path << std::endl;
        return;
    }

    nlohmann::json configuration_data;
    configuration_file >> configuration_data;

    try {

        //Load Hospitals
        for (auto& hospital_instance : configuration_data["Hospitals"]) {
            Hospital* hosp = new Hospital(hospital_instance["x"],  hospital_instance["y"] , specializations, hospital_instance["specialization_grade"].get<std::vector<int>>());
            hospital_list.push_back(hosp);
        }

        //Load Patients
        for (auto& patient_instance : configuration_data["Patients"]) {
            Patient* pat = new Patient(patient_instance["x"],  patient_instance["y"], patient_instance["time"], patient_instance["priority"], specializations, patient_instance["specialization_grade"].get<std::vector<int>>());
            patients_list.push_back(pat);
        }

        const std::vector<int> ambulance_location = configuration_data["Ambulance"]["location_as_hospital"].get<std::vector<int>>();
        ambulance_number = static_cast<int>(ambulance_location.size());
        for(int i=0; i < (ambulance_number); i++) {
            Ambulance *new_ambulance = new Ambulance(hospital_list[ambulance_location[i]]);
            ambulance_list.push_back(new_ambulance);
        }


    }
    catch (const std::exception& e) {
        std::cout << "incorrect input data" << std::endl;
    }

    //close file
    configuration_file.close();
}



} //Config_Data