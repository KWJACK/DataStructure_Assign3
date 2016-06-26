///////////////////////////////////////////////////////////////////////////////
// File Name : Msg.h														 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : Please see the detailed description of samenamed headfile.	  
// here is for the space to describe how to act these funcs in class         
// Etc : Data Structure Assignment #2 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#include "Msg.h"
Msg::Msg()
{	/*
	Msg::Msg
	==================================================
	input : void
	otuput : void
	purpose : construct. initialize the component of Msg object
	*/
	blocking = false;// meand non blocking at frist(default)
	serviceID = 0;//service Id not allocated
	cost = 0;//cost is zero
	nextMsg = NULL;//pointer
}
Msg::~Msg()
{	/*
	Msg::~Msg
	==================================================
	input : void
	otuput : void
	purpose : exist conception
	*/
}
void Msg::setNextMsg(Msg* next)
{	/*
	Msg::setNextMsg
	==================================================
	input : Msg* next ---> Msg will be used Linked list, so connecting should be exist
	otuput : void
	purpose : connecting between each Msg
	*/ 
	nextMsg = next;
}
Msg* Msg::getNextMsg()
{	/*
	Msg::getNextMsg
	==================================================
	input : void
	otuput : Msg* ---> Provide the address of next Msg
	purpose : Provide the address of next Msg
	*/ 
	return nextMsg;
}
void Msg::setblocking()
{	/*
	Msg::setblocking
	==================================================
	input : void
	otuput : void
	purpose : Blocked Msg willn't be done from now on
	*/
	blocking = true;
}
bool Msg::getisBlock()
{	/*
	Msg::getisBlock
	==================================================
	input : void
	otuput : bool ---> true : blocked, false : not block, (default)
	purpose : Inform this Msg whether blocking or not
	*/
	return blocking;
}