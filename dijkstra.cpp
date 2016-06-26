///////////////////////////////////////////////////////////////////////////////
// File Name : dijkstra.cpp													 
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
#include "dijkstra.h"
#include "Edge.h"
#include "Vertex.h"
#include <stdlib.h>
dijkstra::dijkstra()
{	/*
	dijkstra::dijkstra
	==================================================
	input : void
	otuput : void
	purpose : constructor, initialization all component
	*/
	root=NULL;
	root_stack = NULL;
	root_Edge = NULL;
	root_Band = NULL;
	sumVertex = 0;//The number of Vertex is zero first time
}
dijkstra::~dijkstra()
{	/*
	dijkstra::~dijkstra
	==================================================
	input : void
	otuput : void
	purpose : destructor. Release the allocated memory like path, dist, s, and adjacent matrix 
	*/
	//release space for array of dist, s, path
	delete dist;
	delete s;
	delete path;
	//Release the adjacent matrix
	Vertex* pCur = root;
	Vertex* pBefore = NULL;
	while (pCur->V_next){//circuit all vertex
		//Adjcant matix is composed to Linked list, so for to release the memory,
		//need to Before about current Cursor. Deletion will be acted only 'Before' object except the last time
		Edge* pEdge = pCur->VE_next;
		Edge* BeforeEdge = NULL;
		if (pEdge){
			while (pEdge->EE_next){//til readch the end of Edge each one Vertex
				BeforeEdge = pEdge;//shdowing the current edge
				if (pEdge->EE_next){//if next edge exist,,
					pEdge = pEdge->EE_next;//moving the next
				}
				else{//other just delete, not to move.
					delete BeforeEdge;
					break;//escape for next vertex to fast
				}
				delete BeforeEdge;//in case of moving next, delete before edge
			}
			delete pEdge;//if only one edge exist in Vertex, ignore the while statement. Directly delete
		}
		pBefore = pCur;//shadowing the current vertex
		if (pCur->V_next){//same manner with deletion of edge
			pCur = pCur->V_next;
			delete pBefore;
		}
		else{
			delete pBefore;
			delete pCur;
			break;
		}
	}

}
int dijkstra::getSumVertex()
{	/*
	dijkstra::getSumVertex
	==================================================
	input : void
	otuput : int
	purpose : provide a total number of Vertex
	*/
	return sumVertex;
}
void dijkstra::makeAdacency(int n)
{	/*
	dijkstra::makeAdacency
	==================================================
	input : int n ---> a total number of Vertex
	otuput : void
	purpose : ready to dijkstra before excute
	*/
	//allocate the memory space.
	dist = new int[n];
	s = new bool[n];
	path = new int[n];
	//and those need to initialize all.
	for (int i = 0; i < n; i++){
		dist[i] = MAXINT;//MAXINT is infinite value. dist==distance of smallest path
		s[i] = false;//default value. This means that this is not checking yet
		path[i] = 0;
	}
}
int dijkstra::choose()
{	/*
	dijkstra::choose
	==================================================
	input : void
	otuput : int ---> index of Vertex
	purpose : Provide the index of vertex what has most min value of dist 
	*/
	int cst_Min = MAXINT;//initial smallest value is inifite value.
	int index_MIn = 0;//index of vertex what had min value
	for (int i = 0; i < sumVertex; i++)//about all of vertex
	{
		if (cst_Min > dist[i] && s[i] == false)
		//If current vertex is more than lowest value, it would be updated Min value among not including to s yet
		{
			cst_Min = dist[i];//current min value
			index_MIn = i;//index of min vertex
		}
	}
	return index_MIn;//return most smallest value
}
Edge* dijkstra::find(int v1, int v2)
{	/*
	dijkstra::find
	==================================================
	input : int v1 ---> startpoint of index vertex
			int v2 ---> destination point of index vertex
	otuput : Edge
	purpose : return the Edge between v1 and v2, if it doesn't exist, return 0.
	*/
	char nameVertex1 = indextoChar(v1);//convert the capital letter 
	char nameVertex2 = indextoChar(v2);
	Vertex* dTemp = root;
	while (dTemp)//searching all of vertex
	{//first find the start point, and then set the destination point
		if (dTemp->m_name == nameVertex1)
		{
			Edge* rTemp = dTemp->VE_next;//VE_next is Edge between Vertex to Edge
			while (rTemp)//til reaching the end of edge
			{
				if (rTemp->pto == nameVertex2)//if it found the Edge what wanted
					return rTemp;//return rTemp
				else
					rTemp = rTemp->EE_next;//next Edge
			}
			return 0;//case of not found
		}
		else
		{
			dTemp = dTemp->V_next;//next Vertex
		}
	}
	return 0;//case of not found
}
void dijkstra::returnBandwidth(char v, char d, int band)
{	/*
	dijkstra::returnBandwidth
	==================================================
	input : char v ---> start vertex
			char d ---> destination vertex
			int band ---> bandwidth
	otuput : void
	purpose : return the requested cost for adjacent matrix
	*/
	shortestPath(v,d,band);
	int d_index = indexNum(d);//indexNumf func return the Vertex's index as form of inteager 	
	int p = path[d_index];
	char pto = indextoChar(p);
	char pfrom = d;	
	Edge* pEdge = NULL;
	//follow the shortest path, using path made as manner of reverse path
	do{
		Vertex* pVertex = root;//get root of adjacent matrix
		while (pVertex != NULL){//til end of vertex
			pEdge = pVertex->VE_next;//VE_next is link to connect between vertex with edge
			while (pEdge != NULL){//til end of edge
				if (pEdge->pfrom == pfrom && pEdge->pto == pto){//in case of matching that request's partial path				
					pEdge->bandwidth = pEdge->bandwidth + band;//return request's cost
					break;//escape loop, since programm satisfied the purose that return cost value.
				}
				else if (pEdge->pfrom == pto && pEdge->pto == pfrom){//this statement should be written because edge had composed to interactivity					
					pEdge->bandwidth = pEdge->bandwidth + band;//likewise, return request's cost
					break;//escape loop, since programm satisfied the purose that return cost value.					
				}
				else{//for moving that current edge to next edge
					pEdge = pEdge->EE_next;
				}
			}//while(pEdge != NULL)
			pVertex = pVertex->V_next;//for moving that current vertex to next vertex
		}
		pfrom = pto;//shifting next partial path in origal path 
		int temp = indexNum(pto);//		
		pto = indextoChar(path[temp]);
	} while (pfrom != v);//til pfrom reach the startpoint
}

