#include "../include/scheduler.h"
#include <fstream>

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
void Scheduler::loadFromOrlib(std::string filename) {
	std::ifstream in;
	in.open(filename.c_str(), std::ifstream::in);
	if(in.is_open()) {
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
