/**********************************************
Name: Jamie Simpson, Sam Epstein, Juan Apolinar
Class: CSCE 4600-001
Program: Project 1 comparing different scheduling algorithms. FIFO, Round Robin, SJF
File: Main function which declares instances
***********************************************/

#include "Processes.h"

int main(int argc,char* argv[]){
	//takes in the arguements which consist of the scheduling process and whether it is single core or quad core 
	std::string process_choice="all";
	std::string which_processors="both";
	if(argc==2)
		process_choice=argv[1];
	else if(argc>=3){
		process_choice=argv[1];
		which_processors=argv[2];
	}
	if(strcasecmp(process_choice.c_str(),"RR")!=0&&strcasecmp(process_choice.c_str(),"SJF")!=0&&strcasecmp(process_choice.c_str(),"FIFO")!=0&&strcasecmp(process_choice.c_str(),"all")!=0){
		std::cout<<"Error: Invalid processing method entered."<<std::endl;
		display_options();
		return 0;
	}
	if(strcasecmp(which_processors.c_str(),"both")!=0&&strcasecmp(which_processors.c_str(),"single")!=0&&strcasecmp(which_processors.c_str(),"quad")!=0){
		std::cout<<"Error: Invalid processor number entered."<<std::endl;
		display_options();
		return 0;
	}
	srand(time(NULL));//sends rand
	Process RR_single_processor;
	for(int i=0;i<TOTAL_PROCESSES;i++)
		RR_single_processor.add_process(i*TIME_QUANTUM);
	Process RR_quad_processor=RR_single_processor;
	Process FIFO_single_processor=RR_single_processor;
	Process FIFO_quad_processor=RR_single_processor;
	Process SJF_single_processor=RR_single_processor;
	Process SJF_quad_processor=RR_single_processor;
	std::string process_method_used;
	int number_processors;	
	RR_single_processor.overall_stats();
	if(strcasecmp(process_choice.c_str(),"all")==0||strcasecmp(process_choice.c_str(),"rr")==0){
		process_method_used="Round Robin";
		if(strcasecmp(which_processors.c_str(),"single")==0||strcasecmp(which_processors.c_str(),"both")==0){
			number_processors=1;
			RR_single_processor.round_robin(number_processors,"round_robin_single");
			print_finish_message(process_method_used,number_processors);
			RR_single_processor.print_stats(number_processors,process_method_used);
		}
		if(strcasecmp(which_processors.c_str(),"quad")==0||strcasecmp(which_processors.c_str(),"both")==0){
			number_processors=4;
			RR_quad_processor.round_robin(number_processors,"round_robin_quad");
			print_finish_message(process_method_used,number_processors);
			RR_quad_processor.print_stats(number_processors,process_method_used);
		}
	}
	if(strcasecmp(process_choice.c_str(),"all")==0||strcasecmp(process_choice.c_str(),"fifo")==0){
		process_method_used="First In First Out";
		if(strcasecmp(which_processors.c_str(),"single")==0||strcasecmp(which_processors.c_str(),"both")==0){
			number_processors=1;
			FIFO_single_processor.first_in_first_out(number_processors,"first_in_first_out");
			print_finish_message(process_method_used,number_processors);
			FIFO_single_processor.print_stats(number_processors,process_method_used);
		}
		if(strcasecmp(which_processors.c_str(),"quad")==0||strcasecmp(which_processors.c_str(),"both")==0){
			number_processors=4;
			FIFO_quad_processor.first_in_first_out(number_processors,"first_in_first_out");
			print_finish_message(process_method_used,number_processors);
			FIFO_quad_processor.print_stats(number_processors,process_method_used);
		}
	}

	if(strcasecmp(process_choice.c_str(),"all")==0||strcasecmp(process_choice.c_str(),"SJF")==0){
		process_method_used="Shortest Job First";
		if(strcasecmp(which_processors.c_str(),"single")==0||strcasecmp(which_processors.c_str(),"both")==0){
			number_processors=1;
			SJF_single_processor.shortest_job_first(number_processors,"shortest_job_first");
			print_finish_message(process_method_used,number_processors);
			SJF_single_processor.print_stats(number_processors,process_method_used);
		}
		if(strcasecmp(which_processors.c_str(),"quad")==0||strcasecmp(which_processors.c_str(),"both")==0){
			number_processors=4;
			SJF_quad_processor.shortest_job_first(number_processors,"shortest_job_first");
			print_finish_message(process_method_used,number_processors);
			SJF_quad_processor.print_stats(number_processors,process_method_used);
		}
	}
	return 0;
}

void display_options(){
	//tells the user what algorithms are available and how many processors will be used
	std::cout<<"First argument options are:"<<std::endl;
	std::cout<<"RR (Round Robin)"<<std::endl;
	std::cout<<"SJF (Shortest Job First)"<<std::endl;
	std::cout<<"FIFO (First In-First Out)"<<std::endl;
	std::cout<<"ALL (do all of the above individually (default))"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Second argument options are:"<<std::endl;
	std::cout<<"single (One processor)"<<std::endl;
	std::cout<<"quad (Four processors)"<<std::endl;
	std::cout<<"both (Do with both single and quad processors (default))"<<std::endl;
	std::cout<<std::endl;
}

void print_finish_message(std::string process_method_used,int number_processors){
	std::cout<<"Finished "<<process_method_used<<" with "<<number_processors<<" processor(s)! Find process results in generated text file."<<std::endl;
}