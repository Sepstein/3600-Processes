/**********************************************
Name: Jamie Simpson
Class: CSCE 4600-001
Program: Process Simulator Pt.1 
File: Main function which declares instances
***********************************************/

#include "Processes.h"

int main(int argc,char* argv[]){
	if(argc<2){
		std::cout<<"Error: Pass proccessing method as an arugment."<<std::endl;
		display_options();
		return 0;
	}
	std::string process_method=argv[1];
	if(strcasecmp(process_method.c_str(),"RR")&&strcasecmp(process_method.c_str(),"SJF")&strcasecmp(process_method.c_str(),"FIFO")){
		std::cout<<"Error: Invalid processing method entered."<<std::endl;
		display_options();
		return 0;
	}
	srand(time(NULL));//sends rand
	Process process;
	process.create_processes(50,process_method);//creates 100 process for assignment
	process.print_stats();
	return 0;
}

void display_options(){
		std::cout<<"Options are:"<<std::endl;
		std::cout<<"RR (Round Robin)"<<std::endl;
		std::cout<<"SJF (Shortest Job First)"<<std::endl;
		std::cout<<"FIFO (First In-First Out)"<<std::endl;
}