// Base123_Shuffler.cpp : Defines the entry point for the console application.

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Shuffler class (header) encapsulates all the functionality of the Base123 shuffle sequence
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//      Brian Ervin (BErvin@gmail.com)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  
//  22 July 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Base123.h"

#include <string>
#include <vector>

using namespace std;

class CBase123_Shuffler
{
	//  Initialization

public:

	//  Constructor
	CBase123_Shuffler();
	//  Destructor
	virtual ~CBase123_Shuffler();

	//  Interface (public)

public:

	string shuffleSequence(string& strSequence, vector<structStartStop>& vStartsStops);
	double GetBaseSimilarities();

	//  Implementation (private)

private:

	void CountBases(string& strSequence, long(&arlBaseCount)[4]);
	void CountCodons(string& strSequence, long(&arlCodonCounts)[4][4][4]);
	void ZeroCodonCounts(long(&arlCodonCounts)[4][4][4]);
	long AnalyzeBaseSimilarites(string& strSequence, string& strshuffle);
	void AnalyzeOutput(string& strSequence, string& strshuffle);
	bool LoadEdges(string& strSequence);
	string GetCodonshuffle(string& strSequence);
	string GetBaseshuffle(string& strSequence);
	bool ZeroEdgeCounts();

	//  Max bases
	int m_nMaxBases;

	//  Max frames
	int m_nMaxFrames;

	//  Edges
	//  Bases^2xBasesxFrames; e.g., 16 doublet start nodes, 4 bases to complete codon, 3 frames
	long m_arlEdges[16][4][3];

	//  Positional base similarities
	double m_dBaseSimilarities;
};

