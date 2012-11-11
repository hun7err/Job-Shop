#include "../include/job.h"

Job::Job(short int id) {
	this->id = id;
	this->duration = 0;
	this->startTime = 0;
}

Job::~Job() {
	this->Tasks.clear();
}

void Job::addTask(Task* task) {
	this->Tasks.push_back(task);
}

void Job::setStartTime(short int t) {
	this->startTime = t;
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

short int Job::getStartTime() {
	return this->startTime;
}

short int Job::getJobDuration() {
	return this->duration;
}