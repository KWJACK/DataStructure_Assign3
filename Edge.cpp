///////////////////////////////////////////////////////////////////////////////
// File Name : Edge.cpp														 
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
#include "Edge.h"
#include <iostream>
Edge::Edge()
{	/*
	Edge::Edge
	==================================================
	input : void
	otuput : void
	purpose : initiallization of element in edge
	*/
	previousCost = 0;
	EE_next=NULL;
	nextBandwidth = NULL;
	nextMAX = NULL;//this will be used at last allocation on end reading event 
	pfrom=0;
	pto=0;
	cost=0;
	previousCost = 0;
	previousBand = 0;
	bandwidth = 0;
}


Edge::~Edge()
{/*
	Edge::~Edge
	==================================================
	input : void
	otuput : void
	purpose : exist conception
	*/
}
