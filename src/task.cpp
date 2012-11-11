#include "../include/job.h"

Task::Task() {}

Task::Task(short int jid, short int mid, short int dur) {
	this->jobId = jid;
	this->machineId = mid;
	this->duration = dur;
}

short int Task::getMachineId() {
	return this->machineId;
}

short int Task::getDuration() {
	return this->duration;
}

short int Task::getJobId() {
	return this->jobId;
}

void Task::setMachineId(short int mid) {
	this->machineId = mid;
}

void Task::setJobId(short int jid) {
	this->jobId = jid;
}

void Task::setDuration(short int dur) {
	this->duration = dur;
}
