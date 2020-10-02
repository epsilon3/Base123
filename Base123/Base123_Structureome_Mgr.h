// Base123_Structureome_Mgr.h : Declare member variables

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Structureome_Mgr Structure Analyzer (header):
//
//  Base123_Structureome_Mgr tabulates and analyzes secondary structures within
//       ViennaRNA and Rosetta fold output files
//  
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  
//  22 May 2017
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Base123.h"

#include <string>

using namespace std;

bool ListExtractPDBFromSilentFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory, string strApplicationFilePathName, string strApplicationParameters, string strOverwriteFilePathNameTransform, string strAfterFilePathNameTransforms, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
bool ListConvertPDBtoB123Files(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
bool ListConvertDBtoB123Files(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
bool ListTabulateB123Files(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputTableFilePathName, string strErrorFilePathName, int nMaxProcs);

