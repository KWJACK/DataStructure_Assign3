///////////////////////////////////////////////////////////////////////////////
// File Name : Vertex.h														 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description : Vertex class is used to compose adjacency matrix together   
// Edge class. By the file router.in, Vertex will be created in dijkstra class
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>
#include "Edge.h"
class Vertex
{
public:
	Vertex();
	~Vertex();
	char m_name;//Name of Vertex will be set only capital letter
	Vertex* V_next;//link between  one vertex and other vertex
	Edge* VE_next;//vertex to edge
};
