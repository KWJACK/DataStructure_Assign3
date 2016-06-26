///////////////////////////////////////////////////////////////////////////////
// File Name : main.cpp														 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : This program search the shortest path, given by router.in.  
// Dijkstra algorithm will propose the shortest path. And per the command in 
// event.in, program will be activated. It has a total of three instructions 
// : request, eos(end of service), linkfail. See the detail introduction to  
// each of the commands File.cpp. Main has File object, and strat by read    
// function in File class													 
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "File.h"
#include <fstream>
using namespace std;
int main(){
	File myfile;//main has File object named myfile
	myfile.read();//main read two input file, and it will print the result
	return 0;
}