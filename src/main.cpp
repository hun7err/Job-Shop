#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
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
			//cout << "[+] Everything ok so far, loading " << name << endl;
			Scheduler* scheduler = new Scheduler();
			switch(fmt) {
				case 0:
					scheduler->loadFromOrlib(name);
					/*cout << "\t[ ]  jobCount: " << scheduler->getJobCount() << ", machineCount: " << scheduler->getMachineCount() << endl;
					for(int i = 0; i < scheduler->getJobCount(); i++) {
						cout << "\t[" << i << "]: ";
						for(int j = 0; j < scheduler->getJob(i)->getTaskCount(); j++) {
							cout << scheduler->getJob(i)->getTask(j)->getMachineId() << "," << scheduler->getJob(i)->getTask(j)->getDuration() << " ";
						}
						cout << endl;
					}*/
				break;
				case 1:
					scheduler->loadFromTaillard(name);
				break;
			}
			/*cout << "\t[ ]  jobCount: " << scheduler->getJobCount() << ", machineCount: " << scheduler->getMachineCount() << endl;
			for(int i = 0; i < scheduler->getJobCount(); i++) {
				cout << "\t[" << i << "]: ";
				for(int j = 0; j < scheduler->getJob(i)->getTaskCount(); j++) {
					cout << scheduler->getJob(i)->getTask(j)->getMachineId() << "," << scheduler->getJob(i)->getTask(j)->getDuration() << " ";
				}
				cout << endl;
			}*/
			short int jobCount = (argc == 3) ? scheduler->getJobCount() : atoi(argv[3]);
			timespec t1, t2;
			//cout << "[ ] Solving..." << endl;
			clock_gettime(CLOCK_REALTIME, &t1);
			scheduler->solveWithHeuristic(string(name + "_out"), jobCount);
			clock_gettime(CLOCK_REALTIME, &t2);
			double total_time = (double)((t2.tv_sec - t1.tv_sec) + 1.e-9 * (t2.tv_nsec - t1.tv_nsec));
			//cout << "[+] Solved! Total time: ";
			cout << total_time << endl;
			/*for(int i = 0; i < jobCount; i++) {
				cout << "\t[" << i << "]: ";
				for(int j = 0; j < scheduler->getJob(i)->getTaskCount(); j++) {
					cout << scheduler->getJob(i)->getTask(j)->getMachineId() << "," << scheduler->getJob(i)->getTask(j)->getDuration() << " -> (s:" << scheduler->getJob(i)->getTask(j)->getStartTime() <<",e:" << scheduler->getJob(i)->getTask(j)->getStartTime() + scheduler->getJob(i)->getTask(j)->getDuration() << ") ";
				}
				cout << endl;
			}*/

			delete scheduler;
			//cout << "[+] Everything done, cleanup too. Quitting..." << endl;
		}
	}
	return 0;
}

void printProgramInfo(char* argv[]) {
	cout << "Program rozwiazujacy JSP (Job-Shop Problem)" << endl << "Copyright (c) Dominik Galewski, Krzysztof Marciniak" << endl << endl <<  "Sposob uzycia: " << argv[0] << " f nazwa [ilosc]" << endl << endl << "f - format pliku; 0 - orlib, 1 - format Taillarda" << endl << "nazwa - nazwa pliku z ktorego maja byc wczytane instacje" << endl << "liczba - opcjonalny parametr decydujacy ile instancji ma zostac wczytane z pliku; brak oznacza wczytanie wszystkich" << endl;
}
