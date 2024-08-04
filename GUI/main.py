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
        self.data_to_save = {"max_liczba_iteracji": None,
                             "kryterium_aspiracji": None,
                             "dlugosc_listy_tabu": None,
                             "dobor_sasiedztwa": None} #dane zapisywane w .json

        self.input_data = {"liczba_iteracji": None,
                           "liczba_uzyc_kryteriow_aspiracji": None,
                           "czas_obliczen": None,
                           "iteracja_znalazla_wynik": None,
                           "optymalne_rozwiazanie": None,
                           "kolejne_wartosci_funkcji": None,
                           "najlepszy_wynik": None}

        self.sciezka_do_exe = r'../cmake-build-debug-mingw/Hospitals.exe'
        self.sciezka_do_wynikow = r'wyniki.json'

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

        #frontend
        super().__init__()
        self.title("Algorytm TS") # Ustawienie tytułu okna
        self.geometry("1000x800") # Ustawienie rozmiarów okna

        # Utwórz zakładki
        self.notebook = ttk.Notebook(self, padding=10)
        self.utworz_zakladke_zapisu_danych()
        self.zakladka_dla_wykresu()
        self.utworz_zakladke_wyniku()

        # Wyświetl zakładki w pełnej szerokości i wysokości okna
        self.notebook.grid(row=0, column=0, sticky="nsew")
        # Ustaw wagi dla kolumn i wierszy
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)


    def utworz_zakladke_zapisu_danych(self):
        self.karta1 = tk.Frame(self.notebook)
        self.dodaj_pola_karty1()
        self.notebook.add(self.karta1, text="Dane do algorytmu")


    def zakladka_dla_wykresu(self):
        self.karta2 = tk.Frame(self.notebook)
        self.notebook.add(self.karta2, text="Wykres")


    def dodaj_pola_karty1(self):
        # max_liczba_iteracji
        self.label_max_liczba_iteracji = tk.Label(self.karta1, text="maksymalna liczba iteracji")
        self.label_max_liczba_iteracji.grid(row=0, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_max_liczba_iteracji = tk.Entry(self.karta1)
        self.entry_max_liczba_iteracji.grid(row=0, column=0, padx=10, pady=10)

        # dlugosc listy tabu
        self.label_dlugosc_listy_tabu = tk.Label(self.karta1, text="dlugosc listy tabu")
        self.label_dlugosc_listy_tabu.grid(row=1, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_dlugosc_listy_tabu = tk.Entry(self.karta1)
        self.entry_dlugosc_listy_tabu.grid(row=1, column=0, padx=10, pady=10)

        # kryterium aspiracji
        self.label_kryterium_aspiracji = tk.Label(self.karta1, text="kryterium aspiracji")
        self.label_kryterium_aspiracji.grid(row=2, column=1)  # Przesunięcie napisu
        # pole do wpisania wartosci
        self.entry_kryterium_aspiracji = tk.Entry(self.karta1)
        self.entry_kryterium_aspiracji.grid(row=2, column=0, padx=10, pady=10)

        # wybor sasiedztwa
        self.przycisk_sasiedztwo1 = tk.BooleanVar()
        self.przycisk_sasiedztwo1.set(False)
        self.przycisk_sasiedztwo1_okno = tk.Checkbutton(self.karta1, text="Sasiedztwo 1", variable=self.przycisk_sasiedztwo1)
        self.przycisk_sasiedztwo1_okno.grid(row=4, column=0, pady=10)

        self.przycisk_sasiedztwo2 = tk.BooleanVar()
        self.przycisk_sasiedztwo2.set(False)
        self.przycisk_sasiedztwo2_okno = tk.Checkbutton(self.karta1, text="Sasiedztwo 2", variable=self.przycisk_sasiedztwo2)
        self.przycisk_sasiedztwo2_okno.grid(row=5, column=0, pady=10)

        self.przycisk_sasiedztwo3 = tk.BooleanVar()
        self.przycisk_sasiedztwo3.set(False)
        self.przycisk_sasiedztwo3_okno = tk.Checkbutton(self.karta1, text="Sasiedztwo 3", variable=self.przycisk_sasiedztwo3)
        self.przycisk_sasiedztwo3_okno.grid(row=6, column=0, pady=10)

        self.przycisk_sasiedztwo4 = tk.BooleanVar()
        self.przycisk_sasiedztwo4.set(False)
        self.przycisk_sasiedztwo4_okno = tk.Checkbutton(self.karta1, text="Sasiedztwo 4", variable=self.przycisk_sasiedztwo4)
        self.przycisk_sasiedztwo4_okno.grid(row=7, column=0,  pady=10)

        # przycisk zapisu danych
        self.przycisk_karta1 = tk.Button(self.karta1, text="Zapisz", command=self.uruchom_algorytm)
        self.przycisk_karta1.grid(row=50, column=0, padx=10, pady=10)


    def uruchom_algorytm(self):
        # 1. zapisz dane
        try:
            self.data_to_save["max_liczba_iteracji"] = int(self.entry_max_liczba_iteracji.get())
            self.data_to_save["kryterium_aspiracji"] = int(self.entry_kryterium_aspiracji.get())
            self.data_to_save["dlugosc_listy_tabu"] = int(self.entry_dlugosc_listy_tabu.get())
            print(self.wybierz_sasiedztwo())
            self.data_to_save["dobor_sasiedztwa"] = self.wybierz_sasiedztwo()
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


    def utworz_zakladke_wyniku(self):
        # Dodaj pole z iloscia iteracji
        self.ramka = tk.Frame(self.karta1, bd=1, relief=tk.GROOVE)
        self.ramka.grid(row=0, column=151, padx=10, pady=10)
        #napis
        self.napis_iteracje = tk.Label(self.ramka, text="liczba iteracji")
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
        self.napis_aspiracje = tk.Label(self.ramka_aspiracje, text="liczba uzyc kryt aspiracji")
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
        self.napis_czas_wykonania = tk.Label(self.ramka_czas_wykonania, text="czas wykonania [s]")
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
        self.napis_najlepszy_wynik_iteracja = tk.Label(self.ramka_najlepszy_wynik_iteracja, text="iteracja z najlepszym wynikiem")
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
        self.napis_najlepszy_wynik = tk.Label(self.ramka_najlepszy_wynik, text="najlepszy wynik")
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
        wyjscie, bledy = proces.communicate()
        # Wyświetl wyniki
        print("Wyjście:\n")
        print(wyjscie)
        print("\nBłędy:")
        print(bledy)


    def wczytaj_wyniki(self):
        try:
            # Wczytaj dane z pliku JSON
            with open(self.sciezka_do_wynikow, 'r') as plik_json:
                dane = json.load(plik_json)

            self.wartosci_funkcji = dane["wartosci_funkcji"]
            self.liczba_iteracji = dane["liczba_iteracji"]
            self.liczba_uzyc_kryt_aspiracji = dane["liczba_uzyc_kryt_aspiracji"]
            self.czas_wykonania = dane["czas_wykonania"]
            self.iteracja_najlepszy_wynik = dane["iteracja_najlepszy_wynik"]
            self.najlepszy_wynik = dane["najlepszy_wynik"]
            # self.optymalne_rozwiazanie = dane["optymalne_rozwiazanie"]


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

        wykres.set_title('Wartosci funkcji celu')
        wykres.set_xlabel('kolejne rozwiazania')
        wykres.set_ylabel('Wartość funkcji celu')

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
        print(self.wartosci_funkcji[1])


if __name__ == "__main__":
    app = GUI()
    app.mainloop()