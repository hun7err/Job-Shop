#include <iostream>
#include <cstdlib>
#include "../include/scheduler.h"
using namespace std;

void printProgramInfo(char* argv[]);

int main(int argc, char* argv[]) {
	if(argc < 3 || argc > 4) {
		printProgramInfo(argv);
		return -1;
	} else {
		string name(argv[2]);
		int fmt = atoi(argv[1]);
		if(fmt != 0 && fmt != 1) {
			printProgramInfo(argv);
			return -1;	
		} else {
			cout << "[+] Everything ok so far, loading " << name << endl;
			Scheduler* scheduler = new Scheduler();
			switch(fmt) {
				case 0:
					scheduler->loadFromOrlib(name);
				break;
				case 1:
					scheduler->loadFromTaillard(name);
				break;
			}
			// here will be the solution... someday.
			delete scheduler;
			cout << "[+] Everything done, cleanup too. Quitting..." << endl;
		}
	}
	return 0;
}

void printProgramInfo(char* argv[]) {
	cout << "Program rozwiazujacy JSP (Job-Shop Problem)" << endl << "Copyright (c) Dominik Galewski, Krzysztof Marciniak" << endl << endl <<  "Sposob uzycia: " << argv[0] << " f nazwa [ilosc]" << endl << endl << "f - format pliku; 0 - orlib, 1 - format Taillarda" << endl << "nazwa - nazwa pliku z ktorego maja byc wczytane instacje" << endl << "liczba - opcjonalny parametr decydujacy ile instancji ma zostac wczytane z pliku; brak oznacza wczytanie wszystkich" << endl;
}
