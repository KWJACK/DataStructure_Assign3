///////////////////////////////////////////////////////////////////////////////
// File Name : File.cpp														 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : Please see the detail description of same named headfile.	  
// here is for the space to describe how to act these funcs in class         
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <string>
#include <iostream>
#include "File.h"
#include "requestList.h"
#include "MsgList.h"
#include "Msg.h"
using namespace std;
File::File()
{	/*
	File::File
	==================================================
	input : void
	otuput : void
	purpose :
	*/
	inputfile.open("route.txt");
	eventfile.open("event.txt");
	//outputfile read the sentence and then, convert the code by each sentence
	resultfile.open("result.txt", ios::out);//this command mean that to write newly the file called 'encode.txt', 
	//even it had existed the old file smae with name of new file
	//In short, clear the outputfile before start to write new version of outputfile.
	resultfile.close();//and then close the file, this file would be written nothing
	resultfile.open("result.txt", ios::app);//open appendix mode
}
File::~File()
{	/*
	File::~File
	==================================================
	input : void
	otuput : void
	purpose : close the file
	*/
	eventfile.close();
	resultfile.close();
}
void File::read()
{	/*
	File::read
	==================================================
	input : void
	otuput : void
	purpose : make adjacent matrix and carry out according to the event file.
			 and then allocate about remaining deferred requests
	*/
	char str[256] = { 0 };//str array declared for save the line in inputfile temporary
	
	if (inputfile.is_open() == false){//checking route.in whether opon or not
		cout<<"Need to check the file name" << endl;//Inform failure the open
	}
	else
	while (!inputfile.eof()){//success to open the route.in
		inputfile.getline(str, 256, '\n');//get a sentence
		char *ptoken = NULL, *cNULL = NULL, *storechar[6] = { 0 };//Each storechar variable is filed tokenized command
		int i = 1;
		ptoken = strtok_s(str, "\t", &cNULL);
		storechar[0] = ptoken;
		do{//tokenize
			ptoken = strtok_s(NULL, "\t", &cNULL);
			storechar[i] = ptoken;
			i++; 
		} while (ptoken);//till ptoken is filled 'NULL'
		myDijkstra.createLength(storechar);		
	}
	inputfile.close();
	int Vertexnum = myDijkstra.getSumVertex();//total number of vertex
	myDijkstra.makeAdacency(Vertexnum);
	//eventfile read
	if (eventfile.is_open() == false){
		cout << "Need to check the file name" << endl;
	}
	else{
		while (!eventfile.eof()){
			eventfile.getline(str, 256, '\n');
			char *ptoken = NULL, *cNULL = NULL, *storechar[6] = { 0 };//Each storechar variable is filed tokenized command
			int i = 1;
			ptoken = strtok_s(str, "\t", &cNULL);//strtok((str, "\t") and add <string.h>
			storechar[0] = ptoken;
			do{//tokenize
				ptoken = strtok_s(NULL, "\t", &cNULL);
				storechar[i] = ptoken;
				i++;
			} while (ptoken);//till ptoken is filled 'NULL'
			/////////////////////////////////////////////////////////REQUST///////////////////////////////////////////////////////////////
			if (!strcmp(storechar[0], "request")){
				int ID = atoi(storechar[1]);
				reqList.createRequest(*storechar[2], *storechar[3], atoi(storechar[4]), ID);//requestList create
				if (myDijkstra.requesetAllocate(*storechar[2], *storechar[3], atoi(storechar[4])) == false){//in case of success to assign request
					resultfile << "allocated Requst " << ID << endl;//print success mesg
					resultfile << atoi(storechar[4]) << "\t"; 

					Msg* newMsg = new Msg;//save msg string for eos
					newMsg->serviceID = ID;
					newMsg->cost = *storechar[4];//cost msg save
					char temp = myDijkstra.pop_Vertex();
					while(temp != 0){						
						resultfile << temp << "\t";//print path
						newMsg->eventMsg = newMsg->eventMsg + "\t" + temp;
						temp = myDijkstra.pop_Vertex();
					}
					myMsgList.insertMsg(newMsg);//new msg inser to list
					resultfile << endl << endl;
					myDijkstra.clearBandwidth();
				}
				else{//in case of fail to assign request--->save errorlist 
					reqList.setError(ID);
					resultfile <<"deferred Reqest" << ID << endl<<endl;
					char temp = 0;
					do{	
						temp = myDijkstra.pop_Vertex();
					} while (temp != 0);
					myDijkstra.rebackBandwidth();
				}
			}
			/////////////////////////////////////////////////////////EOS///////////////////////////////////////////////////////////////
			else if (!strcmp(storechar[0], "eos")){//in case of eos. That ID will be not using anymore so need to delete since suspension list could pass this ID
				int ID = atoi(storechar[1]);//get id
				//find target request have the id
				request* deleteRequest = reqList.eosRequest(ID);//function:eosRequest return zero if the ID doesn't exist
				if (deleteRequest != NULL){//in case of find target, return bandwidth on the path					
					myDijkstra.returnBandwidth(deleteRequest->getStartpoint(), deleteRequest->getDestipoint(), deleteRequest->getBandwidth());					
					Msg* pCur = myMsgList.findMsg(ID);
					resultfile << "End of service " << ID <<endl;
					resultfile << deleteRequest->getBandwidth()<< pCur->eventMsg << endl << endl;
				}
				else{//in case of not found, print error mseg
					resultfile << "That ID : " << ID << " couldn't find among request list so far" << endl <<endl;
				}
				//all request of suspension try to re-request depending on request number
				request* search = reqList.getErrorList();
				while (search){//about all postponed request
					request* tempSearch = NULL;
					if (myDijkstra.requesetAllocate(search->getStartpoint(), search->getDestipoint(), search->getBandwidth()) == false){//if success to assign request
						resultfile << "allocated Requst " << search->getServiceID() << endl;
						resultfile << search->getBandwidth() << "\t";
						//in here return orgin state blocked request
						if (search->getNextErr()){
							tempSearch = search->getNextErr();
						}
						reqList.cancelError(search);
						Msg* newMsg = new Msg;//for eos, save msg string
						newMsg->serviceID = search->getServiceID();
						newMsg->cost = search->getBandwidth();						
						char temp = myDijkstra.pop_Vertex();
						while (temp != 0){							
							resultfile << temp << "\t";//print path
							newMsg->eventMsg = newMsg->eventMsg + "\t" + temp;
							temp = myDijkstra.pop_Vertex();
						}
						myMsgList.insertMsg(newMsg);//save this mesg newly
						resultfile << endl<<endl;
						myDijkstra.clearBandwidth();
					}
					else{//in case of fail to assign request
						resultfile << "deferred Request" << search->getServiceID() << endl<<endl;//print error mseg
						char temp = 0;
						do{
							temp = myDijkstra.pop_Vertex();
						} while (temp != 0);
						myDijkstra.rebackBandwidth();//return bandwidth
					}
					if (tempSearch != NULL){
						search = tempSearch;
						tempSearch = NULL;
					}
					else{
						search = search->getNextErr();
					}
				}//while (search)
				//delete request in eos list
				myMsgList.deleteMsg(deleteRequest->getServiceID());
				reqList.deleteRequest(deleteRequest);
			}
			/////////////////////////////////////////////////////////LINKFAIL///////////////////////////////////////////////////////////////
			else if (!strcmp(storechar[0], "linkfail")){
				resultfile << "Link failure " << *storechar[1] << " " << *storechar[2] << endl<<endl;			
				//Linkfail is set that one path had deleted then assigned request changed state of suspension
				//suspended requests in list should implement after all request in eventin done
				//travaling MsgList, find the linkfail path
				int serviceID=myMsgList.findID(storechar[1], storechar[2]);
				while (serviceID != 0){
					request* deleteRequest = reqList.eosRequest(serviceID);//function:eosRequest return zero if the ID doesn't exist
					if (deleteRequest != NULL){//in case of founding target
						//return bandwidth
						myDijkstra.returnBandwidth(deleteRequest->getStartpoint(), deleteRequest->getDestipoint(), deleteRequest->getBandwidth());						
						resultfile << "using fail link path : " << serviceID << endl;
					}
					else{//in case of fail to foound target. then print error mseg
						resultfile << "That ID : " << serviceID << "what is written in eos event doesn't exsist until now " << endl <<endl;
					}
					serviceID = myMsgList.findID(storechar[1], storechar[2]);
				}//while (serviceID != 0)				

				myDijkstra.linkfail(*storechar[1], *storechar[2]);
				//Try to re-assign about rebacked request
				//so need to use the msg for found target ID----->if success re-try to dijstra
				int FindserviceID = myMsgList.findBlockMsg();
				if (FindserviceID != 0){
					while (FindserviceID != 0){
						request* Re_request = reqList.eosRequest(FindserviceID);
						if (myDijkstra.requesetAllocate(Re_request->getStartpoint(), Re_request->getDestipoint(), Re_request->getBandwidth()) == false){
							resultfile << "allocated Requst " << FindserviceID << endl;
							resultfile << Re_request->getBandwidth() << "\t";//cost
							reqList.cancelError(Re_request);
							Msg* newMsg = new Msg;
							newMsg->serviceID = FindserviceID;
							newMsg->cost = Re_request->getBandwidth();
							char temp = myDijkstra.pop_Vertex();
							while (temp != 0){								
								resultfile << temp << "\t";//print path
								newMsg->eventMsg = newMsg->eventMsg + "\t" + temp;
								temp = myDijkstra.pop_Vertex();
							}
							myMsgList.insertMsg(newMsg);//just printed mseg save to Msg list
							resultfile << endl;
							myDijkstra.clearBandwidth();
						}
						else{////in case of fail to assign request--->saved in error list
							char temp = myDijkstra.pop_Vertex();
							while (temp != 0){
								temp=myDijkstra.pop_Vertex();
							}
							reqList.setError(FindserviceID);
							resultfile << "deferred Reqest" << FindserviceID<<endl<<endl;
							myDijkstra.rebackBandwidth();
						}
						FindserviceID = myMsgList.findBlockMsg();//check confirmed Msg
					}//while(FindserviceID != 0)
				}//if (FindserviceID != 0)
			}//else if (!strcmp(storechar[0], "linkfail"))
		}//while(event)
	}//else (eventfile.is_open() == true)

	resultfile << "///////////////////////end of file(event.in)/////////////////////////" << endl;
	/////in here implement about suspended msegs
	request* errorRequest = reqList.getErrorList();
	while (errorRequest){		
		bool reDijkstra = myDijkstra.changecost(errorRequest->getStartpoint(), errorRequest->getDestipoint(), errorRequest->getBandwidth());
		if (reDijkstra==true)//in case of no more leftover bandwidth--->so dijkstra will be assign the best alternative path
		{
			myDijkstra.requesetAllocate(errorRequest->getStartpoint(), errorRequest->getDestipoint(), errorRequest->getBandwidth());//try to found best alternative path
			if (myDijkstra.checkDeleteReq(errorRequest->getStartpoint(), errorRequest->getDestipoint())==false){
				resultfile << "allocated Requst " << errorRequest->getServiceID() << endl;
				resultfile << errorRequest->getBandwidth() << "\t";
				char temp = myDijkstra.pop_Vertex();

				while (temp != 0){					
					resultfile << temp << "\t";//print path
					temp = myDijkstra.pop_Vertex();
				}
				resultfile << endl << endl;
				myDijkstra.rebackMAX();
				myDijkstra.clearBandwidth();
			}
			else{//if dijkstra could found any more path, print error mseg to inform fail to assign path
				resultfile << "deferred Request " << errorRequest->getServiceID()<< endl << endl;
				resultfile << "delete Request " << errorRequest->getServiceID() << endl;
				myDijkstra.rebackBandwidth();
			}
		}
		else{//in case of possible to assign, print the path what just assigned request
			myDijkstra.clearBandwidth();
			resultfile << "allocated Requst " << errorRequest->getServiceID() << endl;
			resultfile << errorRequest->getBandwidth() << "\t";
			char temp = myDijkstra.pop_Vertex();
			reqList.cancelError(errorRequest);
			while (temp != 0){//print path				
				resultfile << temp << "\t";				
				temp = myDijkstra.pop_Vertex();
			}
			resultfile << endl << endl;
		}
		errorRequest = errorRequest->getNextErr();
	}
}//read-function end