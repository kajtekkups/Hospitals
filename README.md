# Hospitals

Software tool for manageing city ambulance infrostructure, based on TABU search alghoritm.

## General info
Project is a prototype of a managing system for ambulance infrostructure in a small city.
Tabu search is a metaheuristic search method (general procedure design to find sufficiently good solution,
used for problems where optimal solution is hard to find), in this project I implemented it with c++. 
I also added python GUI with basic options.

## Input data
The data of Hospitals, Patients and ambulances can be found in the GUI/initial_setting.json file. Currently, it is not
possible to edit this data via GUI, but it can be viewed in "input data" tab. 
![Screenshot from 2024-10-11 20-36-18](https://github.com/user-attachments/assets/660fe264-40fa-4e1b-b034-af708f294fe4)

Plan of the city is implemented as a matrix in src/city.cpp -> city.

## Running algorithm
In order to run algorithm, it is necessary to build c++ code with gcc compiler (and keep binary file inside cmake-buil-debug 
catalogue)
GUI can be open by running GUI/main.py script

In "Algorithm input data" tab Tabu Search algorithm parameters can be modified.
After running Algorithm, you can also view the results there
![Screenshot from 2024-10-11 20-35-59](https://github.com/user-attachments/assets/250d523c-53e7-4217-a3c5-57ef65372f9f)

## Results
Results can be viewed in "Ambulance input data" tab and "Ambulance allocation" tab (as a list of patients for each ambulance)
![Screenshot from 2024-10-11 20-38-53](https://github.com/user-attachments/assets/be90225d-8372-4032-99b8-a6e5f3439721)

You can also view the chart of reasult in each iteration
![Screenshot from 2024-10-11 20-36-11](https://github.com/user-attachments/assets/35ebbfb3-e2e3-42e0-85d9-230e55b093b2)
