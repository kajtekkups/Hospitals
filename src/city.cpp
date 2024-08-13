#include "city.hpp"

specializations_vector specializations = {
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


std::vector<std::vector<int>> city {
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 2, 0, 0 ,0, 3, 0, 0, 0 ,0, 1, 0, 0, 0, 3 ,0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1 ,2, 0, 0, 0, 0},
        {1, 0, 1, 1, 0 ,0, 2, 0, 0, 0 ,0, 1, 0, 0, 0, 1 ,1, 0, 0, 0, 0 ,0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 2, 0, 0, 0 ,0, 1 ,1, 2, 2, 0, 0},
        {1, 0, 0, 1, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0 ,1, 2, 1, 1, 1 ,1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1 ,1, 1, 0, 0, 2 ,2, 1 ,0, 0, 1, 0, 0},
        {1, 0, 0, 2, 2 ,1, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0 ,2, 0, 0, 0, 0 ,0, 1, 0, 1, 1, 2, 2, 2, 2, 0, 0, 0, 1, 0, 2, 0, 0 ,0, 0, 0, 2, 2 ,0, 1 ,0, 0, 2, 1, 0},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 0 ,1, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 2, 0, 0 ,0, 0, 0, 2, 0 ,0, 1 ,0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 0, 0, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 2, 0, 0, 0},
        {1, 0, 0, 0, 0 ,0, 0, 1, 3, 0 ,0, 1, 0, 0, 0, 0 ,0, 1, 2, 2, 1 ,1, 1, 1, 2, 1, 2, 3, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 2, 2, 0, 0},
        {1, 3, 1, 0, 0 ,0, 0, 1, 0, 0 ,0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 3, 2, 3, 1 ,1, 1, 2, 2, 1 ,2, 1 ,0, 0, 2, 0, 0},
        {1, 0, 2, 0, 0 ,0, 0, 1, 1, 1 ,0, 1, 0, 0, 0, 0 ,0, 2, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 0, 1, 1, 1},
        {1, 0, 3, 0, 0 ,0, 0, 0, 0, 2 ,0, 1, 0, 0, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0 ,0, 0, 0, 0, 0 ,0, 1 ,0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 2, 0, 0 ,0, 2, 0, 0, 0 ,0, 1, 0, 2, 0, 0 ,0, 1, 0, 2, 0 ,0, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 ,0, 0, 2, 0, 0 ,0, 1 ,0, 0, 0, 2, 0},
        {1, 0, 1, 0, 0 ,0, 1, 0, 0, 0 ,0, 1, 0, 2, 0, 0 ,0, 2, 0, 2, 0 ,0, 1, 2, 1, 0, 0, 1, 0, 0, 0, 2, 0, 1, 0, 2, 0, 1 ,2, 1, 1, 0, 0 ,0, 1 ,0, 0, 0, 1, 0},
        {1, 0, 1, 2, 2 ,1, 1, 0, 0, 0 ,0, 1, 2, 1, 1, 1 ,2, 1, 2, 1, 1 ,1, 1, 0, 1, 0, 0, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2 ,0, 0, 2, 0, 0 ,0, 1 ,0, 0, 0, 1, 0},
        {1, 0, 0, 0, 1 ,0, 2, 0, 0, 0 ,0, 1, 0, 1, 0, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 1, 1, 1, 2, 0, 1, 0, 1, 0, 1, 0, 1, 0, 2 ,0, 0, 1, 1, 1 ,1, 1 ,1, 2, 2, 1, 0},
        {1, 0, 0, 0, 1 ,0, 2, 0, 0, 0 ,0, 1, 0, 2, 0, 0 ,0, 0, 0, 1, 0 ,0, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 ,0, 0, 1, 0, 0 ,0, 1 ,0, 0, 0, 2, 0},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1 ,0, 1, 0, 1, 0, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 1, 0, 2, 0, 0 ,1, 0, 0, 1, 0 ,0, 1 ,0, 2, 0, 0, 1},
        {1, 2, 1, 2, 0, 2, 0, 0, 0, 2 ,1, 1, 0, 2, 0, 0 ,0, 0, 0, 1, 0 ,0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 2, 0, 1, 0, 2, 0, 0 ,2, 1, 1, 2, 1 ,1, 1 ,0, 2, 0, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 2, 1, 1 ,2, 1, 1, 1, 2, 1 ,2, 1, 1, 2, 1 ,1, 1, 2, 2, 1, 0, 0, 0, 2, 1, 1, 2, 1, 1, 1, 2, 1 ,2, 0, 0, 0, 2 ,0, 1 ,1, 1, 2, 1, 2},
        {1, 0, 0, 1, 0 ,0, 2, 0, 0, 1 ,0, 1, 0, 0, 1, 0 ,0, 0, 0, 1, 0 ,0, 1, 0, 0, 1, 1, 2, 1, 2, 0, 0, 0, 1, 0, 1, 0, 0 ,1, 0, 0, 0, 2 ,0, 1 ,0, 2, 0, 0, 2},
        {1, 0, 0, 2, 0 ,0, 1, 0, 0, 2 ,0, 1, 0, 0, 2, 0 ,0, 0, 0, 2, 0 ,0, 1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 0 ,2, 0, 0, 0, 1 ,0, 1 ,0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1 ,1, 1},
};

