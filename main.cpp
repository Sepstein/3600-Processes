/**********************************************
Name: Jamie Simpson
Class: CSCE 4600-001
Program: Process Simulator Pt.1 
File: Main function which declares instances
***********************************************/

#include "Processes.h"

int main(int argc,char* argv[]){
	if(argc<3){
		std::cout<<"Error: Pass proccessing method and number of processors as an arugment."<<std::endl;
		display_options();
		return 0;
	}
	std::string process_method=argv[1];
	std::string number_of_processors=argv[2];
	if(strcasecmp(process_method.c_str(),"RR")!=0&&strcasecmp(process_method.c_str(),"SJF")!=0&&strcasecmp(process_method.c_str(),"FIFO")!=0){
		std::cout<<"Error: Invalid processing method entered."<<std::endl;
		display_options();
		return 0;
	}
	srand(time(NULL));//sends rand
	Process process;
	if(strcasecmp(number_of_processors.c_str(),"single")==0)
		process.create_processes(process_method,1);//creates 100 process for assignment
	else if(strcasecmp(number_of_processors.c_str(),"quad")==0)
		process.create_processes(process_method,4);
	else{
		std::cout<<"Error: Invalid number of processors selected"<<std::endl;
		return 0;
	}
	process.print_stats();
	return 0;
}

void display_options(){
		std::cout<<"First argument options are:"<<std::endl;
		std::cout<<"RR (Round Robin)"<<std::endl;
		std::cout<<"SJF (Shortest Job First)"<<std::endl;
		std::cout<<"FIFO (First In-First Out)"<<std::endl;
		std::cout<<std::endl;
		std::cout<<"Second argument options are:"<<std::endl;
		std::cout<<"SINGLE (One processor)"<<std::endl;
		std::cout<<"QUAD (Four processors)"<<std::endl;
}