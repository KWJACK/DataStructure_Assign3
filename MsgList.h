///////////////////////////////////////////////////////////////////////////////
// File Name : MsgList.h													 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : MsgList manges all of msg in this progam. in here, MsgList  
// class offers to File class that insert, find, delete about msg what wanted  
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Msg.h"
class MsgList
{
private:
	Msg* root_Msg;//root offer where the entrance is located
public:
	MsgList();
	~MsgList();
	Msg* findMsg(int ID);//find msg by using serviceID of request
	void insertMsg(Msg* newMsg);//insert the msg to msgList
	int findID(char* vertex1, char* vertex2);//using both start and destination points, return service ID
	int findBlockMsg();//print the first block msg
	void deleteMsg(int ID);//Delete msg what has same serviceID with paramether
};