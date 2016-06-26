///////////////////////////////////////////////////////////////////////////////
// File Name : requestList.h												 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : requestList class deal with request. In here, requests would
// be managed as various ues, for example created, deleted, set error etc..  
// File class has this class as form of object. So this class will act for   
// File class to search request what wanted from File class					 
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "request.h"
class requestList
{
private:
	request* rootList;//normal request
	request* errorList;//error request(error means to postpone)
public:
	requestList();
	~requestList();
	//create Request object for recording of list form
	void createRequest(char mstartpoint, char mdestipoint, int mbandwidth, int mserviceID);
	void setError(int ID);//this func set the service ID's request as postponed
	request* eosRequest(int ID);//return the first inputed error request. 
	request* getErrorList();//print root of Error
	void deleteRequest(request* target);//Delete the target of request. This func will be used in 'eos' event.
	void cancelError(request* target);//Cancle the target of error request, so this will be restored normal from error
};

