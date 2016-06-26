///////////////////////////////////////////////////////////////////////////////
// File Name : File.h														 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : File header is the space for the file class.			     
// in here, file class construct a adjacency matrixthe as form of list and	 
// write shortest path to result.out by reading event msg in event.in.txt	 							
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "dijkstra.h"
#include "requestList.h"
#include "MsgList.h"
using namespace std;
class File
{
private:
	ifstream inputfile;//for reading router.in.txt
	ifstream eventfile;//for reading event.in.txt
	ofstream resultfile;//for writing result.out.txt
	//File class has these class objects as standard
	dijkstra myDijkstra;//mydijkstra object could calculate the shorestpath 
	requestList reqList;//reqtList manges all request from event.in
	MsgList myMsgList;//msgList records about written the msg on result.out
public:
	File();//constructor
	~File();//destructor
	void read();////This function role is to make result file by reading router.in and event.in
};

