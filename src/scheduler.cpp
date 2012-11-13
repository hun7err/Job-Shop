#include "../include/scheduler.h"
#include <sstream>
#include <fstream>
//#include <iostream> // temporary, debugging purposes only [!]

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
void Scheduler::loadFromOrlib(std::string filename) {	// optimise - I have no idea if it can be done  but still it isn't the best way to do it, probably
	std::ifstream in;
	in.open(filename.c_str(), std::ifstream::in);
	if(in.is_open()) {
		std::string line;
		std::getline(in, line);
		std::stringstream ss;
		size_t p = line.find(' ');
		ss << line.substr(0, p);
		ss >> jobCount;
		ss.clear();
		ss << line.substr(p);
		ss >> machineCount;
		ss.clear();

		int jid		= 0, // job id
			temp	= 0,
			i		= 0; // 
		while(std::getline(in, line)) {
			i = 0;
			Task* t;
			Job* j = new Job(jid);
			while(!line.empty()) {
				p = line.find(' ');
				if(p != std::string::npos)
					ss << line.substr(0, p);
				else
					ss << line.substr(0);
				ss >> temp;
				if(i % 2 == 0) {
					t = new Task();
					t->setJobId(jid);
					t->setMachineId(temp);
				} else {
					t->setDuration(temp);
					j->addTask(t);
					//std::cout << "task jid: " << t->getJobId() << ", machine: " << t->getMachineId() << ", duration: " << t->getDuration() << std::endl;
					//delete t;
				}
				//std::cout << "line: " << line << ", line.size() = " << line.size() << std::endl;
				if(p != std::string::npos)
					line.assign(line.substr(p+1));
				else
					line.clear();
				ss.clear();
				i++;
			}
			this->addJob(j);
			jid++;
			//std::cout << line << std::endl;
		}
		/* while(!eof) {
			getline()
			jobCount, machineCount
			for(i = 0; i < jobCount; i++) {
				getline();
				ilosc_taskow = 2*ilosc_maszyn
				wczytaj_taski
			}
		   }*/
	}
	// reading
	in.close();
}

void Scheduler::loadFromTaillard(std::string filename) {}

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