#include "../include/scheduler.h"
#include <sstream>
#include <fstream>
#include <list>
#include <iostream> // temporary, debugging purposes only [!]

std::vector<Job*> Scheduler::Jobs;

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

bool Scheduler::task_compare (Task* t1, Task* t2) {
	if(Scheduler::Jobs[t1->getJobId()]->getRemainingTime() < Scheduler::Jobs[t2->getJobId()]->getRemainingTime()) return true;
	else return false;
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
					this->getJob(jid)->getTask(tid)->setMachineId(temp-1);
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
		const short int taskCount = machineCount;
		std::vector< std::list<Task*> > MachineUsage;
		short int StopTimes [taskCount];
		//std::cout << "MachineUsage OK" << std::endl;
		for(int i = 0; i < taskCount; i++) {
			//std::cout << "Created list l, pushing it to MachineUsage" << std::endl;
			std::list<Task*> l;
			MachineUsage.push_back(l);
			//std::cout << "StopTimes[" << i << "] = 0" << std::endl;
			StopTimes[i] = 0;
		}
		//std::cout << "Everything prepared, MachineUsage.size() = " << MachineUsage.size() << std::endl;
		int max_scheduling_time = 0;
		for(int t = 0; t < taskCount; t++) {
			//std::cout << "Task " << t << std::endl;
			for(int i = 0; i < machineCount; i++) MachineUsage[i].clear();

			for (int j = 0; j < jCount; j++) {
				Task* cur_task = getJob(j)->getTask(t);
				//std::cout << "Task " << t << " of job " << j << " goes to machine " << cur_task->getMachineId() << std::endl;
				MachineUsage[cur_task->getMachineId()].push_back(cur_task);
				//std::cout << "Task pushed at MachineUsage" << std::endl;
			}

			//for(int cur_machine = 0; cur_machine < machineCount; cur_machine++) MachineUsage[cur_machine].sort(task_compare);
			// posortuj MachineUsage[i], i = 0,1, ... , machineCount-1 po Jobs[jobId]->getRemainingTime() [list::sort] 

			for(int i = 0; i < machineCount; i++) {
				for(std::list<Task*>::iterator cur_task = MachineUsage[i].begin(); cur_task != MachineUsage[i].end(); ++cur_task) {
					//std::cout << "[machine " << i << "] task job remaining time: " << Jobs[(*cur_task)->getJobId()]->getRemainingTime() << std::endl;
					const short int job_dur = Jobs[(*cur_task)->getJobId()]->getJobDuration(),
									task_start_time = std::max(StopTimes[(*cur_task)->getMachineId()], job_dur);
					short int task_end_time = task_start_time + (*cur_task)->getDuration();

					(*cur_task)->setStartTime(task_start_time);

					//std::cout << "Current task at machine " << i << " starts at " <<  task_start_time << " and ends at " << task_end_time << std::endl;

					StopTimes[(*cur_task)->getMachineId()] = task_end_time;
					Jobs[(*cur_task)->getJobId()]->setDuration(task_end_time);
					if(task_end_time > max_scheduling_time) max_scheduling_time = task_end_time;
					short int job_rem_time = Jobs[(*cur_task)->getJobId()]->getRemainingTime();
					Jobs[(*cur_task)->getJobId()]->setRemainingTime(job_rem_time - (*cur_task)->getDuration());
				}
			}
		}
		std::cout << max_scheduling_time << std::endl;
		out << max_scheduling_time << std::endl;
		for(int i = 0; i < jCount; i++) {
			for(int j = 0; j < taskCount; j++) {
				//out << getJob(i)->getTask(j)->getStartTime() << " " << getJob(i)->getTask(j)->getStartTime()+getJob(i)->getTask(j)->getDuration() << " "; // output dla wykresów
				out << getJob(i)->getTask(j)->getStartTime() << " ";
			}
			out << std::endl;
		}
		out.close();
		return true;
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
