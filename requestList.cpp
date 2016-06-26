///////////////////////////////////////////////////////////////////////////////
// File Name : requestList.cpp												 
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
#include "requestList.h"
#include <iostream>
requestList::requestList()
{	/*
	requestList::requestList
	==================================================
	input : void
	otuput : void
	purpose : initialization of both root of normal and error
	*/
	rootList=NULL;
	errorList = NULL;
}
requestList::~requestList()
{	/*
	requestList::~requestList
	==================================================
	input : void
	otuput : void
	purpose : destruct all requests
	*/
	request* pCur = rootList;
	request* pBefore = NULL;
	//Request List had composed to linked list.
	//After moveing the current cursor, and then deletes the before cursor
	while (pCur->getNextReq()){
		pBefore = pCur;
		pCur = pCur->getNextReq();
		delete pBefore;
	}
	delete pCur;//last request delete
}
request* requestList::getErrorList()
{	/*
	requestList::getErrorList
	==================================================
	input : void
	otuput : request*   
	purpose : return the address of root,errorList
	*/
	return errorList;//root of error request
}
void requestList::createRequest(char mstartpoint, char mdestipoint, int mbandwidth, int mserviceID)
{	/*
	requestList::createRequest
	==================================================
	input : char mstartpoint--->This tell Vertex's starting point 
			char mdestipoint--->This tell Vertex's destination point
			int mbandwidth--->value of request's demanding bandwidth
			int mserviceID--->request's ID
	otuput : void
	purpose : create request for recording. This request will be used when programm make the error(postpone) from nomal request 
	*/
	request* newrequest = new request;//allocate memory for request
	newrequest->setBandwidth(mbandwidth);//setting request by using parameter
	newrequest->setDestipoint(mdestipoint);
	newrequest->setStartpoint(mstartpoint);
	newrequest->setServiceID(mserviceID);
	if (!rootList){//First time to make, root doesn't exist
		rootList = newrequest;
	}
	else{//else of root,		
		request* pCur=rootList;
		while (pCur->getNextReq())//till reach to last request
		{
			pCur = pCur->getNextReq();
		}
		pCur->setNextReq(newrequest);//last request gain a successor, newrequest
	}
}
void requestList::setError(int ID)
{	/*
	requestList::setError
	==================================================
	input : int ID--->It tells what to change the request. 
	otuput : void
	purpose : convert normal request to error(postpone)
	*/
	request* pCur = rootList;//get root of request
	while (pCur->getServiceID() != ID && pCur != NULL){//til end of list, find the request what had same serviceID with parameter
		pCur = pCur->getNextReq();
	}

	if (pCur != NULL){//Meaning of suitable request's detection
		if (!errorList) errorList = pCur;//First time to make the root of error
		else{//if root of error is exist,
			request* pCur2 = errorList;//shifting till reach to last error request
			while (pCur2->getNextErr()){
				pCur2 = pCur2->getNextErr();
			}
			pCur2->setNextErr(pCur);//last error request gain a successor, pCur
		}
	}
}
request* requestList::eosRequest(int ID)
{	/*
	requestList::eosRequest
	==================================================
	input : int ID --->It tells what request is target
	otuput : request* --->return address of error request what had same ID with parameter
	purpose : inform the request what commended end of service. But if it couldn't find to suitable request, return 0 
	*/
	request* pCur = rootList;//get root of request
	while (pCur){//search til end of list,
		if (pCur->getServiceID() == ID)//if it find the suitable request,
		{
			request* checkError = errorList;//checking this is error.
			//if pCur is same with checkError, return 0. Meaning this already set Error,
			//so could use this request, therefore return 0;
			if (!errorList)	return pCur;//However if root of error doesn't exist, no need to check whether this is same with error or not
			else{
				while (checkError){//process of checking whether this is same with error or not
					if (checkError == pCur) return 0;
					else{
						checkError = checkError->getNextErr();
					}
				}
				return pCur;//after checking had done, return pCur. Programm will treat this request over.
			}
		}
		pCur = pCur->getNextReq();//move next request to found
	}
	return 0;//doesn't exist the request what had same ID
}
void requestList::deleteRequest(request* target)
{	/*
	requestList::deleteRequest
	==================================================
	input : request* target ---> what delete
	otuput : void
	purpose : delete target request among list
	*/
	request* pCur = rootList;
	request* pBefore = NULL;
	while (pCur){
		if (pCur == target){//check whether this is target or not
			if (pCur == rootList){//if target is root, programm should reset the root of request.
				if (pCur->getNextReq() != NULL){//Next request exist, behind root
					rootList = pCur->getNextReq();//setting root is next request
					delete pCur;//delete
				}
				else{//in case of only root exist,
					delete pCur;
					rootList = NULL;//initialize to root
				}
			}
			else{//If target isn't root, doesn't need to reset root. So just delete the target
				//but programm should link interjacented. 
				pBefore->setNextReq(pCur->getNextReq());
				delete pCur;
			}			
			break;//It has completed the object, escape
		}
		//pBefore shodow pCur
		pBefore = pCur;
		//pCur move next request
		pCur = pCur->getNextReq();
	}//while pCur
}
void requestList::cancelError(request* target)
{	/*
	requestList::cancelError
	==================================================
	input :request* target ---> what cancel
	otuput : void
	purpose : cancel the error, this function allow target request is granted
	*/	
	request* pCur = errorList;//get errorList
	request* pBefore = NULL;//pBefore shadow pCur, first time pBefore is NULL
	if (pCur == target){//in case, root of error is same with target, initialize root of error 
		errorList = pCur->getNextErr();
		pCur->setNextErr(NULL);//and this request is not a error request.
	}
	else{//other case, will be done below
		pBefore = pCur;//move to next error request
		pCur = pCur->getNextErr();
		while (pCur){//till end of error request,
			if (pCur == target){//check that this is smae wiht the target
				//if find the target, cancel the state of error to normal
				pBefore->setNextErr(pCur->getNextErr());
				pCur->setNextErr(NULL);
			}
			pBefore = pCur;//moving the next
			pCur = pCur->getNextErr();
		}
	}
}