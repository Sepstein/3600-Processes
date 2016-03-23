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

void Process::overall_stats(){
	std::cout<<"Overall Process Stats"<<std::endl;//prints all process stats based on processes created
	std::cout<<"-Total processes: "<<TOTAL_PROCESSES<<std::endl;
	std::cout<<"-Average memory: "<<average_memory<<"KB"<<std::endl;
	std::cout<<"-Average cycles: "<<average_cycles<<" cycles"<<std::endl;
	std::cout<<std::endl;
}

void Process::ready_process(){
	Process_list[number_processes_ready].ready=true;
	++number_processes_ready;
	++number_processes_arrived;
}

void Process::round_robin(int number_of_processors,std::string file_name){
	std::ofstream myfile;
	std::ofstream csv_wait;
	std::string log_file=file_name+".log";
	std::string csv_wait_file=file_name+"_wait.csv";
	myfile.open(log_file.c_str(),std::fstream::out);
	csv_wait.open(csv_wait_file.c_str(),std::fstream::out);
	bool multiple_switch_check=false;
	context_switch_penalty=new int[number_of_processors];
	for(int i=0;i<number_of_processors;i++)
		context_switch_penalty[i]=0;
	while(processes_completed!=TOTAL_PROCESSES){
		if(TOTAL_PROCESSES!=number_processes_arrived){
			if(Process_list[number_processes_arrived].entrance_time<=time_passed){
				myfile<<time_passed<<": Process "<<Process_list[number_processes_arrived].process_ID<<" arrived."<<std::endl;
				ready_process();
				if(number_processes_arrived<number_of_processors)
					myfile<<time_passed+context_switch_penalty[number_processes_arrived]<<": Process "<<Process_list[number_processes_arrived-1].process_ID<<" executing."<<std::endl;
			}
		}
		int number_processors_used=number_of_processors_to_use(number_of_processors);//sets number of processors that will be used
		for(int i=0;i<number_processors_used;i++){//cycles through the simulation of what is going on in each process
		//	std::cout<<context_switch_penalty[i]<<"-";
			if(Process_list[i].time_spent==Process_list[i].number_of_cycles){//if the process is done, delete it
				csv_wait<<Process_list[i].process_ID<<","<<time_passed+context_switch_penalty[i]-Process_list[i].number_of_cycles-Process_list[i].entrance_time<<std::endl;
				myfile<<time_passed+context_switch_penalty[i]<<": Process "<<Process_list[i].process_ID<<" fully executed."<<std::endl;
				remove_process(number_of_processors,i,file_name,number_processors_used);
				if(number_processes_ready>number_of_processors)
					myfile<<time_passed+context_switch_penalty[i]<<": Process "<<Process_list[i].process_ID<<" executing."<<std::endl;
			}
			else if((Process_list[i].time_spent%TIME_QUANTUM==0)&&(number_processes_ready>number_of_processors+i)){//if time quantum is spent, will rotate to new process
				myfile<<time_passed+context_switch_penalty[i]<<": Process "<<Process_list[i].process_ID<<" time quantum expired."<<std::endl;
				rotate_processes(number_processors_used,i,multiple_switch_check);
				multiple_switch_check=true;
				myfile<<time_passed+context_switch_penalty[i]<<": Rotating in process "<<Process_list[i].process_ID<<"."<<std::endl;
			}
			++Process_list[i].time_spent;//each of these passings counts as a cycle
		}
		//std::cout<<std::endl;
		//std::cin.ignore();
		++time_passed;
		multiple_switch_check=false;
	}
	for(int i=0;i<number_of_processors;i++){
		time_passed+=context_switch_penalty[i];
		total_context_switch_penaly+=context_switch_penalty[i];
	}
	myfile.close();
	csv_wait.close();
	delete[] context_switch_penalty;
}

