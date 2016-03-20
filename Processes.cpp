/**********************************************
Name: Jamie Simpson
Class: CSCE 4600-001
Program: Process Simulator Pt.1 
File: Contains the functions for creating new processes
***********************************************/

#include "Processes.h"

/*******************************************************************
Function: Creates a specified number of process to add to queue
Param:
	@int number_to_create: Number or procceses to create
Return:
	void
***************************************************************/
void Process::create_processes(std::string process_method,int number_of_processors){
	while(processes_completed!=TOTAL_PROCESSES){
	//	std::cout<<number_of_processes;
		if((time_passed%TIME_QUANTUM==0)&&(number_of_processes!=TOTAL_PROCESSES))
			add_process();
		if(Process_list.empty())
			continue;
		if(strcasecmp(process_method.c_str(),"rr")==0){
			round_robin(number_of_processors);
		}
		else if(strcasecmp(process_method.c_str(),"sjf")==0)
			;//call SJF function
		else if(strcasecmp(process_method.c_str(),"fifo")==0)
			;//call FIFO function
		++time_passed;
	}
	std::cout<<"Done! Find process results in generated text file \"Procceses_output.txt\"."<<std::endl;
}

void Process::round_robin(int number_of_processors){
	int number_processors_used=number_of_processors;
	if(Process_list.size()<4)
		number_processors_used=Process_list.size();
	for(int i=0;i<number_processors_used;i++){
		++Process_list[i].time_spent;
		if(Process_list[i].time_spent==Process_list[i].number_of_cycles){
			++processes_completed;
			Process_list[i].completion_time=time_passed;
			average_completion_time=(average_completion_time+Process_list[i].completion_time)/processes_completed;
			Process_list[i].wait_time=Process_list[i].completion_time-Process_list[i].number_of_cycles-Process_list[i].entrance_time;
			average_wait_time=(average_wait_time+Process_list[i].wait_time)/processes_completed;
			print_to_file("round_robin_sort.txt",number_of_processors);
			Process_list.erase(Process_list.begin()+i);
			if(number_of_processors>number_of_processors){
				context_switch_penalty+=10;
				time_passed+=10;
			}
		}
		else if((Process_list.front().time_spent%TIME_QUANTUM==0)&&(number_of_processes>number_of_processors)){
			std::rotate(Process_list.begin()+i,Process_list.begin()+number_processors_used,Process_list.end());
			context_switch_penalty+=10;
			time_passed+=10;
		}
	}
}

/*******************************************************************
Function: Write processes to specivied file
Param:
	none
Return:
	void
***************************************************************/
void Process::print_to_file(std::string sort_name,int number_of_processors){
	std::ofstream myfile;
	if(processes_completed==0){
		myfile.open(sort_name.c_str(),std::fstream::out);
		myfile<<"Number of processors used: "<<number_of_processors<<std::endl<<std::endl;
	}
	else
		myfile.open(sort_name.c_str(),std::fstream::app|std::fstream::out);
	myfile<<"****************************************************"<<std::endl;
	myfile<<"Process ID: "<<Process_list.front().process_ID<<std::endl;
	myfile<<"Memory Used: "<<Process_list.front().memory_footprint<<"KB"<<std::endl;
	myfile<<"Number of Cycles: "<<Process_list.front().number_of_cycles<<std::endl<<std::endl;
	myfile<<"Entrance time: "<<Process_list.front().entrance_time<<std::endl;
	myfile<<"Completion time: "<<Process_list.front().completion_time<<std::endl;
	myfile<<"Wait time: "<<Process_list.front().wait_time<<std::endl;
	myfile<<"****************************************************"<<std::endl<<std::endl;
	myfile.close();
}