void dijkstra::shortestPath(char v, char d, int band)
{	/*
	dijkstra:shortestPath
	==================================================
	input : char v ---> start vertex
			char d ---> destination vertex
			int band ---> bandwidth
	otuput : void
	purpose : find the shortest paht as manner of dijkstra algorithm
	*/
	int v_index = indexNum(v);//indexNum func's role is to return index of the vertex
	Edge* pEdge = NULL;//Initialization. All component of dijstkra
	for (int i = 0; i < sumVertex; i++){
		pEdge = find(v_index, i);//find the connected edge between two vertex
		path[i] = v_index;
		s[i] = false;//initial setting, false : that mean vertex is not to check yet
		dist[i] = MAXINT;//if vertex's adjacent edge exist, distance array will be written that's cost. 
		if (pEdge) dist[i] = pEdge->cost;
	}
	s[v_index] = true;//The path of itself no need to check 
	dist[v_index] = 0;//therefor, distance is zero
	for (int i = 0; i < (sumVertex - 2); i++){
		int u = choose();//choose func's role is that ruturn most min value of dist
		s[u] = true;//convert to check
		for (int w = 0; w < sumVertex; w++){
			if (s[w] == false){//find vertex among the vertex what yet not including 'S'
				if (find(u, w) != NULL){//find return the connected edge between two vertex(u,w) 
					int utow = find(u, w)->cost;//utow variable means that the way between u and w. 
					if (utow != MAXINT && dist[u] + utow < dist[w]){//cost is not MAXINT, and new path is more short than ever path 
						dist[w] = dist[u] + utow;//save the more short path
						path[w] = u;//save the reverse path for tracing after used
					}
				}//if (find(u, w) != NULL)
			}//if (s[w] == false)
		}//for
	}
}
bool dijkstra::requesetAllocate(char v, char d, int band)//v=startpoint, d=destination potin, char bandwith
{	/*
	dijkstra::requesetAllocate
	==================================================
	input : char v ---> start vertex
			char d ---> destination vertex
			int band ---> bandwidth
	otuput : bool ---> true : Occur the error that means failure to allocate the request
					   false : Success to allocate the request
	purpose : Allocate the reqest and inform the result whether success or not
	*/
	shortestPath(v, d, band);//find shortest path, by using dijsktra algorithm.
	int d_index = indexNum(d);
	bool error = false;//error checking. true : not to success to allocate, and other is contrary 
	bool fail = false;
	int p = path[d_index];//tracing the resever path
	char pto = indextoChar(p);
	char pfrom = d;
	push_Vertex(pfrom);//using the data structure of stack for writing Msg what recorded shortest path
	Edge* pEdge = NULL;
	//tracing reverse path of shortest
	do{
		Vertex* pVertex = root;
		while (pVertex != NULL&& error == false){//til end of vertex and not error
			//,since error will be checked not to need the allocatation no longer
			pEdge = pVertex->VE_next;
			while (pEdge != NULL&& error == false){
				if (pEdge->pfrom == pfrom && pEdge->pto == pto){//found the edge what linked both pfrom and pto
					if (pEdge->bandwidth - band >= 0){//check whether is possible to subtract 
						pEdge->bandwidth = pEdge->bandwidth - band;
						memorizeBandwidth(pEdge, band);
					}
					else{
						error = true;
					}
					break;
				}
				else if (pEdge->pfrom == pto && pEdge->pto == pfrom){
					if (pEdge->bandwidth - band >= 0){
						pEdge->bandwidth = pEdge->bandwidth - band;//subtract
						memorizeBandwidth(pEdge, band);
					}
					else{
						error = true;
					}
					break;
				}
				else{//in case of not found the edge, moving next edge
					pEdge = pEdge->EE_next;
				}
			}//while(pEdge != NULL && error==false)
			pVertex = pVertex->V_next;//moving next vertex
		}
		if (error == true) break;
		pfrom = pto;//for tracing the reverse path
		push_Vertex(pfrom);//pushed to stack partial vertex in whole path 
		int temp = indexNum(pto);
		pto = indextoChar(path[temp]);//convert the capital letter from index of vertex		
	} while (pfrom != v);//til reach the start point

	if (error == true) return true;//failure the allocation
	else return false;//success to allocate

}
bool dijkstra::changecost(char v, char d, int band)
{	/*
	dijkstra::changecost
	==================================================
	input : char v ---> start point
			char d ---> destination point
			int band ---> request's cost
	otuput : bool ---> Inform whether it is possible to allocate or not. true means impossible.
	purpose : about the bandwidth what is shortage, change the cost as infinity value
	*/
	shortestPath(v, d, band);//running dijkstra algorithm
	int d_index = indexNum(d);//covert to index of destination point
	bool error = false;//if error is true, means impossible to allocate about demanded request
	int p = path[d_index];//for tracing the reverse path
	char pto = indextoChar(p);//convert to capital letter from index
	char pfrom = d;
	Edge* pEdge = NULL;
	do{
		Vertex* pVertex = root;
		while (pVertex != NULL){//til end of vertex in adjacent maxtrix
			pEdge = pVertex->VE_next;//getting the Vertex's Edge by using VE_next
			while (pEdge != NULL){//til end of edge about each Vertex
				if (pEdge->pfrom == pfrom && pEdge->pto == pto){//find the edge what has same names for tracing reverse path
					if (pEdge->bandwidth - band >= 0){//pass the case of enough bandwidth
					}
					else{//however, not enough, convert to infinity value
						error = true;//inform that it has changed at least once
						pEdge->previousCost = pEdge->cost;//save original cost to the previousCost for return the value
						pEdge->cost = MAXINT;//MAXINT is infinity value
						push_edge(pEdge);//push the edge for using later when return the value
					}
					break;//Since there is no longer need to search
				}
				else if (pEdge->pfrom == pto && pEdge->pto == pfrom){//same with up, but change the vertex each other
					if (pEdge->bandwidth - band >= 0){//pass the case of enough bandwidth
					}
					else{
						error = true;//inform that it has changed at least once
						pEdge->previousCost = pEdge->cost;
						pEdge->cost = MAXINT;
						push_edge(pEdge);//push the edge for using later when return the value
					}
					break;//Since there is no longer need to search
				}
				else{//moving next edge
					pEdge = pEdge->EE_next;
				}
			}//while(pEdge != NULL && error==false)
			pVertex = pVertex->V_next;//moving next vertex
		}		
		pfrom = pto;//moving next reverse path
		int temp = indexNum(pto);
		pto = indextoChar(path[temp]);
	} while (pfrom != v);//til reach the start point
	if (error == true) return true;
	else return false;//default
}

