// Base123_File_Mgr.h : Declare member variables

////////////////////////////////////////////////////////////////////////////////
//
//  Processes general file system requests; see ReportBase123Help() function for details:
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  14 October 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

int SystemExternalExecute(string strApplicationFilePathName, string strApplicationParameters, string& strErrorEntry);
int POpenExternalExecute(string strApplicationFilePathName, string strApplicationParameters, string& strErrorEntry);
int ProcessExternalExecute(string strApplicationFilePathName, string strApplicationParameters, string strWorkingDirectory, string& strErrorEntry);
bool ParseFileListByBatch(string strInputFilePathNameList, string strOutputListFilePathNameTransform, string strProjectPathName, int nMaxBatches);
bool CreateDistributedBatchJob(string strInputFilePathNameList, string strOutputListFilePathNameTransform, string strQueueName, string strWallTime, string strJobName, string strAccountID, string strApplicationName, string strApplicationParameters, string strProjectPathName, int nMaxBatches, bool bUseAprun, bool bMakeList, int nMaxProcs);
bool ListDeleteFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strErrorFilePathName, int nMaxProcs);
bool ListDeleteFilesInDirectory(string strInputFilePathNameList, string strDeletePathNameTransform, string strErrorFilePathName, int nMaxProcs);
bool ListConvertPath(string strInputFilePathNameList, string strOutputFilePathNameTransform, string strOutputListFilePathName, int nMaxProcs);
bool ListTransformRenameFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strFilePathNameTransforms, string strErrorFilePathName, int nMaxProcs);
bool ListMatchReplaceRenameFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strMatchAndReplace, string strErrorFilePathName, int nMaxProcs);
bool ListConfirmOutputFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strMissingListFilePathName, int nMaxProcs);
bool ListCompareDifferentialFiles(string strInputFilePathNameListFrom, string strInputFilePathNameListTo, string strFilePathNameTransform, string strDiffMethod, string strOutputListFilePathName, int nMaxProcs);