#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <vector>
#include <string>
#include "job.h"

class Scheduler {
	private:
		short int machineCount;		// how many machines are there?
		short int jobCount;		// how many jobs do we have?
		std::vector<Job*> Jobs;		// job list
		short int schedulingDuration;	// scheduling duration
	public:
		// + (input)
		bool loadFromOrlib(std::string fileName);	// load from orlib format
		bool loadFromTaillard(std::string fileName);	// load from Taillard format
		void setMachineCount(short int mCount);		// set machine count
		void setJobCount(short int jCount);		// set job count
		void addJob(Job* job);
		// - (output)
		Job* getJob(short int jobId);
		short int getJobCount();		// return job count
		short int getMachineCount();		// return machine count
		short int getSchedulingDuration();	// return the scheduling duration
		bool solveWithHeuristic(std::string fileName, short int jCount);
	Scheduler();				// default constructor
	Scheduler(int mCount, int jCount);	// set machine and job count while starting
	~Scheduler();				// clean up
};

#endif // SCHEDULER_H
