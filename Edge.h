///////////////////////////////////////////////////////////////////////////////
// File Name : Edge.h														 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : Edge class is used to compose adjacency matrix. This edge 	 
// mean connecting between one vertex with other vertex. And those link are	 
// duplex link.																 
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
using namespace std;
class Edge
{
	friend class Vertex;
private:
	
public:
	Edge();
	~Edge();
	char pfrom;//start point vertax
	char pto;//destination vertax
	Edge* EE_next;//
	Edge* nextMAX;
	Edge* nextBandwidth;
	int cost;
	int previousCost;
	int previousBand;
	int bandwidth;
	
};

