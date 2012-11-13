#ifndef JOB_H
#define JOB_H
#include <vector>
#include "task.h"

class Job {
	private:
		std::vector<Task*> Tasks;
		short int id;
		short int startTime;
		short int duration;
	public:
		// + (input)
		void addTask(Task* task);
		void setStartTime(short int t);
		void setDuration(short int dur);
		// - (output)
		Task* getTask(short int taskId);
		short int getJobId();
		short int getStartTime();
		short int getJobDuration();
		short int getTaskCount();
	// constructors and destructors
	Job(short int id);
	~Job();
};

#endif // JOB_H