void Process::shortest_job_first(int number_of_processors,std::string file_name){
	std::ofstream myfile;
	std::ofstream csv_wait;
	std::string log_file=file_name+".log";
	std::string csv_file=file_name+".csv";
	myfile.open(log_file.c_str(),std::fstream::out);
	std::string csv_wait_file=file_name+"_wait.csv";
	csv_wait.open(csv_wait_file.c_str(),std::fstream::out);
	context_switch_penalty=new int[number_of_processors];
	for(int i=0;i<number_of_processors;i++)
		context_switch_penalty[i]=0;
	while(processes_completed!=TOTAL_PROCESSES){
		if(TOTAL_PROCESSES!=number_processes_arrived){
			if(Process_list[number_processes_ready].entrance_time==time_passed){
				myfile<<time_passed<<": Process "<<Process_list[number_processes_arrived].process_ID<<" arrived."<<std::endl;
				ready_process();
				for(int i=2;i<number_processes_ready;i++){
					if(Process_list[i-1].number_of_cycles>Process_list[i].number_of_cycles){	
						Process_values temp = Process_list[i-1];
						Process_list[i-1] = Process_list[i];
						Process_list[i] = temp;
					}
				}
			}
		}
		++time_passed;
		int number_processors_used=number_of_processors_to_use(number_of_processors);//sets number of processors that will be used
		for(int i=0;i<number_processors_used;i++){//cycles through the simulation of what is going on in each process
			++Process_list[i].time_spent;//each of these passings counts as a cycle
			if(Process_list[i].time_spent==Process_list[i].number_of_cycles){//if the process is done, delete it
				csv_wait<<Process_list[i].process_ID<<","<<time_passed+context_switch_penalty[i]-Process_list[i].number_of_cycles-Process_list[i].entrance_time<<std::endl;
				myfile<<time_passed+context_switch_penalty[i]<<": Process "<<Process_list[i].process_ID<<" fully executed."<<std::endl;
				remove_process(number_of_processors,i,file_name,number_processors_used);
				myfile<<time_passed+context_switch_penalty[i]<<": Process "<<Process_list[i].process_ID<<" entered processor."<<std::endl;

			}
		}
	}
	for(int i=0;i<number_of_processors;i++){
		time_passed+=context_switch_penalty[i];
		total_context_switch_penaly+=context_switch_penalty[i];
	}
	myfile.close();
	csv_wait.close();
	delete[] context_switch_penalty;
}

void Process::first_in_first_out(int number_of_processors,std::string file_name){
	std::ofstream myfile;
	std::ofstream csv_wait;
	std::string log_file=file_name+".log";
	myfile.open(log_file.c_str(),std::fstream::out);
	std::string csv_wait_file=file_name+"_wait.csv";
	csv_wait.open(csv_wait_file.c_str(),std::fstream::out);
	context_switch_penalty=new int[number_of_processors];
	for(int i=0;i<number_of_processors;i++)
		context_switch_penalty[i]=0;
	while(processes_completed!=TOTAL_PROCESSES){
		if(TOTAL_PROCESSES!=number_processes_arrived){
			if(Process_list[number_processes_arrived].entrance_time<=time_passed){
				myfile<<time_passed<<": Process "<<Process_list[number_processes_arrived].process_ID<<" arrived."<<std::endl;
				ready_process();
			}
		}
		++time_passed;
		int number_processors_used=number_of_processors_to_use(number_of_processors);//sets number of processors that will be used
		for(int i=0;i<number_processors_used;i++){//cycles through the simulation of what is going on in each process
			++Process_list[i].time_spent;//each of these passings counts as a cycle				
			if(Process_list[i].time_spent==Process_list[i].number_of_cycles){//if the process is done, delete it
				csv_wait<<Process_list[i].process_ID<<","<<time_passed+context_switch_penalty[i]-Process_list[i].number_of_cycles-Process_list[i].entrance_time<<std::endl;
				myfile<<time_passed+context_switch_penalty[i]<<": Process "<<Process_list[i].process_ID<<" fully executed."<<std::endl;
				remove_process(number_of_processors,i,file_name,number_processors_used);
				myfile<<time_passed+context_switch_penalty[i]<<": Process "<<Process_list[i].process_ID<<" entered processor."<<std::endl;
			}
		}
	}
	for(int i=0;i<number_of_processors;i++){
		time_passed+=context_switch_penalty[i];
		total_context_switch_penaly+=context_switch_penalty[i];
	}
	myfile.close();
	csv_wait.close();
	delete[] context_switch_penalty;
}

void Process::remove_process(int number_of_processors,int i,std::string file_name,int number_processors_used){
	++processes_completed;
	Process_list[i].completion_time=time_passed+context_switch_penalty[i];
	average_completion_time=(average_completion_time+Process_list[i].completion_time);
	Process_list[i].wait_time=Process_list[i].completion_time-Process_list[i].time_spent+context_switch_penalty[i]-Process_list[i].entrance_time;
	average_wait_time=(average_wait_time+Process_list[i].wait_time);
	print_to_file(file_name,number_of_processors,i);
	Process_list[i]=Process_list[number_processors_used];
	Process_list.erase(Process_list.begin()+number_processors_used);
	if(number_processes_ready>number_of_processors)
		context_switch_penalty[i]=context_switch_penalty[i]+10;
	--number_processes_ready;
}