void dijkstra::createLength(char *arr[])
{	/*
	dijkstra::createLength
	==================================================
	input : char arr[]---> this array have all information relating with request
	otuput : void
	purpose : make the adjacent matrix as list form
	*/
	Edge *edge1, *edge2;
	//Both points are due to have an edge in both directions of two way point
	edge1 = createEdge(*arr[0], *arr[1], atoi(arr[2]), atoi(arr[3]));//start point, desti point, bandwidth, cost
	edge2 = createEdge(*arr[1], *arr[0], atoi(arr[2]), atoi(arr[3]));//desti point, start point, bandwidth, cost
	
	Vertex* pCur=root;	
	if (!pCur){//in the biginning of read the route.in
		//make new Vertex and setting root for adjacent matrix
		Vertex *newVertex = new Vertex;
		root = newVertex;
		newVertex->m_name = *arr[0];
		newVertex->VE_next = edge1;
		//til second vertex, create the space without any conditions
		Vertex *nextVertex = new Vertex;
		nextVertex->m_name = *arr[1];
		nextVertex->VE_next = edge2;
		newVertex->V_next = nextVertex;
		sumVertex += 2;//In the beginning, there are none of the vertices so adding that both
		
	}
	else{//after beginning
		Vertex* find1 = listSearch(*arr[0]);//listSearch func inform the vertex if it will be matched
		Vertex* find2 = listSearch(*arr[1]);
		if (find1 == NULL){//created new
			while (pCur->V_next){//for connecting the last vertex
				pCur = pCur->V_next;//shift
			}
			Vertex* newVertex = new Vertex;
			pCur->V_next = newVertex;
			newVertex->m_name = *arr[0];
			newVertex->VE_next = edge1;
			sumVertex += 1;//add the number of vertex to sum
		}
		else{//Already exists, no need to create new vertex just connecting with edge
			Edge* pEdge = find1->VE_next;
			while (pEdge->EE_next){
				pEdge = pEdge->EE_next;
			}
			pEdge->EE_next = edge1;//connecting
		}
		if (find2 == NULL){//same with find1 so pass the explaination
			pCur = root;
			while (pCur->V_next){
				pCur = pCur->V_next;
			}
			Vertex* newVertex = new Vertex;
			pCur->V_next = newVertex;
			newVertex->m_name = *arr[1];
			newVertex->VE_next = edge2;
			sumVertex += 1;
		}
		else{
			Edge* pEdge = find2->VE_next;
			while (pEdge->EE_next){
				pEdge = pEdge->EE_next;
			}
			pEdge->EE_next = edge2;
		}
	}		
}

