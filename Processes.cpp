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
void Process::create_processes(int number_to_create){
	while(processes_completed!=TOTAL_PROCESSES){
		if((time_passed%TOTAL_PROCESSES==0)&&(number_of_processes!=TOTAL_PROCESSES))
			add_process();
		
	}
	for(int i=0;i<number_to_create;i++)
		add_process();//adds a new process to the queue;
	std::cout<<"Done! Find process results in generated text file \"Procceses_output.txt\"."<<std::endl;
}

/*******************************************************************
Function: Write processes to specivied file
Param:
	none
Return:
	void
***************************************************************/
void Process::print_to_file(){
	std::ofstream myfile;
	myfile.open("Processes_output.txt");
	myfile<<"****************************************************"<<std::endl;
	myfile<<"List of Processes"<<std::endl<<std::endl;
	myfile<<"--------------------------------------------------"<<std::endl;
	for(int i=0;i<Process_list.size();i++){
		myfile<<"Process Number: "<<i+1<<std::endl<<std::endl;//Prints each Process in the order they are stored in the queue.
		myfile<<"Process ID: "<<Process_list[i].process_ID<<std::endl;
		myfile<<"Memory Used: "<<Process_list[i].memory_footprint<<"KB"<<std::endl;
		myfile<<"Number of Cycles: "<<Process_list[i].number_of_cycles<<std::endl;
		if(i+1!=Process_list.size())
			myfile<<"--------------------------------------------------"<<std::endl;
	}
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
/*void Process::print_stats(){
	std::cout<<"****************************************************"<<std::endl;
	std::cout<<"Process Stats"<<std::endl<<std::endl;//prints all process stats based on processes created
	std::cout<<"Total processes: "<<total_processes<<std::endl;
	std::cout<<"Average memory: "<<average_memory<<"KB"<<std::endl;
	std::cout<<"Average cycles: "<<average_cycles<<std::endl;
	std::cout<<"****************************************************"<<std::endl;
}*/

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
//	total_processes=0;
	total_cycles=0;
	average_cycles=0;
	average_memory=0;
	cycles_in_queue=0;
	processes_completed=0;
	time_passed=0;
	number_of_processes=0;
}

/**********************************************************************
Function: Constructor for process list that passes in new processer data.
Param:
	int id: New process id
	long int cycles: Number of cycles that it takes for process to complete
	int memory: Amount of memory process uses
Return:
	void
***************************************************************************/
Process::Process_values::Process_values(int id, long int cycles, float memory){
	process_ID=id;//values passed in are assigned to process
	number_of_cycles=cycles;
	memory_footprint=memory;
	time_spent=0;
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
	if(Process_list.empty()){
		Process_values new_process(1,new_cycles,new_memory);//first process always starts with 1 and incremented from there
		Process_list.push_back(new_process);
	}
	else{
		Process_values new_process(Process_list.back().process_ID+1,new_cycles,new_memory);//new cycles pushed to back of queue;
		Process_list.push_back(new_process);
	}
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
