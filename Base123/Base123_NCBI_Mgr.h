// Base123_NCBI_Mgr.h : Declare member variables

////////////////////////////////////////////////////////////////////////////////
//
//  Processes all NCBI file formats to be input into the Base123 system; depending on input 
//      parameters using accession number(s) as file name(s); see ReportBase123Help() function for details:
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  14 October 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

bool CreateORFFile(string strORFFilePathName);
bool ParseGBKContainerFile(string strInputFilePathName, string strOutputFilePathNameTransform, string& strListEntry, string& strErrorEntry);
bool ParseORFs(string strAccession, string strBasePathName, string strSequence, string strDirection, string strFrameNumber, string strStarts, string strStops, int nMinORFLength, int nMaxORFLength, bool bIsVirtualParse, vector<structORF>& vORFs, string& strORFListFileText, string& strErrorEntry);
bool ParsePORFtoORF(string strPORFFilePathName, string strORFFolderName, int nMinORFLength, int nMaxORFLength, bool bIsVirtualParse, vector<structORF>& vORFs, string& strORFListFileText, string& strErrorEntry);
bool ParseFAtoPORF(string strFAFilePathName, int nMinORFLength, int nMaxORFLength, string& strListEntry, string& strErrorEntry);
bool ProcessFNAFile(string strFNAFilePathName, string strOutputFilePathNameTransform, vector<string> vSubFolders, string& strFNAListEntry, string& strFAListEntry, string& strErrorEntry);
bool ListProcessFNAtoFA(string strInputFilePathNameList, string strInputFilePathNameTransform, vector<string> vSubFolders, string strFNAOutputListFilePathName, string strFAOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
bool ListParseFAtoPORF(string strInputFilePathNameList, string strInputFilePathNameTransform, int nMinORFLength, int nMaxORFLength, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
bool ListParsePORFtoORF(string strInputFilePathNameList, string strInputFilePathNameTransform, string strORFFolderName, int nMinORFLength, int nMaxORFLength, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
bool ListParseGBKContainerFiles(string strInputListFilePathName, string strOutputFilePathNameTransform, string strOutputFilePathNameList, string strErrorFilePathName, int nMaxProcs);
