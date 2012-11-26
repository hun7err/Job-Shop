#include "../include/scheduler.h"
#include <sstream>
#include <fstream>
#include <iostream> // temporary, debugging purposes only [!]

Scheduler::Scheduler(){
	this->machineCount = 0;
	this->jobCount = 0;
	this->schedulingDuration = 0;
}

Scheduler::Scheduler(int mCount, int jCount) {
	this->machineCount = mCount;
	this->jobCount = jCount;
	this->schedulingDuration = 0;
}

Scheduler::~Scheduler() {
	this->Jobs.clear();
}

/*
	short format description:
	
	job_count machine_count
	task1_machine_number task1_duration task2_machine_number task2_duration[...]
	[...]
	task1_machine_number task1_duration [...]

	there are job_count lines like that built of machine_count*2 numbers because each task needs a number of a machine it belongs to and the task duration
*/
bool Scheduler::loadFromOrlib(std::string filename) {	// optimise - I have no idea if it can be done  but still it isn't the best way to do it, probably
	std::ifstream in;
	in.open(filename.c_str(), std::ifstream::in);
	if(in.is_open()) {
		int	jid	= 0,
			temp	= 0,
			i	= 0;
		std::string line;
		std::getline(in, line);
		std::stringstream ss;
		ss << line;
		ss >> temp;
		this->setJobCount(temp);
		ss >> temp;
		this->setMachineCount(temp);

		ss.clear();
		while(std::getline(in, line)) {
			i = temp = 0;
			Task* t;
			Job* j = new Job(jid);
			ss << line;
			while (ss >> temp) {
				if (i % 2 == 0) {
					t = new Task();
					t->setJobId(jid);
					t->setMachineId(temp);
				} else {
					t->setDuration(temp);
					j->addTask(t);
				}
				i++;
			}
			ss.clear();
			j->setRemainingTime();
			this->addJob(j);
			jid++;
		}
		in.close();
		return true;
	} else return false;
}

bool Scheduler::loadFromTaillard(std::string filename) {
	std::ifstream in;
	in.open(filename.c_str());
	if(in.is_open()) {
		std::string line;
		int temp = 0, tid = 0, jid = 0;
		std::getline(in, line);
		std::stringstream ss;
		ss << line;
		ss >> temp;
		this->setJobCount(temp);
		ss >> temp;
		this->setMachineCount(temp);
		while(ss >> temp);
		ss.clear();
		bool times = true;

		while(std::getline(in, line)) {
			Task* t;
			Job* j = new Job(jid);
			if(line.find("Times") != std::string::npos) {
				times = true;
				continue;
			}
			if(line.find("Machines") != std::string::npos) {
				times = false;
				jid = 0;
				continue;
			}
			ss << line;
			while(ss >> temp) {
				if(times) {
					//std::cout << "line: " << line << std::endl;
					//std::cout << "duration: " << temp << std::endl;
					t = new Task();
					t->setJobId(jid);
					t->setDuration(temp);
					j->addTask(t);
				} else {
					this->getJob(jid)->getTask(tid)->setMachineId(temp);
				}
				tid++;
			}
			j->setRemainingTime();
			this->addJob(j);
			ss.clear();
			jid++;
			tid = 0;
		}
		// everything else
		return true;
	} else return false;
}

bool Scheduler::solveWithHeuristic(std::string fileName, short int jCount) {
	std::ofstream out;
	out.open(fileName.c_str());
	if(out.is_open()) {
		//std::vector< std::vector<short int> > result;
		const short int mCount = machineCount;
		std::list<Task*> MachineUsage [mCount];
		/*for(int i = 0; i < jCount; i++) { // for every job
			for (int j = 0; j <  getJob(i)->getTaskCount(); j++) { // and every task of them
				// processing
			}
		}*/
		/*while(true) {
			//short int jid = 0, tid = 0;

			// sprawdz, czy pierwsze taski innych kontenerow maja takie samo id maszyny - jesli nie, przydziel maszyne. Jesli tak, rozwiaz konflikt poprzez wyszukanie wsrod nich tasku ktory nalezy do jobu o najkrotszym czasie pozostalym do zakonczenia [ getRemainingTime() ]. Informacje dodatkowe do pomyslu sa ponizej (156. linia ATM).

			if(!(Jobs[0]->empty()))
				Task* t = Jobs[0]->getTask(0);
			for(int i = 0; i < jCount; i++) {
				for(int j = 0; j < jCount, j != i; j++) {
				}
				//if(Jobs[i]->getRemainingTime() < Jobs[0]->getRemainingTime())
				//Task* cur_t = Jobs[i]->getTask(0);
				
			}
		}*/

		/*
			nowy pomysl:

			zadania trzymac normalnie w wektorach, ale w kazdym przebiegu petli zdejmowac je z przodu, analizowac i - jesli pozostaja do wykonania - wrzucac je na przod kontenera zwiekszajac startTime o czas trwania poprzedniego zadania. Zadanie zdjete z przodu wektora wrzucac na koniec wektora rozwiazan po odpowiednim zaktualizowaniu czasu startu
		*/

		// rozwiazanie i zapis do pliku
	} else return false;
}

void Scheduler::setMachineCount(short int mCount) {
	this->machineCount = mCount;
}

void Scheduler::setJobCount(short int jCount) {
	this->jobCount = jCount;
}

void Scheduler::addJob(Job* job) {
	this->Jobs.push_back(job);
}

short int Scheduler::getJobCount() {
	return this->jobCount;
}

short int Scheduler::getMachineCount() {
	return this->machineCount;
}

short int Scheduler::getSchedulingDuration() {
	return this->schedulingDuration;
}

Job* Scheduler::getJob(short int jobId) {
	return this->Jobs[jobId];
}
