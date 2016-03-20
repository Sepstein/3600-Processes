/**********************************************
Name: Jamie Simpson
Class: CSCE 4600-001
Program: Process Simulator Pt.1 
File: Contains prototypes for functions of the processes.
***********************************************/

#include "declarations.h"

class Process{
	private:
		struct Process_values{
			int process_ID;//unique process id for each process
			long int number_of_cycles;//number of cycles reuired to finish process
			int memory_footprint;//amount of memory used by process
			int time_spent;
			int completion_time;
			int entrance_time;
			int wait_time;
			Process_values(int,long int,float,int);//initializer for each process
		};
		std::vector<struct Process_values> Process_list;//list of processors
		float total_memory;//sum of memory used by processes
		long int total_cycles;//totall cycles that it will take to execute all process
		float average_memory;//average memory used by processes
		long int average_cycles;//average cycles that it will take to complete each process;
		long int generate_cycles();//generates the number of cycles based on given range
		float generate_memory();//generates amount of memory given range
		void add_process();//adds new process
		void round_robin(int);
		int cycles_in_queue;
		int processes_completed;
		long int time_passed;
		int number_of_processes;
		int average_wait_time;
		int average_completion_time;
		int context_switch_penalty;
	public:
		Process();
		~Process(){};
		void create_processes(std::string,int);//creates a specified number of processes
		void print_to_file(std::string);
		void print_stats();//print statistics regarding to how much memory and cycles the ueued process take
		void print_processes();//print all processes in queue
};

void display_options();