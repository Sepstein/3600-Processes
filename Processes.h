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
			bool ready;
			Process_values(int,long int,float,int);//initializer for each process
		};
		std::vector<struct Process_values> Process_list;//list of processors
		float total_memory;//sum of memory used by processes
		long int total_cycles;//totall cycles that it will take to execute all process
		float average_memory;//average memory used by processes
		long int average_cycles;//average cycles that it will take to complete each process;
		int processes_completed;
		long int time_passed;
		int number_of_processes;
		int average_wait_time;
		int average_completion_time;
		int context_switch_penalty;
		int number_processes_ready;
		int number_processes_arrived;
		int number_of_processors_to_use(int);
		long int generate_cycles();//generates the number of cycles based on given range
		float generate_memory();//generates amount of memory given range
		void print_to_file(std::string,int,int);
		void print_processes();//print all processes in queue
		void rotate_processes(int,int);
		void remove_process(int,int,std::string,int);
		void ready_process();
	public:
		Process();
		void print_stats(int,std::string);//print statistics regarding to how much memory and cycles the ueued process take
		void add_process(int);//adds new process
		void round_robin(int,std::string);
		void first_in_first_out(int,std::string);
		void overall_stats();
};

void display_options();
void display_stats();
