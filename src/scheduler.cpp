#include "../include/scheduler.h"

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

void Scheduler::loadFromOrlib(std::string filename) {}

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
