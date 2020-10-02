// Base123.h : Declare member variables

////////////////////////////////////////////////////////////////////////////////
//
//  Base123 main application (header):
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  22 June 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

using namespace std;

#include <string>
#include <vector>
#include <iostream>

//  Base123 members

#ifdef _WIN64
	#define strPathDelimiter '\\';
#else
	#define strPathDelimiter '/';
#endif

//  Base123 structureome structure meta-data, structure
struct structMetaStruct
{
	string strAccession;
	string strFrameDirection;
	int nFrameNumber;
	long lStart;
	long lStop;
};

//  Structureome sub-structure, structure
struct structSubStruct
{
	unsigned long int uliSubStructure;
	bool bIsStemSubStructure;
};

//  ORF structure
struct structORF
{
	string strName;
	string strSequence;
};

//  CDS structure
struct structCDS
{
	string strIsComplement;
	string strNameID;
	long lStart;
	long lStop;
	string strCompleteness;
};

//  CDS start/stop structure
struct structStartStop
{
	long lStart;
	long lStop;
	int nDepth;
};

//  Adenine nucleotide value, binary
const unsigned int m_untA = 0b00;
//  Cytosine nucleotide value, binary
const unsigned int m_untC = 0b01;
//  Guanine nucleotide value, binary
const unsigned int m_untG = 0b10;
//  Thymine/uracil nucleotide value, binary
const unsigned int m_untTU = 0b11;

//  Empty nucleotide value, decimal
const unsigned int m_untVoidACGTU = 0;

//  Adenine nucleotide value, hairpin, decimal
const unsigned int m_untHpA = 1;
//  Cytosine nucleotide value, hairpin, decimal
const unsigned int m_untHpC = 2;
//  Guanine nucleotide value, hairpin, decimal
const unsigned int m_untHpG = 3;
//  Thymine/uracil nucleotide value, hairpin, decimal
const unsigned int m_untHpTU = 4;

//  Empty nucleotide value, decimal
const unsigned int m_untStructSpace = 5;

//  Adenine nucleotide value, stem, decimal
const unsigned int m_untStA = 6;
//  Cytosine nucleotide value, stem, decimal
const unsigned int m_untStC = 7;
//  Guanine nucleotide value, stem, decimal
const unsigned int m_untStG = 8;
//  Thymine/uracil nucleotide value, stem, decimal
const unsigned int m_untStTU = 9;