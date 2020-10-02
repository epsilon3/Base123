// Base123_FRESH.h : Declare member variables

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_FRESH Frame Respecting Eularian Shuffler (header):
//
//  FRESH generates randomly shuffled genomes based on an input sequence(s);
//  output is a sequence permutation with identical codon frequency in all
//  frames (1,2,3); nucleotide base frequency is Not considered, but will
//  necessarily preserve these frequencies with reserved codon frequency
//
//  FRESH is based on the dinucleotide/codon preserving algorithm presented
//  described by S. Altschul and B. Erickson in 1985. Expanded to preserve
//  codon usage within frames
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
#include "Base123_Catalog_Entry.h"
#include "Base123_Catalog.h"

#include <string>

using namespace std;

bool CompareStartsAndStops(const structStartStop& st1, const structStartStop& st2);
bool IsCDSStartStopStored(structStartStop& stSS, vector<structStartStop>& vSS);
bool ParseStartsAndStops(long lLength, vector<structCDS>& vCDSs, vector<structStartStop>& vSS);
bool shuffleFAFile(string strInputFilePathName, CBase123_Catalog& bCatalog, int nOutputCount, string& strListEntry, string& strErrorEntry);
bool ListshuffleFAFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strCatalogFilePathName, int nMaxCatalogEntries, int nOutputCount, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
