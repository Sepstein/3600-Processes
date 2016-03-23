/**********************************************
Name: Jamie Simpson
Class: CSCE 4600-001
Program: Process Simulator Pt.1 
File: Contains libraries and constant declarations.
***********************************************/

#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <strings.h>
#include <string>
#include <stdio.h>
#include <string.h>

//defintion of the processor property ranges as defined in the problem.
const int MAX_CYCLE=11000;
const int MIN_CYCLE=1000;
const int MIN_MEM=1;
const int MEAN_MEM=20;
const int MAX_MEM=100;
const int TIME_QUANTUM=50;
const int TOTAL_PROCESSES=50;