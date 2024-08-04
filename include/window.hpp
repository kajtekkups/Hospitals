#ifndef HOSPITALS_WINDOW_HPP
#define HOSPITALS_WINDOW_HPP

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

// sciezka do bazy danych (wejscie z gui)
const std::string data_file_path = "../GUI/dane.json";
// sciezka do bazy danych (wyniki dla gui)
const std::string results_file_path = "../GUI/wyniki.json";


//TODO: zmienne sa tu deklarowane tymczasowo, docelowo trzeba to umiescic pewnie gdzies w structures.hpp
//dane wejsciowe z GUI
extern int max_liczba_iteracji;
extern int kryterium_aspiracji;
extern int dlugosc_listy_tabu;
extern std::vector<int> dobor_sasiedztwa;

//dane wyjsciowe do GUI
extern int act_liczba_iteracji;
extern int liczba_uzyc_kryterium_aspiracji;
extern int czas_wykonania;
extern int iteracja_z_najlepszym_wynikiem;
extern int wartosci_funkcji[10000];
extern double najlepszy_wynik;

int wczytaj_dane();

int zapisz_dane();

#endif //HOSPITALS_WINDOW_HPP
