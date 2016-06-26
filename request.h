///////////////////////////////////////////////////////////////////////////////
// File Name : request.h													 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : request class manage all of requsts in this program. In here
// program record an one request entirely. Each request object will be uesd  
// in requestList.															 
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
class request
{
private:
	char startpoint;//start point
	char destipoint;//destination point
	int bandwidth;
	int serviceID;
	//request has two ways. Each ways offer movable to other request
	request* nextRequest;//nextRequest is normal way
	request* nextError;//Error is special way, this skip normal way to reach error way
public:
	request();
	~request();
	//set
	void setStartpoint(char m_startpoint);
	void setDestipoint(char m_destipoint);
	void setBandwidth(int m_bandwidth);
	void setServiceID(int m_serviceID);
	void setNextReq(request* nextReq);
	void setNextErr(request* nextErr);
	//get
	char getStartpoint();
	char getDestipoint();
	request* getNextErr();
	request* getNextReq();
	int getServiceID();
	int getBandwidth();
};