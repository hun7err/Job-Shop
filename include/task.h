#ifndef TASK_H
#define TASK_H

class Task {
	private:
		short int machineId;
		short int duration;
		short int jobId;
		short int startTime;
	public:
		// + (input)
		void setMachineId(short int mid);
		void setJobId(short int jid);
		void setDuration(short int dur);
		// - (output)
		short int getMachineId();
		short int getDuration();
		short int getJobId();
		short int getStartTime();
	Task();
	Task(short int jid, short int mid, short int dur);
};

#endif // TASK_H
