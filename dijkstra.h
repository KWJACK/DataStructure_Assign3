///////////////////////////////////////////////////////////////////////////////
// File Name : dijkstra0.h													 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : Dijkstra class can calculate shortest path in adjacency matrix 
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <stdlib.h>
#define nmax 100
#define MAXINT 9999
class dijkstra
{
private:
	///these three variable(dist, s, path) will be used dynamic allocation. 
	int* dist;//for saving the shortest path per index
	bool* s;//for checking to find shortest path per index.If this is true, that mean this index of Vertex had checked to find shortest path
	int* path;//for traceback the shortest path per index.
	Vertex* root;//This adjacency matrix. 
	Vertex* root_stack;//data structure of stack is useful to make reverse order.
	Edge* root_Edge;
	Edge* root_Band;
	int sumVertex;//The number of vertex
	void push_Vertex(char v);//push vertex can help to make traceback of path
	//This func will be used only inner.
public:
	dijkstra();
	~dijkstra();
	void makeAdacency(int n);
	bool requesetAllocate(char v, char d, int band);
	void shortestPath(char v, char d, int band);
	int choose();
	Edge* find(int v1, int v2);

	void createLength(char* arr[]);
	Edge* createEdge(char from, char to, int bandwidth, int cost);
	Vertex* listSearch(char target);
	int indexNum(char name);
	char indextoChar(int index);
	char pop_Vertex();
	void push_edge(Edge* pushEdge);
	int getSumVertex();

	void linkfail(char fromV, char toV);
	void rebackMAX();
	bool changecost(char v, char d, int band);
	void returnBandwidth(char v, char d, int band);
	bool checkDeleteReq(char v, char d);
	void memorizeBandwidth(Edge* pushEdge, int bandwidth);
	void rebackBandwidth();
	void clearBandwidth();
};

