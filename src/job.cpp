#include "../include/job.h"

Job::Job(short int id) {
	this->id = id;
	this->duration = 0;
	this->remainingTime = 0;
}

Job::~Job() {
	for(unsigned int i = 0; i < Tasks.size(); i++) delete Tasks[i];
	this->Tasks.clear();
}

void Job::addTask(Task* task) {
	this->Tasks.push_back(task);
}

void Job::setRemainingTime() {
	if(! (this->Tasks.empty()) ) {
		for (unsigned short int i = 0; i < this->Tasks.size(); i++) {
			this->remainingTime += this->Tasks[i]->getDuration();
		}
	}
}

void Job::setDuration(short int dur) {
	this->duration = dur;
}

Task* Job::getTask(short int taskId) {
	return this->Tasks[taskId];
}

short int Job::getJobId() {
	return this->id;
}

short int Job::getJobDuration() {
	return this->duration;
}

short int Job::getTaskCount() {
	return this->Tasks.size();
}
