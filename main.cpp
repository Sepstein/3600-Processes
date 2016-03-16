/**********************************************
Name: Jamie Simpson
Class: CSCE 4600-001
Program: Process Simulator Pt.1 
File: Main function which declares instances
***********************************************/

#include "Processes.h"

int main(int argc,char* argv[]){
	srand(time(NULL));//sends rand
	Process process;
	process.create_processes(50);//creates 100 process for assignment
//	process.print_stats();//prints stats from generated file
	process.print_to_file();
	return 0;
}