std::vector<Hospital*> hospital_list;

std::vector<Patient*> patients_list;

std::vector<Ambulance*> ambulance_list;


//check if coordinations are correct
bool isValid(int x, int y, std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited) {
        return (x >= 0 && x < CITY_LENGTH && y >= 0 && y < CITY_HEIGTH && grid[x][y] && !visited[x][y]);
}


//Alghoritm for finding shortest path from poin A to point B
int BFS(std::vector<std::vector<int>>& grid, const Point& start, const Point& end) {
        std::vector<std::vector<bool>> visited(CITY_LENGTH, std::vector<bool>(CITY_HEIGTH, false));
        std::queue<Point> q;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        q.push(start);
        visited[start.x][start.y] = true;

        while (!q.empty()) {
                Point current = q.front();
                q.pop();

                if (current.x == end.x && current.y == end.y) {
                        return current.distance; // Zwraca ilość kroków do celu
                }

                for (int i = 0; i < 4; ++i) {
                        int newX = current.x + dx[i];
                        int newY = current.y + dy[i];

                        if (isValid(newX, newY, grid, visited)) {
                                visited[newX][newY] = true;
                                q.push({newX, newY, current.distance + grid[newX][newY]});
                        }
                }
        }
        return -1; // Brak ścieżki
}


//funckja szukajaca odpowiedniego szpitala dla pacjenta, zwraca ten szpital
//najlepszy pod wzgledem czasu
Hospital* get_best_hospital(Patient *pat){
        std::vector<Hospital*> spec_hospital;
        std::map<specialization_type, int> patient_injuries = pat -> getInjuriesList();

        for (auto hospital : hospital_list){
                int correct = 1;
                std::map<std::string, int> spec = hospital->getSpecializationList();
                for (const auto&[patient_spec, snd] : patient_injuries){
                        if (spec[patient_spec] < patient_injuries[patient_spec]){
                                correct = 0;
                                break;
                        }
                }
                if (correct == 1){
                        spec_hospital.push_back(hospital);
                }
        }

        const int min_time = 9999999;
        Hospital* besthospital = spec_hospital[0];

        for (auto hospital : spec_hospital){
                Point hosp_loc = Point{hospital->getHospitalLocationX(), hospital->getHospitalLocationY(), 0};
                Point patient_loc = Point{pat->getLocationX(), pat->getLocationY(), 0};
                int travel_time = BFS(city, patient_loc, hosp_loc);
                if (min_time > travel_time) {
                        besthospital = hospital;
                }
        }
        return besthospital;
}