///////////////////////////////////////////////////////////////////////////////
// File Name : MsgList.cpp													 
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
#include "MsgList.h"
MsgList::MsgList()
{	/*
	MsgList::MsgList
	==================================================
	input : void
	otuput : void
	purpose : construct. initialize the root of MsgList
	*/
	root_Msg = NULL;
}
MsgList::~MsgList()
{	/*
	MsgList::~MsgList
	==================================================
	input : void
	otuput : void
	purpose : destructor. Release the allocated memory for Msg space
	*/
	//Msg List had composed to linked list.
	//After moveing the current cursor, and then deletes the before cursor
	Msg* pCur = root_Msg;
	Msg* pBefore = NULL;
	while (pCur->getNextMsg()){//til reach the last Msg object
		pBefore = pCur;
		pCur = pCur->getNextMsg();
		delete pBefore;
	}
	delete pCur;//last msg delete
}
void MsgList::insertMsg(Msg* newMsg)
{	/*
	MsgList::insertMsg
	==================================================
	input : Msg* newMsg ---> created newMsg
	otuput : void
	purpose : Insert the newMsg to MsgList
	*/
	if (!root_Msg) root_Msg = newMsg;//in the beginning, setting root
	else{
		Msg* pCur = root_Msg;//til reach the last msg
		while (pCur->getNextMsg()){
			pCur = pCur->getNextMsg();
		}
		pCur->setNextMsg(newMsg);//connecting with newMsg
	}
}
Msg* MsgList::findMsg(int ID)
{	/*
	MsgList::findMsg
	==================================================
	input : int ID ---> Request's service ID
	otuput : Msg* ---> Address of the Msg have same ID
	purpose : found the Msg and then print the Msg what has same ID
	*/
	Msg* pCur = root_Msg;
	while (pCur){//til end of Msg
		if (pCur->serviceID == ID) return pCur;
		else pCur = pCur->getNextMsg();//moving next
	}
	return 0;//this means failure to search
}
int MsgList::findID(char* vertex1, char* vertex2)
{	/*
	MsgList::findID
	==================================================
	input : char* vertex1 ---> hint of request
			char* vertex2 ---> same with
	otuput : int ---> return request's service ID what found
	purpose : destructor. Release the allocated memory for Msg space
	*/
	string searchWord = vertex1;//making similar form
	searchWord += "\t";
	searchWord += vertex2;
	string reverseWord = vertex2;
	reverseWord += "\t";
	reverseWord += vertex1;

	Msg* pCur = root_Msg;
	while (pCur){//til end of Msg
		if (pCur->getisBlock() == false){//check among the msg what is not block yet
			string eventstring = pCur->eventMsg;
			if (eventstring.find(searchWord) != string::npos){//if same msg found,  
				break;//break, since found the msg
			}
			if (eventstring.find(reverseWord) != string::npos){
				break;
			}
			pCur = pCur->getNextMsg();//moving next msg
		}
		else{//moving next Msg
			pCur = pCur->getNextMsg();
		}
	}
	if (pCur ==NULL) return 0;//This means not to exist the Msg what wanted
	else{//in case, same msg found
		int ID = pCur->serviceID;//get serviceID
		pCur->setblocking();//This msg doesn't used no longer so blocking
		return ID;		
	}
}
int MsgList::findBlockMsg()
{	/*
	MsgList::findBlockMsg
	==================================================
	input : void
	otuput : int ---> 
	purpose : destructor. Release the allocated memory for Msg space
	*/
	Msg* pCur = root_Msg;
	Msg* pBefore = NULL;
	while (pCur){//til end of Msg
		if (pCur->getisBlock() == true){//if it found the first block msg 
			break;
		}
		else{//moving next msg
			pBefore = pCur;
			pCur = pCur->getNextMsg();
		}
	}
	if (pCur){//in case of found the msg
		if (pBefore == NULL){//this check to rootMsg is same with pCur
			root_Msg = pCur->getNextMsg();//convert next msg to root
		}
		else{//other case, setting next
			pBefore->setNextMsg(pCur->getNextMsg());
		}
		int value=pCur->serviceID;//get serviceID
		delete pCur;//delete msg <- this is fisrt blocked Msg 
		return value;
	}
	else{//If BlockMsg are no longer present
		return 0;
	}
}
void MsgList::deleteMsg(int ID)
{	/*
	MsgList::deleteMsg
	==================================================
	input : int ID ---> serviceID
	otuput : void
	purpose : delete the Msg in Msg list
	*/
	Msg* pCur = root_Msg;//get root of msg
	Msg* pBefore = NULL;
	while (pCur){//til end of Msg
		if (pCur->serviceID == ID){//found the same Msg has the serviceID
			if (pBefore == NULL){//checking root need to update
				root_Msg = pCur->getNextMsg();//update root
				delete pCur;//delete
				break;
			}
			else{//other case
				pBefore->setNextMsg(pCur->getNextMsg());//setting nextMsg for deletion
				delete pCur;
				break;
			}
		}//moving next Msg
		pBefore = pCur;
		pCur = pCur->getNextMsg();
	}	
}