void Process::rotate_processes(int number_processors_used,int i,bool multiple_switch_check){
	if(multiple_switch_check==false)
		context_switch_penalty[i]+=10;
	Process_values temp=Process_list[i];
	Process_list[i]=Process_list[number_processors_used];
	std::rotate(Process_list.begin()+number_processors_used,Process_list.begin()+number_processors_used+1,Process_list.begin()+number_processes_ready);
	Process_list[number_processes_ready-1]=temp;
}

int Process::number_of_processors_to_use(int number_of_processors){
	if(number_processes_ready<number_of_processors)
		return number_processes_ready;
	else
		return number_of_processors;
}

/*******************************************************************
Function: Write processes to specified file
Param:
	
	none
Return:
	void
***************************************************************/
void Process::print_to_file(std::string file_name,int number_of_processors,int i){
	std::ofstream myfile;
	file_name+=".txt";
	if(processes_completed==0){
		myfile.open(file_name.c_str(),std::fstream::out);
		myfile<<"Number of processors used: "<<number_of_processors<<std::endl<<std::endl;
	}
	else
		myfile.open(file_name.c_str(),std::fstream::app|std::fstream::out);
	myfile<<"****************************************************"<<std::endl;
	myfile<<"Process ID: "<<Process_list[i].process_ID<<std::endl;
	myfile<<"Memory Used: "<<Process_list[i].memory_footprint<<"KB"<<std::endl;
	myfile<<"Number of Cycles: "<<Process_list[i].number_of_cycles<<std::endl<<std::endl;
	myfile<<"Entrance time: "<<Process_list[i].entrance_time<<std::endl;
	myfile<<"Completion time: "<<Process_list[i].completion_time<<std::endl;
	myfile<<"Wait time: "<<Process_list[i].wait_time<<std::endl;
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
void Process::print_stats(int number_of_processors,std::string process_method_used){
	std::cout<<"-Total completion time: "<<time_passed<<" cyclees"<<std::endl;
	std::cout<<"-Average completion time: "<<average_completion_time/TOTAL_PROCESSES<<" cycles"<<std::endl;
	std::cout<<"-Average wait time: "<<average_wait_time/TOTAL_PROCESSES<<" cycles"<<std::endl;
	std::cout<<"-Context switch penalty: "<<total_context_switch_penaly<<" cycles"<<std::endl;
	std::cout<<std::endl;
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
	for(unsigned int i=0;i<Process_list.size();i++){
		std::cout<<"Process Number: "<<i+1<<std::endl<<std::endl;//Prints each Process in the order they are stored in the queue.
		std::cout<<"Process ID: "<<Process::Process_list[i].process_ID<<std::endl;
		std::cout<<"Memory Used: "<<Process::Process_list[i].memory_footprint<<"KB"<<std::endl;
		std::cout<<"Number of Cycles: "<<Process::Process_list[i].number_of_cycles<<std::endl;
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
	processes_completed=0;
	time_passed=0;
	average_wait_time=0;
	average_completion_time=0;
	context_switch_penalty=0;
	total_memory=0;
	total_cycles=0;
	average_cycles=0;
	average_memory=0;
	number_of_processes=0;
	number_processes_ready=0;
	number_processes_arrived=0;
	total_context_switch_penaly=0;
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
Process::Process_values::Process_values(int id, long int cycles, float memory,int entry_time){
	process_ID=id;//values passed in are assigned to process
	number_of_cycles=cycles;
	memory_footprint=memory;
	time_spent=0;
	completion_time=0;
	entrance_time=entry_time;
	wait_time=0;
	ready=false;
}

/*******************************************************************
Function: Adds a process to go through to the queue;
Param:
	none void
Return:
	void
***************************************************************/
void Process::add_process(int entrance_time){
	int new_cycles=generate_cycles();//generates cycles and memory to go along with the new process
	int new_memory=generate_memory();
	Process_values new_process(number_of_processes,new_cycles,new_memory,entrance_time);//first process always starts with 1 and incremented from there
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
