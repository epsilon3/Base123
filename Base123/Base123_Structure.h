// Base123_Structur.h : Declare member variables

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Structure Object (header):
//
//  Base123_Structure encapsulates a data type for the storage and manipulation of
//        secondary structure data
//  
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  
//  3 August 2017
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Base123.h"

#include <string>

using namespace std;

class Base123_Structure
{
	//  Initialization

public:
	//  Constructor
	Base123_Structure();
	//  Constructor
	virtual ~Base123_Structure();

	//  Interface (public)

public:

	//  I/O methods

	//  Write structure to Base123 (*.b123) File
	bool WriteStructureToB123File(string strOutputFilePathName);
	//  Write structure to Base123 (*.b123) File
	bool WriteStructureToB123File();
	//  Write structure to Dot-Bracket (*.db) File
	bool WriteStructureToDBFile(string strOutputFilePathName);
	//  Write structure to Dot-Bracket (*.db) File
	bool WriteStructureToDBFile();
	//  Read structure from Base123 (*.b123) File
	bool ReadStructureFromB123File(string strFilePathName);
	//  Read structure from Dot-Bracket (*.db) or ViennaRNA (*.fold) File
	bool ReadStructureFromDBFile(string strFilePathName);
	//  Read structure from Rosetta PDB (*.pdb) File
	bool ReadStructureFromPDBFile(string strFilePathName);

	//  Structural methods

	//  Get source file path name
	string GetFilePathName();
	//  Set source file path name
	bool SetFilePathName(string strFilePathName);
	//  Get structural reading frame direction
	string GetFrameDirection();
	//  Set structural reading frame direction
	bool SetFrameDirection(string strFrameDirection);
	//  Get structural reading frame number
	int GetFrameNumber();
	//  Set structural reading frame number
	bool SetFrameNumber(int nFrameNumber);
	//  Get sequence start
	long GetStart();
	//  Set sequence start
	bool SetStart(long lStart);
	//  Get sequence stop
	long GetStop();
	//  Set sequence stop
	bool SetStop(long lStop);
	//  Get NCBI accession
	string GetNCBIAccession();
	//  Set NCBI accession
	bool SetNCBIAccession(string strAccession);
	//  Get NCBI Header
	string GetNCBIHeader();
	//  Set NCBI Header
	bool SetNCBIHeader(string strNCBIHeader);
	//  Get structureome Index
	long GetStructureomeIndex();
	//  Set structureome Index
	bool SetStructureomeIndex(long lStructureomeIndex);

	//  Get Structure as Base123 (*.b123) String
	string GetStructureAsB123String();
	//  Set Structure as Base123 (*.b123) String
	bool SetStructureAsB123String(string strStructure);
	//  Set Structure as Dot-Bracket (*.db) String
	bool SetStructureAsDBString(string strDBSequence, string strStructure);

	//  Sub-Structural methods

	//  Get Sub-Structure by Index
	structSubStruct* GetSubStructByIndex(long lIndex);
	//  Set Sub-Structure by Index
	bool SetSubStructByIndex(long lIndex, unsigned long int uliSubStructure, bool bIsStemSubStructure);
	//  Append Sub-Structure to end of stack
	bool AppendSubStruct(string strSubStructure, bool bIsStemSubStructure);
	//  Append Sub-Structure to end of stack
	bool AppendSubStruct(unsigned long int uliSubStructure, bool bIsStemSubStructure);
	//  Append Sub-Structure to end of stack
	bool AppendSubStruct(structSubStruct sssAppend);

	//  Implementation (private)

private:

	//  Operational methods

	//  Converts sub-structures to Base123 (*.b123) string
	string StructureToB123String();
	//  Gets Dot-Bracket (*.db) file text from sub-structures
	string GetDBFileTextFromSubStructures();
	//  Converts Base123 (*.b123) string to sub-structures
	bool StructureFromB123String(string strB123Structure);
	//  Converts Dot-Bracket (*.db) string to sub-structures
	bool StructureFromDBString(string strSequence, string strDBStructure);

	//  Member variables

	//  Source file path name
	string m_strFilePathName;

	//  Structural reading frame direction
	string m_strFrameDirection;

	//  Structural reading frame number
	int m_nFrameNumber;

	//  Structural sequence start
	long m_lStart;

	//  Structural sequence stop
	long m_lStop;

	//  NCBI Accession
	string m_strNCBIAccession;

	//  NCBI Header
	string m_strNCBIHeader;

	//  Sub-Structural components
	vector<structSubStruct> m_vSubStructures;

	//  Structureome Index
	long m_lStructureomeIndex;
};