/*******************************************************************
Function: Prints statistics based on the Processes created.
Param:
	none
Return:
	void
***************************************************************/
void Process::print_stats(){
	std::cout<<"****************************************************"<<std::endl;
	std::cout<<"Process Stats"<<std::endl<<std::endl;//prints all process stats based on processes created
	std::cout<<"Total processes: "<<processes_completed<<std::endl;
	std::cout<<"Average memory: "<<average_memory<<"KB"<<std::endl;
	std::cout<<"Average cycles: "<<average_cycles<<" cycles"<<std::endl<<std::endl;
	std::cout<<"Average wait time: "<<average_wait_time<<" cycles"<<std::endl;
	std::cout<<"Average completion time: "<<average_completion_time<<" cycles"<<std::endl;
	std::cout<<"Context switch penalty: "<<context_switch_penalty<<" cycles"<<std::endl;
	std::cout<<"****************************************************"<<std::endl;
}

/*******************************************************************
Function: Prints each process and the specifics assigned to it.
Param:
	void
Return:
	void
***************************************************************/
void Process::print_processes(){
	std::cout<<"****************************************************"<<std::endl;
	std::cout<<"List of Processes"<<std::endl<<std::endl;
	std::cout<<"--------------------------------------------------"<<std::endl;
	for(int i=0;i<Process_list.size();i++){
		std::cout<<"Process Number: "<<i+1<<std::endl<<std::endl;//Prints each Process in the order they are stored in the queue.
		std::cout<<"Process ID: "<<Process_list[i].process_ID<<std::endl;
		std::cout<<"Memory Used: "<<Process_list[i].memory_footprint<<"KB"<<std::endl;
		std::cout<<"Number of Cycles: "<<Process_list[i].number_of_cycles<<std::endl;
		if(i+1!=Process_list.size())
			std::cout<<"--------------------------------------------------"<<std::endl;
	}
	std::cout<<"****************************************************"<<std::endl<<std::endl;
}

/*******************************************************************
Function: Constructor for Process class
Param:
	none
Return:
	void
***************************************************************/
Process::Process(){
	total_memory=0;
	total_cycles=0;
	average_cycles=0;
	average_memory=0;
	cycles_in_queue=0;
	processes_completed=0;
	time_passed=0;
	number_of_processes=0;
	average_wait_time=0;
	average_completion_time=0;
	context_switch_penalty=0;
}

/**********************************************************************
Function: Constructor for process list that passes in new processer data.
Param:
	int id: New process id
	long int cycles: Number of cycles that it takes for process to complete
	int memory: Amount of memory process uses
Return:
	voidadd_
***************************************************************************/
Process::Process_values::Process_values(int id, long int cycles, float memory,int time){
	process_ID=id;//values passed in are assigned to process
	number_of_cycles=cycles;
	memory_footprint=memory;
	time_spent=0;
	completion_time=0;
	entrance_time=time;
	wait_time=0;
}

/*******************************************************************
Function: Adds a process to go through to the queue;
Param:
	none void
Return:
	void
***************************************************************/
void Process::add_process(){
	int new_cycles=generate_cycles();//generates cycles and memory to go along with the new process
	int new_memory=generate_memory();
	Process_values new_process(number_of_processes,new_cycles,new_memory,(int)time_passed);//first process always starts with 1 and incremented from there
	Process_list.push_back(new_process);
	++number_of_processes;//increments number of process
	total_memory+=new_memory;
	total_cycles+=new_cycles;
	average_memory=total_memory/number_of_processes;
	average_cycles=total_cycles/number_of_processes;
}

/*******************************************************************
Function: Generates cycles for a given process
Param:
	none
Return:
	long int: Number of Cycles
***************************************************************/
long int Process::generate_cycles(){
	return (rand()%(MAX_CYCLE-MIN_CYCLE+1)+1000);//generates cycles with a mean of 6000 and range 1000-11000
}

/*******************************************************************
Function: Generates Memory for a given process
Param:
	none
Return:
	float: Amount of memory
***************************************************************/		
float Process::generate_memory(){
	int bound_selector=rand()%100;//this is used to select if bounds will be below or above the mean of 20.
	float memory;
	float random = ((float) rand()) / (float) RAND_MAX;//generates a floating mem number
	if(bound_selector<80)//Necessary to set mean of 20.
    		memory = (random * (MEAN_MEM-MIN_MEM))+MIN_MEM;
	else
		memory = (random * (MAX_MEM-MEAN_MEM))+MEAN_MEM;
	return memory;
}
