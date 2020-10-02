// Base123_Fold.h : Declare member variables

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Fold:  
//
//  Conducts nuceotide polymer fold operations
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  19 Sep 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Base123.h"

#include <string>

using namespace std;

bool ListConfirmFoldOutputFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strORFFolderName, int nMinORFLength, int nMaxORFLength, string strMissingPORFListFilePathName, string strMissingORFListFilePathName, string strAnalyticalOutputFilePathName, int nMaxProcs);
bool FoldORFFiles(vector<string>& vORFFiles, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory, string strApplicationFilePathName, string strApplicationParameters, string strOutputFilePathNameTransform, string strOverwriteFilePathNameTransform, string strAfterFilePathNameTransforms, int nLengthMultiplierFactor, string strOutputListFileNameSuffix, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);
bool FoldPORFFile(string strInputFilePathName, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory, string strApplicationFilePathName, string strApplicationParameters, string strOutputFilePathNameTransform, string strOverwriteFilePathNameTransform, string strAfterFilePathNameTransforms, int nLengthMultiplierFactor, string strORFFolderName, int nMinORFLength, int nMaxORFLength, string strOutputListFileNameSuffix, int nMaxProcs);
bool ListFoldFiles(string strInputFilePathNameList, bool bPORFFiles, string strInputFilePathNameTransform, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory, string strApplicationFilePathName, string strApplicationParameters, string strOutputFilePathNameTransform, string strOverwriteFilePathNameTransform, string strAfterFilePathNameTransforms, int nLengthMultiplierFactor, string strORFFolderName, int nMinORFLength, int nMaxORFLength, string strORFOutputListFileNameSuffix, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs);