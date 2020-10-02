// Base123_Structur.cpp : Encapsulates a data type for the storage and manipulation of secondary structure data

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Structure Object (source):
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

#include "Base123.h"
#include "Base123_Structure.h"
#include "Base123_Utilities.h"
#include "Base123_File_Mgr.h"

#include <sstream>

//  Initialization

////////////////////////////////////////////////////////////////////////////////
//
//  Virtual Constructor
//         
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

Base123_Structure::Base123_Structure()
{
	try
	{
		//  Source file path name
		m_strFilePathName = "";

		//  Structural reading frame direction
		m_strFrameDirection = "";

		//  Structural reading frame Number
		m_nFrameNumber = -1;

		//  Structural sequence start
		m_lStart = -1;

		//  Structural sequence stop
		m_lStop = -1;

		//  Accession
		m_strNCBIAccession = "";

		//  NCBI Header
		m_strNCBIHeader = "";

		//  Sub-Structural components
		m_vSubStructures.clear();

		//  Structureome Index
		m_lStructureomeIndex = -1;
	}
	catch (exception ex)
	{
		cout << "ERROR [Base123_Structure] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Virtual Destructor
//         
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

Base123_Structure::~Base123_Structure()
{
	try
	{
	}
	catch (exception ex)
	{
		cout << "ERROR [~Base123_Structure] Exception Code:  " << ex.what() << "\n";
	}
}

//  Interface

//  I/O methods

////////////////////////////////////////////////////////////////////////////////
//
//  Write structure to Base123 .b123 File
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strOutputFilePathName:  file path name to write
//                                :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::WriteStructureToB123File(string strOutputFilePathName)
{
	try
	{
		//  File text
		string strFileText = "";

		//  If file path name is not empty
		if (!strOutputFilePathName.empty())
		{
			strFileText = StructureToB123String();

			return WriteFileText(strOutputFilePathName, strFileText);
		}
		else
		{
			ReportTimeStamp("[WriteStructureToB123File]", "ERROR:  Output File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [WriteStructureToB123File] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Write structure to Base123 .b123 File
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strOutputFilePathName:  file path name to write
//                                :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::WriteStructureToB123File()
{
	try
	{
		//  File text
		string strFileText = "";

		//  If file path name is not empty
		if (!m_strFilePathName.empty())
		{
			strFileText = StructureToB123String();

			return WriteFileText(m_strFilePathName, strFileText);
		}
		else
		{
			ReportTimeStamp("[WriteStructureToB123File]", "ERROR:  File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [WriteStructureToB123File] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Write structure to Dot-Bracket (*.db) File
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strOutputFilePathName:  file path name to write
//                                :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::WriteStructureToDBFile(string strOutputFilePathName)
{
	try
	{
		//  File text
		string strFileText = "";

		//  If file path name is not empty
		if (!strOutputFilePathName.empty())
		{
			strFileText = GetDBFileTextFromSubStructures();

			return WriteFileText(m_strFilePathName, strFileText);
		}
		else
		{
			ReportTimeStamp("[WriteStructureToDBFile]", "ERROR:  Output File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [WriteStructureToDBFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Write structure to Dot-Bracket (*.db) File
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::WriteStructureToDBFile()
{
	try
	{
		//  File text
		string strFileText = "";

		//  If file path name is not empty
		if (!m_strFilePathName.empty())
		{
			strFileText = GetDBFileTextFromSubStructures();

			return WriteFileText(m_strFilePathName, strFileText);
		}
		else
		{
			ReportTimeStamp("[WriteStructureToDBFile]", "ERROR:  File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [WriteStructureToDBFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Reads structure from Base123 (*.b123) File 
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName:  file path name to read
//                               :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::ReadStructureFromB123File(string strInputFilePathName)
{
	try
	{
		//  File text
		string strFileText = "";
		//  Structure meta structure
		structMetaStruct smsGet;

		//  If file path name is not empty
		if (!strInputFilePathName.empty())
		{
			//  Get file text
			if (GetFileText(strInputFilePathName, strFileText))
			{
				//  Get structure meta data
				smsGet = GetMetaStructureFromBIGFilePathName(strInputFilePathName);

				//  Set structure
				StructureFromB123String(strFileText);

				//  Set meta data
				m_strNCBIAccession = smsGet.strAccession;
				m_strFrameDirection = smsGet.strFrameDirection;
				m_nFrameNumber = smsGet.nFrameNumber;
				m_lStart = smsGet.lStart;
				m_lStop = smsGet.lStop;

				//  Set header
				m_strNCBIHeader = "";

				//  Set file path name
				m_strFilePathName = strInputFilePathName;

				return true;
			}
		}
		else
		{
			ReportTimeStamp("[ReadStructureFromB123File]", "ERROR:  Input Base123 File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ReadStructureFromB123File] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Reads structure from Dot-Bracket (*.db) File 
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName:  file path name to read
//                               :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::ReadStructureFromDBFile(string strInputFilePathName)
{
	try
	{
		//  File text
		string strFileText = "";
		//  File text
		vector<string> vFileTextParts;
		//  Structure meta structure
		structMetaStruct smsGet;

		//  If file path name is not empty
		if (!strInputFilePathName.empty())
		{
			//  Get file text
			if (GetFileText(strInputFilePathName, strFileText))
			{
				//  Split Dot-Bracket file text
				SplitString(strFileText, '\n', vFileTextParts);

				//  If file text parts is not empty
				if (vFileTextParts.size() >= 3)
				{
					//  Get structure meta data
					smsGet = GetMetaStructureFromBIGFilePathName(strInputFilePathName);

					//  Set header (first line is header)
					m_strNCBIHeader = vFileTextParts[0];
					//  Set structure (second line is sequence, third line is dot-bracket)
					StructureFromDBString(vFileTextParts[1], vFileTextParts[2]);

					//  Set meta data
					m_strNCBIAccession = smsGet.strAccession;
					m_strFrameDirection = smsGet.strFrameDirection;
					m_nFrameNumber = smsGet.nFrameNumber;
					m_lStart = smsGet.lStart;
					m_lStop = smsGet.lStop;

					//  Set file path name
					m_strFilePathName = strInputFilePathName;

					return true;
				}
				else
				{
					ReportTimeStamp("[ReadStructureFromDBFile]", "ERROR:  Dot-Bracket (*.db) File [" + strInputFilePathName + "] Parse Failed");
				}
			}
			else
			{
				ReportTimeStamp("[ReadStructureFromDBFile]", "ERROR:  File Path Name [" + strInputFilePathName + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ReadStructureFromDBFile]", "ERROR:  Input Base123 File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ReadStructureFromDBFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Reads structure from Rosetta PDB (*.pdb) File 
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName:  file path name to read
//                               :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::ReadStructureFromPDBFile(string strInputFilePathName)
{
	try
	{
		//  File text
		string strFileText = "";
		//  File text parts
		vector<string> vFileTextParts;

		//  If file path name is not empty
		if (!strInputFilePathName.empty())
		{
			//  If get file text
			if(GetFileText(strInputFilePathName, strFileText))
			{
				//  Split file text parts
				SplitString(strFileText, '\n', vFileTextParts);

				//  If file text parts is not empty
				if (vFileTextParts.size() > 0)
				{
					//  Iterate file text parts
					//  Set file path name
					m_strFilePathName = strInputFilePathName;
				}
				else
				{
					ReportTimeStamp("[ReadStructureFromPDBFile]", "ERROR:  PDB File Text Parts Container is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ReadStructureFromPDBFile]", "ERROR:  Input PDB File [" + strInputFilePathName + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ReadStructureFromPDBFile]", "ERROR:  Input PDB File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ReadStructureFromPDBFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

//  Structural methods

////////////////////////////////////////////////////////////////////////////////
//
//  Get source file path name
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns file path name, if successful; else, empty string
//         
////////////////////////////////////////////////////////////////////////////////

string Base123_Structure::GetFilePathName()
{
	try
	{
		return m_strFilePathName;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetFilePathName] Exception Code:  " << ex.what() << "\n";
	}

	return "";
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set source file path name
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strFilePathName:  file path name to read
//                          :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetFilePathName(string strFilePathName)
{
	try
	{
		//  
		//  If file path name is not empty
		if (!strFilePathName.empty())
		{
			//  Set file path name
			m_strFilePathName = strFilePathName;
		}
		else
		{
			ReportTimeStamp("[SetFilePathName]", "ERROR:  File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetFilePathName] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get structural reading frame direction
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns structural reading frame direction [f/r], if successful; else, empty string
//         
////////////////////////////////////////////////////////////////////////////////

string Base123_Structure::GetFrameDirection()
{
	try
	{
		return m_strFrameDirection;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetFrameDirection] Exception Code:  " << ex.what() << "\n";
	}

	return "";
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set structural reading frame direction
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strFrameDirection:  structural reading frame direction to set
//                            :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetFrameDirection(string strFrameDirection)
{
	try
	{ 
		//  If structural reading frame is not empty
		if ((ConvertStringToLowerCase(strFrameDirection) == "f") || (ConvertStringToLowerCase(strFrameDirection) == "r"))
		{
			//  Set structural reading frame
			m_strFrameDirection = ConvertStringToLowerCase(strFrameDirection);

			return true;
		}
		else
		{
			ReportTimeStamp("[SetFrameDirection]", "ERROR:  Structural Reading Frame Direction is Must Be [f/r]");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetFrameDirection] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get structural reading frame number
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns structural reading frame number [1-3], if successful; else, empty string
//         
////////////////////////////////////////////////////////////////////////////////

int Base123_Structure::GetFrameNumber()
{
	try
	{
		return m_nFrameNumber;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetFrameNumber] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set structural reading frame number
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [int] nFrameNumber:  structural reading frame number to set
//                    :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetFrameNumber(int nFrameNumber)
{
	try
	{
		//  
		//  If structural reading frame is not empty
		if ((nFrameNumber >= 1) && (nFrameNumber <= 3))
		{
			//  Set structural reading frame number
			m_nFrameNumber = nFrameNumber;

			return true;
		}
		else
		{
			ReportTimeStamp("[SetFrameNumber]", "ERROR:  Structural Reading Frame Number is Out of Range [1-3]");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetFrameNumber] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get sequence start
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns structural sub-sequence start position, if successful; else, -1
//         
////////////////////////////////////////////////////////////////////////////////

long Base123_Structure::GetStart()
{
	try
	{
		return m_lStart;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetStart] Exception Code:  " << ex.what() << "\n";
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set sequence start
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [long] lStart:  sequence start position
//               :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetStart(long lStart)
{
	try
	{
		//  If start position is greater than 0
		if (lStart >= 0)
		{
			//  Set structural sub-sequence start
			m_lStart = lStart;
		}
		else
		{
			ReportTimeStamp("[SetStart]", "ERROR:  Structural Sub-Sequence Start Position is Out of Range [>0]");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetStart] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get sequence stop
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns structural sub-sequence stop position, if successful; else, -1
//         
////////////////////////////////////////////////////////////////////////////////

long Base123_Structure::GetStop()
{
	try
	{
		return m_lStop;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetStop] Exception Code:  " << ex.what() << "\n";
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set sequence stop
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strFilePathName:  file path name to read
//                          :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetStop(long lStop)
{
	try
	{
		//  If stop position is greater than 0
		if (lStop >= 0)
		{
			//  Set structural sub-sequence stop
			m_lStop = lStop;
		}
		else
		{
			ReportTimeStamp("[SetStop]", "ERROR:  Structural Sub-Sequence Stop Position is Out of Range [>0]");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetStop] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get NCBI accession
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns NCBI accession, if successful; else, empty string
//         
////////////////////////////////////////////////////////////////////////////////

string Base123_Structure::GetNCBIAccession()
{
	try
	{
		return m_strNCBIAccession;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetNCBIAccession] Exception Code:  " << ex.what() << "\n";
	}

	return "";
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set NCBI accession
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strNCBIAccession:  NCBI accession to set
//                           :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetNCBIAccession(string strNCBIAccession)
{
	try
	{
		//  If file path name is not empty
		if (!strNCBIAccession.empty())
		{
			//  Set file path name
			m_strNCBIAccession = strNCBIAccession;

			return true;
		}
		else
		{
			ReportTimeStamp("[SetNCBIAccession]", "ERROR:  NCBI Accession is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetNCBIAccession] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get NCBI Header
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns NCBI header, if successful; else, empty string
//         
////////////////////////////////////////////////////////////////////////////////

string Base123_Structure::GetNCBIHeader()
{
	try
	{
		return m_strNCBIHeader;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetNCBIHeader] Exception Code:  " << ex.what() << "\n";
	}

	return "";
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set NCBI Header
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strNCBIHeader:  NCBI header string to set
//                        :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetNCBIHeader(string strNCBIHeader)
{
	try
	{
		//  Set NCBI header
		m_strNCBIHeader = strNCBIHeader;

		return true;
	}
	catch (exception ex)
	{
		cout << "ERROR [SetNCBIHeader] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get structureome Index
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns structureome index, if successful; else, -1
//         
////////////////////////////////////////////////////////////////////////////////

long Base123_Structure::GetStructureomeIndex()
{
	try
	{
		return m_lStructureomeIndex;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetStructureomeIndex] Exception Code:  " << ex.what() << "\n";
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set structureome Index
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [long] lStructureomeIndex:  structureome index to set
//                           :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetStructureomeIndex(long lStructureomeIndex)
{
	try
	{
		//  If index is valid
		if (lStructureomeIndex >= 0)
		{
			//  Set structureome index
			m_lStructureomeIndex = lStructureomeIndex;

			return true;
		}
		else
		{
			ReportTimeStamp("[SetStructureomeIndex]", "ERROR:  Structureome Index is Invalid [<0]");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetStructureomeIndex] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Get Structure as Base123 (*.b123) String
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns structure as a Base123 (*.b123) string, if successful; else, an empty string
//         
////////////////////////////////////////////////////////////////////////////////

string Base123_Structure::GetStructureAsB123String()
{
	try
	{
		return StructureToB123String();
	}
	catch (exception ex)
	{
		cout << "ERROR [GetStructureAsB123String] Exception Code:  " << ex.what() << "\n";
	}

	return "";
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set Structure as Base123 (*.b123) String
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strB123Structure:  structure string to set
//                           :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetStructureAsB123String(string strB123Structure)
{
	try
	{
		//  If structure is not empty
		if (!strB123Structure.empty())
		{
			return StructureFromB123String(strB123Structure);
		}
		else
		{
			ReportTimeStamp("[SetStructureAsB123String]", "ERROR:  Input Structure is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetStructureAsB123String] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set Structure as Dot-Bracket (*.db) String
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strDBSequence :  sequence string to set
//  [string] strDBStructure:  structure string to set
//                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetStructureAsDBString(string strDBSequence, string strDBStructure)
{
	try
	{
		//  If structure is not empty
		if (!strDBStructure.empty())
		{
			return StructureFromDBString(strDBSequence, strDBStructure);
		}
		else
		{
			ReportTimeStamp("[SetStructureAsDBString]", "ERROR:  Input Structure is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetStructureAsDBString] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

//  Sub-Structural methods

////////////////////////////////////////////////////////////////////////////////
//
//  Get Sub-Structure by Index
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [long] lIndex:  index of sub-structure to return
//               :  returns pointer to the indexed sub-structure, if successful; else, NULL
//         
////////////////////////////////////////////////////////////////////////////////

structSubStruct* Base123_Structure::GetSubStructByIndex(long lIndex)
{
	try
	{
		//  If index is in-range
		if ((lIndex >= 0) && (lIndex < m_vSubStructures.size()))
		{
			//  Get sub-structure
			return &m_vSubStructures[lIndex];
		}
		else
		{
			ReportTimeStamp("[GetSubStructByIndex]", "ERROR:  Index [" + ConvertLongToString(lIndex) + "] is Out of Range [0:" + ConvertLongToString(m_vSubStructures.size()) + "]");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [GetSubStructByIndex] Exception Code:  " << ex.what() << "\n";
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Set Sub-Structure by Index
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [long] lIndex                      :  index of the sub-structure to set
//  [unsigned long int] uliSubStructure:  the sub-structure to set
//  [bool] bIsStemSubStructure         :  if true, sub-structure is a stem; else, hairpin
//                                     :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::SetSubStructByIndex(long lIndex, unsigned long int uliSubStructure, bool bIsStemSubStructure)
{
	try
	{
		//  If index is in-range
		if ((lIndex >= 0) && (lIndex < m_vSubStructures.size()))
		{
			//  Set sub-structure
			m_vSubStructures[lIndex].uliSubStructure = uliSubStructure;
			m_vSubStructures[lIndex].bIsStemSubStructure = bIsStemSubStructure;
		}
		else
		{
			ReportTimeStamp("[SetSubStructByIndex]", "ERROR:  Index [" + ConvertLongToString(lIndex) + "] is Out of Range [0:" + ConvertLongToString(m_vSubStructures.size()) + "]");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SetSubStructByIndex] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Append Sub-Structure to end of stack
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] uliSubStructure  :  sub-structure to append
//  [bool] bIsStemSubStructure:  if true, sub-structure is a stem; else, hairpin
//                            :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::AppendSubStruct(string strSubStructure, bool bIsStemSubStructure)
{
	try
	{
		//  Sub-structure to append
		structSubStruct sssAppend;

		//  Set sub-structure
		stringstream(strSubStructure) >> sssAppend.uliSubStructure;
		sssAppend.bIsStemSubStructure = bIsStemSubStructure;

		return AppendSubStruct(sssAppend);
	}
	catch (exception ex)
	{
		cout << "ERROR [AppendSubStruct] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Append Sub-Structure to end of stack
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [unsigned long int] uliSubStructure:  sub-structure to append
//  [bool] bIsStemSubStructure         :  if true, sub-structure is a stem; else, hairpin
//                                     :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::AppendSubStruct(unsigned long int uliSubStructure, bool bIsStemSubStructure)
{
	try
	{
		//  Sub-structure to append
		structSubStruct sssAppend;

		//  Set sub-structure
		sssAppend.uliSubStructure = uliSubStructure;
		sssAppend.bIsStemSubStructure = bIsStemSubStructure;

		return AppendSubStruct(sssAppend);
	}
	catch (exception ex)
	{
		cout << "ERROR [AppendSubStruct] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Append Sub-Structure to end of stack 
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [structSubStruct] sssAppend:  sub-structure to append
//                             :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::AppendSubStruct(structSubStruct sssAppend)
{
	try
	{
		//  Append sub-structure
		m_vSubStructures.push_back(sssAppend);

		return true;
	}
	catch (exception ex)
	{
		cout << "ERROR [AppendSubStruct] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

//  Implementation

////////////////////////////////////////////////////////////////////////////////
//
//  Converts sub-structures to Base123 (*.b123) string
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

string Base123_Structure::StructureToB123String()
{
	//  Structure as string
	string strStructure = "";

	try
	{
		//  If sub-structures exist
		if (m_vSubStructures.size() > 0)
		{
			//  Iterate and concatenate sub-structures
			for (long lIndex = 0; lIndex < (long)m_vSubStructures.size(); lIndex++)
			{
				strStructure += ConvertUnsignedLongIntToString(m_vSubStructures[lIndex].uliSubStructure);
			}
		}
		else
		{
			ReportTimeStamp("[StructureToString]", "ERROR:  Sub-Structure Container is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [StructureToString] Exception Code:  " << ex.what() << "\n";
	}

	return strStructure;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Gets Dot-Bracket (*.db) file text from sub-structures
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns Dot-Bracket (*.db) file text, if successful; else, empty string
//         
////////////////////////////////////////////////////////////////////////////////

string Base123_Structure::GetDBFileTextFromSubStructures()
{
	//  Structure to return
	string strFileText = "";

	try
	{
		//  DB sequence
		string strSequence = "";
		//  DB structure
		string strStructure = "";
		//  If true, concatenating stem
		bool bIsStemOn = false;
		//  If true, concatenating opening bracket, else closing bracket
		bool bIsOpenBracket = true;

		//  If sub-structures exist
		if (m_vSubStructures.size() > 0)
		{
			//  Set header, default is ">_"
			if (!m_strNCBIHeader.empty())
			{
				if (m_strNCBIHeader[0] != '>')
					strFileText = ">" + m_strNCBIHeader + "\n";
				else
					strFileText = m_strNCBIHeader + "\n";
			}
			else
				strFileText = ">_\n";

			//  Iterate and concatenate sub-structures
			for (long lIndex = 0; lIndex < (long)m_vSubStructures.size(); lIndex++)
			{
				//  Sub-sequence
				string strSubSequence = "";

				//  Get sub-sequence
				strSubSequence = ConvertUnsignedLongIntToString(m_vSubStructures[lIndex].uliSubStructure);

				//  Iterate and parse sub-sequence nucleotides
				for (long lCount = 0; lCount < strSubSequence.length(); lCount++)
				{
					//  Nucleotide
					int nNuc = -1;
					string strNuc = "";

					strNuc = strSubSequence[lCount];
					stringstream(strNuc) >> nNuc;

					//  Nucleotide value, hairpin & stem, decimal
					if ((nNuc == m_untHpA) || (nNuc == m_untStA))
						strSequence += "a";
					else if ((nNuc == m_untHpC) || (nNuc == m_untStC))
						strSequence += "c";
					else if ((nNuc == m_untHpG) || (nNuc == m_untStG))
						strSequence += "g";
					else if ((nNuc == m_untHpTU) || (nNuc == m_untStTU))
						strSequence += "u";

					//  Nucleotide value, stemp, decimal
					if ((nNuc == m_untHpA) || (nNuc == m_untHpC) || (nNuc == m_untHpG) || (nNuc == m_untHpTU))
					{
						if ((bIsStemOn) && (!bIsOpenBracket))
						{
							bIsStemOn = false;
							bIsOpenBracket = true;
						}
						else if ((bIsStemOn) && (bIsOpenBracket))
						{
							bIsOpenBracket = false;
						}

						strStructure += ".";
					}
					else if ((nNuc == m_untStA) || (nNuc == m_untStC) || (nNuc == m_untStG) || (nNuc == m_untStTU))
					{
						if (!bIsStemOn)
						{
							bIsStemOn = true;
							bIsOpenBracket = true;
						}

						if (bIsOpenBracket)
							strStructure += "[";
						else
							strStructure += "]";
					}
				}
			}

			strFileText += strSequence + "\n" + strStructure + "\n";
		}
		else
		{
			ReportTimeStamp("[GetDBFileTextFromSubStructures]", "ERROR:  Sub-Structure Container is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [GetDBFileTextFromSubStructures] Exception Code:  " << ex.what() << "\n";
	}

	return strFileText;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Converts Base123 (*.b123) string to sub-structures
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strB123Structure:  structure string to convert
//                           :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::StructureFromB123String(string strB123Structure)
{
	try
	{
		//  Sub-structure
		string strSubStructure = "";
		//  Stem on, if true; else, hairpin
		bool bIsStemOn = false;

		//  Clear structural container
		m_vSubStructures.clear();

		//  If structure is not empty
		if (!strB123Structure.empty())
		{
			//  Convert Base123 nucleotides to sub-structures
			for (long lCount = 0; lCount <= strB123Structure.length(); lCount++)
			{
				//  Last nucleotide
				if (lCount == strB123Structure.length())
				{
					// If not empty, convert final sub-structure
					if (!strSubStructure.empty())
						AppendSubStruct(strSubStructure, bIsStemOn);
				}
				//  Continuing nucleotide
				else
				{
					//  Get nucleotide
					int nNuc = -1;
					string strNuc = "";

					strNuc = strB123Structure[lCount];
					stringstream(strNuc) >> nNuc;

					//  Hairpin values 1-4
					if ((nNuc >= 1) && (nNuc <= 4))
					{
						//  Turn off stem
						if (bIsStemOn)
						{
							// If not empty, convert final sub-structure
							if (!strSubStructure.empty())
								AppendSubStruct(strSubStructure, bIsStemOn);

							//  Clear sub-structure
							strSubStructure = "";
							//  Set stem flag
							bIsStemOn = false;
						}
					}
					//  Stem values 6-9
					else if ((nNuc >= 6) && (nNuc <= 9))
					{
						//  Turn on stem
						if (!bIsStemOn)
						{
							// If not empty, convert final sub-structure
							if (!strSubStructure.empty())
								AppendSubStruct(strSubStructure, bIsStemOn);

							//  Clear sub-structure
							strSubStructure = "";
							//  Set stem flag
							bIsStemOn = true;
						}
					}

					//  Concatenate sub-structure
					strSubStructure += strB123Structure[lCount];

					//  If sub-structure string equals maximum digit limit, then save and free
					if (strSubStructure.length() >= 19)
					{
						// If not empty, convert final sub-structure
						if (!strSubStructure.empty())
							AppendSubStruct(strSubStructure, bIsStemOn);

						//  Clear sub-structure
						strSubStructure = "";
					}
				}
			}

			return true;
		}
		else
		{
			ReportTimeStamp("[StructureFromB123String]", "ERROR:  Input Structure is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [StructureFromString] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Converts Dot-Bracket (*.db) string to sub-structures
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strDBSequence :  sequence string to convert
//  [string] strDBStructure:  structure string to convert
//                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool Base123_Structure::StructureFromDBString(string strDBSequence, string strDBStructure)
{
	try
	{
		//  Sub-structure
		string strSubStructure = "";
		//  Stem on, if true; else, hairpin
		bool bIsStemOn = false;

		//  Clear structural container
		m_vSubStructures.clear();

		//  If structure is not empty
		if (!strDBSequence.empty())
		{
			//  If structure is not empty
			if (!strDBStructure.empty())
			{
				//  If structure is not empty
				if (strDBSequence.length() != strDBStructure.length())
				{
					//  Iterate sequence and structure, concatenate and push sub-structures
					for (long lCount = 0; lCount <= strDBSequence.length(); lCount++)
					{
						//  Append final sub-structure
						if (lCount == strDBSequence.length())
						{
							// If not empty, convert final sub-structure
							if (!strSubStructure.empty())
								AppendSubStruct(strSubStructure, bIsStemOn);
						}
						//  Concatenate continued sub-structure
						else
						{
							//  Nuc and DB notation
							char chrNuc = '\0';
							char chrDB = '\0';

							//  Get nuc and DB notation
							chrNuc = strDBSequence[lCount];
							chrDB = strDBStructure[lCount];

							//  If hairpin and stem is on
							if (chrDB == '.')
							{
								//  If stem is on
								if (bIsStemOn)
								{
									// If not empty, convert final sub-structure
									if (!strSubStructure.empty())
										AppendSubStruct(strSubStructure, bIsStemOn);

									//  Clear sub-structure
									strSubStructure = "";
									//  Set stem flag
									bIsStemOn = false;
								}
							}
							//  If stem and stem is off
							else
							{
								//  If stem is off
								if (!bIsStemOn)
								{
									// If not empty, convert final sub-structure
									if (!strSubStructure.empty())
										AppendSubStruct(strSubStructure, bIsStemOn);

									//  Clear sub-structure
									strSubStructure = "";
									//  Set stem flag
									bIsStemOn = true;
								}
							}

							//  Concatenate sub-structure
							if ((ConvertCharacterToLowerCase(chrNuc) == 'a') && (chrDB == '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untHpA);
							}
							else if ((ConvertCharacterToLowerCase(chrNuc) == 'a') && (chrDB != '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untStA);
							}
							else if ((ConvertCharacterToLowerCase(chrNuc) == 'c') && (chrDB == '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untHpC);
							}
							else if ((ConvertCharacterToLowerCase(chrNuc) == 'c') && (chrDB != '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untStC);
							}
							else if ((ConvertCharacterToLowerCase(chrNuc) == 'g') && (chrDB == '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untHpG);
							}
							else if ((ConvertCharacterToLowerCase(chrNuc) == 'g') && (chrDB != '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untStG);
							}
							else if (((ConvertCharacterToLowerCase(chrNuc) == 'u') || (ConvertCharacterToLowerCase(chrNuc) == 't')) && (chrDB == '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untHpTU);
							}
							else if (((ConvertCharacterToLowerCase(chrNuc) == 'u') || (ConvertCharacterToLowerCase(chrNuc) == 't')) && (chrDB != '.'))
							{
								strSubStructure += ConvertUnsignedIntToString(m_untStTU);
							}

							//  If sub-structure string equals maximum digit limit, then save and free
							if (strSubStructure.length() >= 19)
							{
								// If not empty, convert final sub-structure
								if (!strSubStructure.empty())
									AppendSubStruct(strSubStructure, bIsStemOn);

								//  Clear sub-structure
								strSubStructure = "";
							}
						}
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[StructureFromDBString]", "ERROR:  Input Sequence and Structure are of Unequal Length");
				}
			}
			else
			{
				ReportTimeStamp("[StructureFromDBString]", "ERROR:  Input Structure is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[StructureFromDBString]", "ERROR:  Input Sequence is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [StructureFromDBString] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}