Edge* dijkstra::createEdge(char from, char to, int bandwidth, int cost)
{	/*
	dijkstra::createEdge
	==================================================
	input : char from ---> element of edge in from
			char to ---> element of edge in to
			int bandwidth ---> element of edge in bandwidth
			int cost ---> element of edge in cost
	otuput : Edge* ---> return the address of new created Edge
	purpose :
	*/
	Edge* newEdge = new Edge;//allocated the space for edge
	newEdge->pfrom = from;//setting about all element in edge
	newEdge->pto = to;
	newEdge->cost = cost;
	newEdge->bandwidth = bandwidth;
	return newEdge;
}
Vertex* dijkstra::listSearch(char target)
{	/*
	dijkstra::listSearch
	==================================================
	input : char target ---> target vertex
	otuput : Vertex* ---> for return the address of vertex
	purpose : search the name of the corresponding vertex
	*/
	Vertex* pCur = root;
	while (pCur){//til end of vertex
		if (pCur->m_name == target)
			return pCur;//if it found, retrun the addres of vertex
		else pCur = pCur->V_next;
	}
	return NULL;//this means not to found
}
int dijkstra::indexNum(char name)
{	/*
	dijkstra::indexNum
	==================================================
	input : char name ---> name of vertex
	otuput : int ---> index of vertex
	purpose : convert the index from the vertex
	*/
	int count = 0;//count is index
	Vertex* pCur = root;
	while (pCur){
		if (pCur->m_name == name) return count;//founed the corresponding vertex
		else{
			pCur = pCur->V_next;
			count++;//for next index, added
		}
	}
}
char dijkstra::indextoChar(int index)
{	/*
	dijkstra::indextoChar
	==================================================
	input : int index ---> index of vertex
	otuput : char ---> name of vertex
	purpose : convert the name from the index
	*/
	Vertex* pCur = root;
	for (int i = 0; i < index; i++)//counting index
		pCur = pCur->V_next;
	return pCur->m_name;//inform vertex's name with corresponding index
}
void dijkstra::push_Vertex(char v)
{	/*
	dijkstra::push_Vertex
	==================================================
	input : char v ---> vertex name
	otuput : void
	purpose : push vertex. It will be used to print the path
	*/
	Vertex* newStack = new Vertex;
	newStack->m_name = v;
	if (!root_stack)root_stack=newStack;
	else{//push the stack
		newStack->V_next = root_stack;
		root_stack = newStack;
	}
}
char dijkstra::pop_Vertex()
{	/*
	dijkstra::pop_Vertex
	==================================================
	input : void
	otuput : char ---> Vertex name
	purpose : write the vertex to result file as using pushed vertex
	*/
	Vertex* pCur = root_stack;
	if (root_stack != NULL){//pop in the stack
		root_stack = pCur->V_next;
		char value = pCur->m_name;
		delete pCur;//delete the element
		return value;//for writing the name of vertex
	}
	else return 0;//no longer the vertex exist, return 0
}
void dijkstra::push_edge(Edge* pushEdge)
{	/*
	dijkstra::push_edge
	==================================================
	input : Edge* pushEdge ---> push this edge
	otuput : void
	purpose : memorize the edge for restore the original 
			 after end of coverting inifinity value
	*/
	if (!root_Edge) root_Edge = pushEdge;
	else{//push the edge, but not to need the allocation for space
		Edge* pCur = root_Edge;
		while (pCur->nextMAX){//using nextMax path. not to use the EE_Next
			pCur = pCur->nextMAX;
		}
		pCur->nextMAX = pushEdge;
	}
}
void dijkstra::memorizeBandwidth(Edge* pushEdge, int bandwidth)
{	/*
	dijkstra::memorizeBandwidth
	==================================================
	input : Edge* pushEdge ---> push this Edge
			int bandwidth ---> memory amount of bandwidth
	otuput : void
	purpose : memorize the edge of bandwidth for restore the original
			 after end of allocation the request
	*/
	Edge* saveEdge = pushEdge;//push the edge
	saveEdge->previousBand = bandwidth;//memorize the bandwidth to previousBand

	if (!root_Band) root_Band = pushEdge;
	else{//push the edge, but not to need the allocation for space
		Edge* pCur = root_Band;
		while (pCur->nextBandwidth){//using nextMax path. not to use the EE_Next
			pCur = pCur->nextBandwidth;
		}
		pCur->nextBandwidth = pushEdge;
	}
}
void dijkstra::rebackBandwidth()
{	/*
	dijkstra::rebackBandwidth
	==================================================
	input : void
	otuput : void
	purpose : return bandwidth in case of deferred request
	*/
	Edge* pCur = root_Band;
	Edge* pBefore = NULL;
	while (pCur){//infinitied values had linked as the path of nextMAX
		pCur->bandwidth +=pCur->previousBand;//reback the cost 
		pCur->previousBand = 0;//set to initialization
		pBefore = pCur;
		pCur = pCur->nextBandwidth;//moving next edge
		pBefore->nextBandwidth = NULL;//initialize
	}
	root_Band = NULL;//Since all the edge what had infinity value changed
}
void dijkstra::clearBandwidth()
{	/*
	dijkstra::clearBandwidth
	==================================================
	input : void
	otuput : void
	purpose : clear the memory of previous bandwidth in the edge. Only the case of allocated request
	*/
	Edge* pCur = root_Band;
	Edge* pBefore = NULL;
	while (pCur){//til end of nextBandwith's edge
		pCur->previousBand = 0;//set to initialization
		pBefore = pCur;
		pCur = pCur->nextBandwidth;//moving next edge
		pBefore->nextBandwidth = NULL;//initialize
	}
	root_Band= NULL;//Since all the edge what had previousBandwidth value changed
}
void dijkstra::rebackMAX()
{	/*
	dijkstra::rebackMAX
	==================================================
	input : void
	otuput : void
	purpose : reback the cost about infinity value by using previousCost
	*/
	Edge* pCur = root_Edge;
	Edge* pBefore = NULL;
	while (pCur){//infinitied values had linked as the path of nextMAX
		pCur->cost = pCur->previousCost;//reback the cost 
		pCur->previousCost = 0;//set to initialization
		pBefore = pCur;
		pCur = pCur->nextMAX;
		pBefore->nextMAX = NULL;
	}
	root_Edge = NULL;//Since all the edge what had infinity value changed
}
void dijkstra::linkfail(char fromV, char toV)
{	/*
	dijkstra::linkfail
	==================================================
	input : char fromV ---> from vertex
			char toV ---> to vertex
	otuput : void
	purpose : Break off the edge between both side of vertexs, fromV and toV
	*/
	Vertex* pCur = root;
	while (pCur){//til end of vertex
		if (pCur->m_name == fromV || pCur->m_name ==toV){//found the same vertex
			Edge* deleteEdge = pCur->VE_next;//get the vertex's edge by VE_next
			//if programm are looking to find as soon as in VE_next, delete the special Edge.
			if ((deleteEdge->pfrom == fromV && deleteEdge->pto == toV) || (deleteEdge->pfrom == toV && deleteEdge->pto == fromV)){
				deleteEdge->cost = MAXINT;//chage cost
			}
			else{//search edge
				if (deleteEdge->EE_next){//check to next edge exist or not, but all case will be exist.
				//if this is not to exist, no need to check
					deleteEdge = deleteEdge->EE_next;
					while (deleteEdge){//til end of edge
						//found the same edge
						if ((deleteEdge->pfrom == fromV && deleteEdge->pto == toV) || (deleteEdge->pfrom == toV && deleteEdge->pto == fromV)){
							deleteEdge->cost = MAXINT;
							break;
						}
						else{//moving the pBefore and pcurrent edge 
							deleteEdge = deleteEdge->EE_next;
						}
					}//while (deleteEdge)
				}//if (deleteEdge->EE_next)
			}//else Edge
		}//if		
		pCur = pCur->V_next;//moving next vertex
	}//while
}
bool dijkstra::checkDeleteReq(char v, char d)
{	/*
	dijkstra::checkDeleteReq
	==================================================
	input : char v ---> start point
			char d ---> destination point
	otuput : bool ---> Inform whether is possible to allocate the request or not
	purpose : Inform that this request will be deleted or allocated 
	*/
	//convering for tracing reverse path
	int d_index = indexNum(d);
	int p = path[d_index];
	char pto = indextoChar(p);
	char pfrom = d;
	Vertex* check = root;//get the root
	while (check!=NULL)//til end of vertex
	{
		if (check->m_name == pto || check->m_name == pfrom){//found the same vertex
			Edge* checkLink = check->VE_next;
			while (checkLink != NULL){//til end of edge
				if (checkLink->pfrom == pfrom && checkLink->pto == pto){//if this is satisfied,
					//There is a link between two points. Therefore, no longer programm need to search .
					return false;
				}
				else if (checkLink->pto == pfrom && checkLink->pfrom == pto){//check reversely
					return false;
				}
				else{
					checkLink = checkLink->EE_next;//moving next edge
				}
			}
			//til end of edge, couldn't found it, this 
			return true;//means that fail to allocation about the request
		}
		check = check->V_next;//moving next vertex
	}
	return true;
}