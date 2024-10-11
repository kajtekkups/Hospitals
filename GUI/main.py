import json
import tkinter as tk
from tkinter import ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
from matplotlib.figure import Figure

#TODO: tylkko na potrzeby prezentacji
import subprocess


class GUI(tk.Tk):
    def __init__(self):
        self.data_to_save = {"max_iteration": None,
                             "aspiration_criterion": None,
                             "tabu_list_length": None,
                             "neighborhood_selection_method": None} #dane zapisywane w .json

        self.input_data = {"iterations_number": None,
                           "aspiration_criterion_use_number": None,
                           "execution_time": None,
                           "best_result_iteration": None,
                           "optymalne_rozwiazanie": None,
                           "single_results": None,
                           "best_result": None}

        self.sciezka_do_exe = r'../cmake-build-debug/Hospitals'
        self.sciezka_do_wynikow = r'wyniki.json'
        self.initial_settings_file = r'./initial_setting.json'

        self.wartosci_funkcji =[]
        self.liczba_iteracji = None
        self.liczba_uzyc_kryt_aspiracji = None
        self.czas_wykonania = None
        self.iteracja_najlepszy_wynik = None
        self.najlepszy_wynik = None
        self.optymalne_rozwiazanie = None
        self.przycisk_sasiedztwo1 = None
        self.przycisk_sasiedztwo2 = None
        self.przycisk_sasiedztwo3 = None
        self.przycisk_sasiedztwo4 = None

        self.algorithm_output = None
        self.ambulance_list = []

        self.tree_hospital = None
        self.tree_parient = None
        self.tree_ambulance = None
        self.tree_ambulance_allocation = None

        #frontend
        super().__init__()
        self.title("Tabu Search Algorithm") # Ustawienie tytułu okna
        self.geometry("1000x800") # Ustawienie rozmiarów okna

        # Utwórz zakładki
        self.notebook = ttk.Notebook(self, padding=10)
        self.utworz_zakladke_zapisu_danych()
        self.zakladka_dla_wykresu()
        self.create_results_objects()
        self.input_data_tab()
        self.ambulance_allocation_tab()

        # Wyświetl zakładki w pełnej szerokości i wysokości okna
        self.notebook.grid(row=0, column=0, sticky="nsew")
        # Ustaw wagi dla kolumn i wierszy
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)


    def utworz_zakladke_zapisu_danych(self):
        self.karta1 = tk.Frame(self.notebook)
        self.dodaj_pola_karty1()
        self.notebook.add(self.karta1, text="Algorithm input data")

    def zakladka_dla_wykresu(self):
        self.karta2 = tk.Frame(self.notebook)
        self.notebook.add(self.karta2, text="Chart")

    def input_data_tab(self):
        self.karta3 = tk.Frame(self.notebook)
        self.notebook.add(self.karta3, text="Input data")
        self.create_hospital_table()
        self.create_patient_table()
        self.create_ambulance_table()

    def ambulance_allocation_tab(self):
        self.karta4 = tk.Frame(self.notebook)
        self.notebook.add(self.karta4, text="Ambulance allocation")

    def create_hospital_table(self):
        self.tree_hospital = ttk.Treeview(self.karta3, columns=("Name", "Position_X", "Position_Y", "Specialization_grade"), show="headings")
        self.tree_hospital.heading("Name", text="Hospital name")
        self.tree_hospital.heading("Position_X", text="Position X")
        self.tree_hospital.heading("Position_Y", text="Position Y")
        self.tree_hospital.heading("Specialization_grade", text="Specialization grade")

        # set colum width
        self.tree_hospital.column("Name", width=100)
        self.tree_hospital.column("Position_X", width=10)
        self.tree_hospital.column("Position_Y", width=10)
        self.tree_hospital.column("Specialization_grade", width=200)
        self.tree_hospital.pack(fill=tk.BOTH)

        # Wczytywanie danych z pliku JSON
        with (open(self.initial_settings_file, 'r') as file):
            data = json.load(file)
            for hospital in data['Hospitals']:
                position_x = data['Hospitals'][hospital]['x']
                position_y = data['Hospitals'][hospital]['y']
                specialization = data['Hospitals'][hospital]['specialization_grade']
                self.tree_hospital.insert("", "end", values=(hospital, position_x, position_y, specialization))

    def create_patient_table(self):
        self.tree_parient = ttk.Treeview(self.karta3, columns=("Name", "Position_X", "Position_Y", "time", "priority", "Specialization_grade"),
                                 show="headings")

        self.tree_parient.heading("Name", text="Patient name")
        self.tree_parient.heading("Position_X", text="Position X")
        self.tree_parient.heading("Position_Y", text="Position Y")
        self.tree_parient.heading("time", text="Time")
        self.tree_parient.heading("priority", text="priority")
        self.tree_parient.heading("Specialization_grade", text="Specialization grade")

        # set colum width
        self.tree_parient.column("Name", width=100)
        self.tree_parient.column("Position_X", width=10)
        self.tree_parient.column("Position_Y", width=10)
        self.tree_parient.column("time", width=10)
        self.tree_parient.column("priority", width=10)
        self.tree_parient.column("Specialization_grade", width=200)
        self.tree_parient.pack(fill=tk.BOTH)

        # Wczytywanie danych z pliku JSON
        with (open(self.initial_settings_file, 'r') as file):
            data = json.load(file)
            for patient in data['Patients']:
                position_x = data['Patients'][patient]['x']
                position_y = data['Patients'][patient]['y']
                time = data['Patients'][patient]['time']
                priority = data['Patients'][patient]['priority']
                specialization = data['Patients'][patient]['specialization_grade']
                self.tree_parient.insert("", "end", values=(patient, position_x, position_y, time, priority, specialization))


    def create_ambulance_table(self):
        self.tree_ambulance = ttk.Treeview(self.karta3, columns=("Name", "Hospital"),
                                 show="headings")

        self.tree_ambulance.heading("Name", text="Patient name")
        self.tree_ambulance.heading("Hospital", text="Hospital")

        # set colum width
        self.tree_ambulance.column("Name", width=100)
        self.tree_ambulance.column("Hospital", width=100)
        self.tree_ambulance.pack(fill=tk.BOTH)

        # Wczytywanie danych z pliku JSON
        with (open(self.initial_settings_file, 'r') as file):
            data = json.load(file)
            ambulance_number = 1
            for ambulance_hospital in data['Ambulance']['location_as_hospital']:
                self.ambulance_list = self.ambulance_list + [ambulance_number]

                name_ambulace = "Ambulans_" + str(ambulance_number)
                hospital = "Hospital_" + str(ambulance_hospital)
                self.tree_ambulance.insert("", "end", values=(name_ambulace, hospital))
                ambulance_number = ambulance_number + 1

    def dodaj_pola_karty1(self):
        # max_liczba_iteracji
        self.label_max_liczba_iteracji = tk.Label(self.karta1, text="Maximum number of iterations")
        self.label_max_liczba_iteracji.grid(row=0, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_max_liczba_iteracji = tk.Entry(self.karta1)
        self.entry_max_liczba_iteracji.grid(row=0, column=0, padx=10, pady=10)

        # dlugosc listy tabu
        self.label_dlugosc_listy_tabu = tk.Label(self.karta1, text="tabu list lenght")
        self.label_dlugosc_listy_tabu.grid(row=1, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_dlugosc_listy_tabu = tk.Entry(self.karta1)
        self.entry_dlugosc_listy_tabu.grid(row=1, column=0, padx=10, pady=10)

        # kryterium aspiracji
        self.label_kryterium_aspiracji = tk.Label(self.karta1, text="Aspiration criteria")
        self.label_kryterium_aspiracji.grid(row=2, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_kryterium_aspiracji = tk.Entry(self.karta1)
        self.entry_kryterium_aspiracji.grid(row=2, column=0, padx=10, pady=10)

        # wybor sasiedztwa
        self.przycisk_sasiedztwo1 = tk.BooleanVar()
        self.przycisk_sasiedztwo1.set(False)
        self.przycisk_sasiedztwo1_okno = tk.Checkbutton(self.karta1, text="Neighborhood 1", variable=self.przycisk_sasiedztwo1)
        self.przycisk_sasiedztwo1_okno.grid(row=4, column=0, pady=10)

        self.przycisk_sasiedztwo2 = tk.BooleanVar()
        self.przycisk_sasiedztwo2.set(False)
        self.przycisk_sasiedztwo2_okno = tk.Checkbutton(self.karta1, text="Neighborhood 2", variable=self.przycisk_sasiedztwo2)
        self.przycisk_sasiedztwo2_okno.grid(row=5, column=0, pady=10)

        self.przycisk_sasiedztwo3 = tk.BooleanVar()
        self.przycisk_sasiedztwo3.set(False)
        self.przycisk_sasiedztwo3_okno = tk.Checkbutton(self.karta1, text="Neighborhood 3", variable=self.przycisk_sasiedztwo3)
        self.przycisk_sasiedztwo3_okno.grid(row=6, column=0, pady=10)

        self.przycisk_sasiedztwo4 = tk.BooleanVar()
        self.przycisk_sasiedztwo4.set(False)
        self.przycisk_sasiedztwo4_okno = tk.Checkbutton(self.karta1, text="Neighborhood 4", variable=self.przycisk_sasiedztwo4)
        self.przycisk_sasiedztwo4_okno.grid(row=7, column=0,  pady=10)

        # przycisk zapisu danych
        self.przycisk_karta1 = tk.Button(self.karta1, text="Run", command=self.uruchom_algorytm)
        self.przycisk_karta1.grid(row=50, column=0, padx=10, pady=10)


    def uruchom_algorytm(self):
        # 1. zapisz dane
        try:
            self.data_to_save["max_iteration"] = int(self.entry_max_liczba_iteracji.get())
            self.data_to_save["aspiration_criterion"] = int(self.entry_kryterium_aspiracji.get())
            self.data_to_save["tabu_list_length"] = int(self.entry_dlugosc_listy_tabu.get())
            print(self.wybierz_sasiedztwo())
            self.data_to_save["neighborhood_selection_method"] = self.wybierz_sasiedztwo()
            self.save_data()
        except ValueError:
            print("To nie jest poprawna liczba całkowita.")

        print(self.data_to_save)

        # 2. uruchom algorytm
        self.run_exe()

        # 3. wczytaj wyniki
        self.wczytaj_wyniki()

        # 4. wyswietl wyniki
        self.wyswietl_wyniki()




    def wybierz_sasiedztwo(self):

        wektor_sasiedztwa = [0, 0, 0, 0]

        if self.przycisk_sasiedztwo1.get():
            wektor_sasiedztwa[0] = 1
        if self.przycisk_sasiedztwo2.get():
            wektor_sasiedztwa[1] = 1
        if self.przycisk_sasiedztwo3.get():
            wektor_sasiedztwa[2] = 1
        if self.przycisk_sasiedztwo4.get():
            wektor_sasiedztwa[3] = 1

        return wektor_sasiedztwa


    def save_data(self):
        # Zapis do pliku JSON
        with open("dane.json", "w") as file:
            json.dump(self.data_to_save, file)


    def create_results_objects(self):
        # Dodaj pole z iloscia iteracji
        self.ramka = tk.Frame(self.karta1, bd=1, relief=tk.GROOVE)
        self.ramka.grid(row=0, column=151, padx=10, pady=10)
        #napis
        self.napis_iteracje = tk.Label(self.ramka, text="number of iterations")
        self.napis_iteracje.grid(padx=10)
        #wartosc
        self.etykieta_liczba_iteracji = tk.IntVar()
        self.etykieta_liczba_iteracji.set(self.liczba_iteracji)
        self.wartosc_etykiety = tk.Label(self.ramka, textvariable=self.etykieta_liczba_iteracji)
        self.wartosc_etykiety.grid(row=0, column=151, padx=10)

        # liczba uzyc kryt aspiracji
        self.ramka_aspiracje = tk.Frame(self.karta1, bd=1, relief=tk.GROOVE)
        self.ramka_aspiracje.grid(row=1, column=151, padx=10, pady=10)
        #napis
        self.napis_aspiracje = tk.Label(self.ramka_aspiracje, text="Aspiration criteria usage number")
        self.napis_aspiracje.grid(padx=10)
        #wartosc
        self.etykieta_liczba_aspiracji = tk.IntVar()
        self.etykieta_liczba_aspiracji.set(self.liczba_uzyc_kryt_aspiracji)
        self.wartosc_etykiety_aspiracji = tk.Label(self.ramka_aspiracje, textvariable=self.etykieta_liczba_aspiracji)
        self.wartosc_etykiety_aspiracji.grid(row=0, column=2, padx=10)

        # czas_wykonania
        self.ramka_czas_wykonania = tk.Frame(self.karta1, bd=1, relief=tk.GROOVE)
        self.ramka_czas_wykonania.grid(row=2, column=151, padx=10, pady=10)
        #napis
        self.napis_czas_wykonania = tk.Label(self.ramka_czas_wykonania, text="time [s]")
        self.napis_czas_wykonania.grid(padx=10)
        #wartosc
        self.etykieta_czas_wykonania = tk.IntVar()
        self.etykieta_czas_wykonania.set(self.czas_wykonania)
        self.wartosc_etykiety_czasu = tk.Label(self.ramka_czas_wykonania, textvariable=self.etykieta_czas_wykonania)
        self.wartosc_etykiety_czasu.grid(row=0, column=2, padx=10)

        # iteracja z najlepszym wynikiem
        self.ramka_najlepszy_wynik_iteracja = tk.Frame(self.karta1, bd=1, relief=tk.GROOVE)
        self.ramka_najlepszy_wynik_iteracja.grid(row=3, column=151, padx=10, pady=10)
        #napis
        self.napis_najlepszy_wynik_iteracja = tk.Label(self.ramka_najlepszy_wynik_iteracja, text="Iteration with best result")
        self.napis_najlepszy_wynik_iteracja.grid(padx=10)
        #wartosc
        self.etykieta_najlepszy_wynik_iteracja = tk.IntVar()
        self.etykieta_najlepszy_wynik_iteracja.set(self.iteracja_najlepszy_wynik)
        self.wartosc_najlepszy_wynik_iteracja = tk.Label(self.ramka_najlepszy_wynik_iteracja, textvariable=self.etykieta_najlepszy_wynik_iteracja)
        self.wartosc_najlepszy_wynik_iteracja.grid(row=0, column=2, padx=10)

        # najlepszy_wynik
        self.ramka_najlepszy_wynik = tk.Frame(self.karta1, bd=1, relief=tk.GROOVE)
        self.ramka_najlepszy_wynik.grid(row=4, column=151, padx=10, pady=10)
        #napis
        self.napis_najlepszy_wynik = tk.Label(self.ramka_najlepszy_wynik, text="best result")
        self.napis_najlepszy_wynik.grid(padx=10)
        #wartosc
        self.etykieta_najlepszy_wynik = tk.IntVar()
        self.etykieta_najlepszy_wynik.set(self.najlepszy_wynik)
        self.wartosc_najlepszy_wynik = tk.Label(self.ramka_najlepszy_wynik, textvariable=self.etykieta_najlepszy_wynik)
        self.wartosc_najlepszy_wynik.grid(row=0, column=2, padx=10)




    def run_exe(self):

        #TODO:tylko zeby zaprezentowac dzialanie
        proces = subprocess.Popen(self.sciezka_do_exe, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        # Pobierz wyjście i błędy
        self.algorithm_output, bledy = proces.communicate()
        # Wyświetl wyniki
        print("Wyjście:\n")
        print(self.algorithm_output)
        print("\nBłędy:")
        print(bledy)

    def process_algorithm_output(self):
        self.algorithm_output = self.algorithm_output.replace(" ", "")
        self.algorithm_output = self.algorithm_output.replace("Ambulans", "")
        self.algorithm_output = self.algorithm_output.replace("Pacjent", "")
        lines = self.algorithm_output.split("\n")

        ambulance_allocation = {}
        for ambulance in self.ambulance_list:
            ambulance_allocation[str(ambulance)] = []

        for element in lines:
            if ':' in element:
                ambulans_number, patient_number = element.split(":")
                patient_number = int(patient_number) + 1
                ambulance_allocation[str(ambulans_number)].append(patient_number)


        #update GUI
        self.tree_ambulance_allocation = ttk.Treeview(self.karta4, columns=("Ambulance", "patients_list"),
                                 show="headings")

        self.tree_ambulance_allocation.heading("Ambulance", text="Ambulance")
        self.tree_ambulance_allocation.heading("patients_list", text="Patients number")

        # set colum width
        self.tree_ambulance_allocation.column("Ambulance", width=100)
        self.tree_ambulance_allocation.column("patients_list", width=100)
        self.tree_ambulance_allocation.pack(fill=tk.BOTH)

        # Wczytywanie danych z pliku JSON
        for ambulace_number, patient_number in ambulance_allocation.items():
            self.tree_ambulance_allocation.insert("", "end", values=(ambulace_number, patient_number))


    def wczytaj_wyniki(self):
        try:
            # Wczytaj dane z pliku JSON
            with open(self.sciezka_do_wynikow, 'r') as plik_json:
                dane = json.load(plik_json)

            self.liczba_iteracji = dane["iterations_number"]
            self.liczba_uzyc_kryt_aspiracji = dane["aspiration_criterion_use_number"]
            self.czas_wykonania = dane["execution_time"]
            self.iteracja_najlepszy_wynik = dane["best_result_iteration"]
            self.najlepszy_wynik = dane["best_result"]
            self.wartosci_funkcji = dane["single_results"]


        except Exception as e:
            # Wyświetl wartość w etykiecie
            self.etykieta_wartosci.config(text="Algorytm nie zostal uruchomiony (nie udalo sie odczytac wyniku)")


    def rysuj_wykres(self):
        # Dane do wykresu (przykładowe dane)
        dane_y = self.wartosci_funkcji[0:self.liczba_iteracji]
        dane_x = [i for i in range(self.liczba_iteracji)]

        # Tworzenie figury Matplotlib
        fig = Figure(figsize=(10, 8), dpi=100)
        wykres = fig.add_subplot(1, 1, 1)
        wykres.plot(dane_x, dane_y, label='Wartosci funkcji celu',  linewidth=0.5)

        wykres.set_title('Objective function chart')
        wykres.set_xlabel('Solutions')
        wykres.set_ylabel('Objective function value')

        # Konwersja figury na Tkinter PhotoImage
        canvas = FigureCanvasTkAgg(fig, master=self.karta2)
        canvas_widget = canvas.get_tk_widget()

        # Umiejscowienie widgetu Canvas w oknie Tkinter
        canvas_widget.grid(row=0, column=200, padx=10, pady=10)


    def wyswietl_wyniki(self):
        self.etykieta_liczba_iteracji.set(self.liczba_iteracji)
        self.etykieta_liczba_aspiracji.set(self.liczba_uzyc_kryt_aspiracji)
        self.etykieta_czas_wykonania.set(self.czas_wykonania)
        self.etykieta_najlepszy_wynik_iteracja.set(self.iteracja_najlepszy_wynik)
        self.etykieta_najlepszy_wynik.set(self.najlepszy_wynik)
        self.rysuj_wykres()
        self.process_algorithm_output()
        print(self.wartosci_funkcji[1])


if __name__ == "__main__":
    app = GUI()
    app.mainloop()