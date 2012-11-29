#ifndef JOB_H
#define JOB_H
#include <vector>
#include "task.h"

class Job {
	private:
		std::vector<Task*> Tasks;  // zrobic z tego liste i dodac metody odpowiadajce push_front, pop_front itp.
		short int id;
		short int remainingTime;
		short int duration;
	public:
		// + (input)
		void addTask(Task* task);
		void setRemainingTime();
		void setDuration(short int dur);
		void setRemainingTime(short int t);
		// - (output)
		Task* getTask(short int taskId);
		short int getJobId();
		short int getStartTime();
		short int getJobDuration();
		short int getTaskCount();
		short int getRemainingTime();
	// constructors and destructors
	Job(short int id);
	~Job();
};

#endif // JOB_H
