///////////////////////////////////////////////////////////////////////////////
// File Name : Msg.h														 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : This class's role is that record about the msg written in   
// result.out. Those messages will be used to handling the event like eos or 
// linkfail. The Msg what matched with event command, will serve a soultion  
// of that event command.													 
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <iostream>
using namespace std;
class Msg//message
{
private:
	Msg* nextMsg;//Msg object can shift to next Msg
	bool blocking;//This blocking variable offer the information like that,
	//if this is true that mean the msg is not to find, so program would ues to ignore this.
	//So default vaule is false. Blocking should be done absolutely necessary.
public:
	Msg();
	~Msg();
	void setNextMsg(Msg* next);//setting address of Msg for next msg
	Msg* getNextMsg();//get address of Msg to shift next Msg
	string eventMsg;//Msg is composed of string variable.
	int serviceID;//This says what msg from event commmand
	int cost;//request's cost
	void setblocking();//this func can convert to block the msg
	bool getisBlock();//This func shows whether this msg is blocked or not
};

