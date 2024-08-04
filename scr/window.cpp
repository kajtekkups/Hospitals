#include "window.hpp"

int wczytaj_dane(){

    // Strumień do odczytu pliku JSON
    std::ifstream plik(data_file_path);

    // Sprawdź, czy plik został otwarty poprawnie
    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku " << data_file_path << std::endl;
        return 1;
    }

    // Parsuj dane z pliku JSON
    nlohmann::json dane;
    plik >> dane;

    try {
        // Wyciągnij dane i zapisz do zmiennych
        max_liczba_iteracji = dane["max_liczba_iteracji"];
        kryterium_aspiracji = dane["kryterium_aspiracji"];
        dlugosc_listy_tabu = dane["dlugosc_listy_tabu"];
        nlohmann::json tablica_sasiedztwa = dane["dobor_sasiedztwa"];
        dobor_sasiedztwa.push_back(tablica_sasiedztwa[0]);
        dobor_sasiedztwa.push_back(tablica_sasiedztwa[1]);
        dobor_sasiedztwa.push_back(tablica_sasiedztwa[2]);
        dobor_sasiedztwa.push_back(tablica_sasiedztwa[3]);
    }
    catch (const std::exception& e) {
        std::cout << "nie poprawnie zapisane dane wejsciowe, algorytm nie byl w stanie ich odczytac" << std::endl;
    }

    // Zamknij plik
    plik.close();

    return 0;
}


int zapisz_dane(){

    // Tworzenie obiektu JSON
    nlohmann::json dane_do_zapisu;


    // Dodawanie danych do obiektu JSON
    dane_do_zapisu["liczba_iteracji"] = act_liczba_iteracji;
    dane_do_zapisu["liczba_uzyc_kryt_aspiracji"] = liczba_uzyc_kryterium_aspiracji;
    dane_do_zapisu["czas_wykonania"] = czas_wykonania;
    dane_do_zapisu["iteracja_najlepszy_wynik"] =  iteracja_z_najlepszym_wynikiem;
    dane_do_zapisu["najlepszy_wynik"] =  (int)najlepszy_wynik;
    //    dane_do_zapisu["optymalne_rozwiazanie"] =  [["karetka1", [1, 2]], ["karetka2", [1]]];
    dane_do_zapisu["wartosci_funkcji"] = wartosci_funkcji;

    // Tworzenie strumienia do zapisu do pliku
    std::ofstream plik(results_file_path);

    if (plik.is_open()) {
        // Zapisywanie danych do pliku
        plik << dane_do_zapisu.dump(4); // dump(4) oznacza wcięcie każdego poziomu o cztery spacje
        plik.close();
        std::cout << "Dane zapisane do pliku." << std::endl;
    } else {
        std::cerr << "Błąd otwarcia pliku do zapisu." << std::endl;
    }

    return 0;
}