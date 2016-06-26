///////////////////////////////////////////////////////////////////////////////
// File Name : request.cpp													 
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
#include "request.h"
#include <iostream>
request::request()
{	/*
	request::request
	==================================================
	input : void
	otuput : void
	purpose : 
	*/
	startpoint=0;//start point
	destipoint=0;//destination point
	bandwidth=0;
	serviceID=0;
	nextRequest = NULL;
	nextError = NULL;
}
request::~request()
{	/*
	request::~request
	==================================================
	input : void
	otuput : void
	purpose :
	*/
}
//all of setting functions will be used to create Vertex for adjacent maxtrix
void request::setStartpoint(char m_startpoint)
{	/*
	request::setStartpoint
	==================================================
	input : char m_startpoint ---> Notification about required settings
	otuput : void
	purpose : setting Vertex's startpoint
	*/
	startpoint = m_startpoint;
}
void request::setDestipoint(char m_destipoint)
{	/*
	request::setDestipoint
	==================================================
	input :char m_destipoint ---> Notification about required settings
	otuput : void
	purpose :setting Vertex's destination point
	*/
	destipoint = m_destipoint;
}
void request::setBandwidth(int m_bandwidth)
{	/*
	request::setBandwidth
	==================================================
	input : int m_bandwidth ---> Notification about required settings
	otuput : void
	purpose :setting Vertex's bandwidth
	*/
	bandwidth = m_bandwidth;
}
void request::setServiceID(int m_serviceID)
{	/*
	request::setServiceID
	==================================================
	input : int m_serviceID ---> Notification about required settings
	otuput : void
	purpose :setting Vertex's ID
	*/
	serviceID = m_serviceID;
}
void request::setNextReq(request* nextReq)
{	/*
	request::setNextReq
	==================================================
	input : request* nextReq ---> Notification about required settings
	otuput : void
	purpose :setting the address of next request
	*/
	nextRequest = nextReq;
}

void request::setNextErr(request* nextErr)
{	/*
	request::setNextErr
	==================================================
	input : request* nextErr ---> Notification about required settings
	otuput : void
	purpose :setting the address of next error request
	*/
	nextError = nextErr;
}
request* request::getNextErr()
{	/*
	request::getNextErr
	==================================================
	input : void
	otuput : request* ---> get address of next error request
	purpose :give a address  of next error request
	*/
	return nextError;
}
request* request::getNextReq()
{	/*
	request::getNextErr
	==================================================
	input : void
	otuput : request* ---> get address of next error request
	purpose :give a address  of next error request
	*/
	return nextRequest;
}
int request::getServiceID()
{	/*
	request::getServiceID
	==================================================
	input : void
	otuput : init ---> serviceID is composed to inteager
	purpose : give the request's service ID
	*/
	return serviceID;
}
char request::getStartpoint()
{	/*
	request::getNextErr
	==================================================
	input : void
	otuput : char ---> Vertex name is composed to capital letter
	purpose :Provides the startpoint's name of Vertex
	*/
	return startpoint;
}
char request::getDestipoint()
{	/*
	request::getNextErr
	==================================================
	input : void
	otuput : char ---> Vertex name is composed to capital letter
	purpose : Provides the destination point's name of Vertex
	*/
	return destipoint;
}
int request::getBandwidth()
{	/*
	request::getBandwidth
	==================================================
	input : void 
	otuput : int ---> bandwidth is composed to inteager
	purpose :Provide the bandwidth of request
	*/
	return bandwidth;
}
