///////////////////////////////////////////////////////////////////////////////
// File Name : Vertex.cpp													 
// Date : 2015/12/03														 
// Compiler : g++ 4.6.3														 
// Os : ubuntu 12.04.3														 
// Author : Jae Ken Lee														 
// Student ID : 2012722081													 
// --------------------------------------------------------------------------
// ver : 1.0																 
// Description :  Please see the detailed description of samenamed headfile.  
// here is for the space to initialization of variable in this class         
// Etc : Data Structure Assignment #3 (Dijstra)								 
///////////////////////////////////////////////////////////////////////////////
#include "Vertex.h"
#include "Edge.h"
Vertex::Vertex()
{	/*
	Vertex::Vertex
	==================================================
	input : void
	otuput : void
	purpose : initialization of two pointer, and vertex's name
	*/
	m_name=0;
	V_next=NULL;//between  vertex-->bottom
	VE_next = NULL;
}
Vertex::~Vertex()
{	/*
	Vertex::~Vertex
	==================================================
	input : void
	otuput : void
	purpose : exist conception
	*/
	
}