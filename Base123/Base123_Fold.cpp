// Base123_Fold.cpp : Function definitions

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Fold:
//
//  Conducts nucelotide polymer fold operations
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  
//  19 Sep 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#include "Base123.h"
#include "Base123_Utilities.h"
#include "Base123_File_Mgr.h"
#include "Base123_NCBI_Mgr.h"
#include "Base123_Fold.h"

#include <omp.h>
#include <sys/types.h>
#include <sys/stat.h>

////////////////////////////////////////////////////////////////////////////////
//
//  Confirms fold output files (by standard .ORF file name) via transforms
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName           :  input file path name list
//  [string] strInputFilePathNameTransform  :  input (*.pORF) file path name transform (includes string replacements, see help)
//  [string] strOutputFilePathNameTransform :  output file path name transform (includes string replacements, see help)
//  [string] strORFFolderName               :  folder name for temporary storage of .ORF file output
//  [int] nMinORFLength                     :  minimum sequence length for ORF parse
//  [int] nMaxORFLength                     :  maximum sequence length for ORF parse
//  [string] strMissingPORFListFilePathName :  missing .pORF list file path name
//  [string] strMissingORFListFilePathName  :  missing .ORF list file path name
//  [string] strAnalyticalOutputFilePathName:  analytical output file path name
//  [int] nMaxProcs                         :  maximum processors for openMP
//                                          :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListConfirmFoldOutputFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strORFFolderName, 
	int nMinORFLength, int nMaxORFLength, string strMissingPORFListFilePathName, string strMissingORFListFilePathName, string strAnalyticalOutputFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Missing pORF list entries
	vector<string> vMissingPORFEntries;
	//  Missing ORF list entries
	vector<string> vMissingORFEntries;
	//  Analytical total entries
	vector<long> vTotalEntries;
	//  Analytical total missing entries
	vector<long> vTotalMissingEntries;
	//  Analytical output entries
	vector<string> vAnalyticalOutputEntries;
	//  Missing pORF list file text
	string strMissingPORFListFileText = "";
	//  Missing ORF list file text
	string strMissingORFListFileText = "";
	//  Analytical output file text
	string strAnalyticalOutputFileText = "";
	//  

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  If output file path name transforms is not empty
			if (!strOutputFilePathNameTransform.empty())
			{
				//  If output pORF list file path name is not empty
				if (!strMissingPORFListFilePathName.empty())
				{
					//  If output ORF list file path name is not empty
					if (!strMissingORFListFilePathName.empty())
					{
						//  If analytical output file path name is not empty
						if (!strAnalyticalOutputFilePathName.empty())
						{
							//  Get input file text
							if (GetFileText(strInputFilePathNameList, strInputListFileText))
							{
								//  Split file text into file list
								SplitString(strInputListFileText, '\n', vFilePathNames);

								//  If input file text is not empty
								if (vFilePathNames.size() > 0)
								{
									//  Initialize pORF list file vector<string>
									vMissingPORFEntries.resize(vFilePathNames.size());

									//  Initialize ORF list file vector<string>
									vMissingORFEntries.resize(vFilePathNames.size());

									//  Initialize analytical total vector<long>
									vTotalEntries.resize(vFilePathNames.size());

									//  Initialize analytical total missing vector<long>
									vTotalMissingEntries.resize(vFilePathNames.size());

									//  Initialize analytical file vector<string>
									vAnalyticalOutputEntries.resize(vFilePathNames.size());

									//  Initialize time stamp lock
									omp_init_lock(&lockList);

									//  Declare omp parallel
									#pragma omp parallel num_threads(nMaxProcs)
									{
										//  omp loop
										#pragma omp for
										for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
										{
											//  Test max procs
											if (lCount == 0)
											{
												omp_set_lock(&lockList);
												ReportTimeStamp("[ListConfirmFoldOutputFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
												omp_unset_lock(&lockList);
											}

											//  Update for timestamp every 10,000 files
											if (lCount % 10000 == 0)
											{
												omp_set_lock(&lockList);
												ReportTimeStamp("[ListConfirmFoldOutputFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
												omp_unset_lock(&lockList);
											}

											//  If the file path name is not empty, then proceed
											if (!vFilePathNames[lCount].empty())
											{
												//  .pORF file path name
												string strPORFFilePathName = "";
												//  Virtual ORF vector
												vector<structORF> vORFs;
												//  List entry
												string strParsePORFListEntry = "";
												//  Error entry
												string strParsePORFErrorEntry = "";
												//  Missing ORF count
												int nORFMissingTotal = 0;

												//  If input file path name transform is not empty
												if (!strInputFilePathNameTransform.empty())
													strPORFFilePathName = TransformFilePathName(vFilePathNames[lCount], strInputFilePathNameTransform, "");
												else
													strPORFFilePathName = vFilePathNames[lCount];

												//  Fold the resultant ORF list
												if (ParsePORFtoORF(strPORFFilePathName, strORFFolderName, nMinORFLength, nMaxORFLength, true, vORFs, strParsePORFListEntry, strParsePORFErrorEntry))
												{
													//  Iterate ORFs and confirm fold output for each
													for (long lCountORF = 0; lCountORF < (long)vORFs.size(); lCountORF++)
													{
														//  If the ORF is properly set
														if ((!vORFs[lCountORF].strName.empty()) && (!vORFs[lCountORF].strSequence.empty()))
														{
															//  ORF file path name
															string strORFFilePathName = "";
															//  Output file path name
															string strOutputFilePathName = "";
															//  ORF orientation
															string strORFOrientation = "";
														
															//  Concatenate ORF file path name
															strORFFilePathName = GetBasePath(strPORFFilePathName) + strPathDelimiter;
															strORFFilePathName += strORFFolderName + strPathDelimiter;
															strORFFilePathName += GetBaseFileName(strPORFFilePathName) + "." + vORFs[lCountORF].strName + ".ORF";

															//  Get ORF orientation
															if ((strORFFilePathName.find(".F1_") != string::npos) || (strORFFilePathName.find(".F2_") != string::npos) ||
																(strORFFilePathName.find(".F3_") != string::npos))
																strORFOrientation = "f";
															else
																strORFOrientation = "r";

															//  Transform output file path name (create pseudo file name with ORF extension to get correct file name)
															strOutputFilePathName = TransformFilePathName(strORFFilePathName, strOutputFilePathNameTransform, "");
															strOutputFilePathName = ReplaceInString(strOutputFilePathName, "^ORF_ORIENTATION^", strORFOrientation, true);
															strOutputFilePathName = ReplaceInString(strOutputFilePathName, "^FNELE^", GetFileNameExceptLastExtension(strORFFilePathName), true);

															//  Transform output files
															if (!IsFilePresent(strOutputFilePathName))
															{
																if (vMissingPORFEntries[lCount].empty())
																{
																	//omp_set_lock(&lockList);
																	//ReportTimeStamp("[ListConfirmFoldOutputFiles]", "\npORF:  \n" + vFilePathNames[lCount] + "\n");
																	//omp_unset_lock(&lockList);

																	//  Append pORF with missing ORFs
																	vMissingPORFEntries[lCount] = vFilePathNames[lCount] + "\n";
																}

																//omp_set_lock(&lockList);
																//ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ORF:  \n" + strOutputFilePathName + "\n");
																//omp_unset_lock(&lockList);

																//  Append missing ORF
																vMissingORFEntries[lCount] += strORFFilePathName + "\n";

																//  increment total missing count
																nORFMissingTotal++;
															}
														}
													}

													//  Set analytical totals
													vTotalEntries[lCount] = (int)vORFs.size();
													vTotalMissingEntries[lCount] = nORFMissingTotal;

													if (nORFMissingTotal <= 0)
													{
														omp_set_lock(&lockList);
														ReportTimeStamp("[ListConfirmFoldOutputFiles]", "COMPLETE:  " + vFilePathNames[lCount]);
														omp_unset_lock(&lockList);
													}

													//  Format and set analytical output
													vAnalyticalOutputEntries[lCount] = GetAccessionFromBIGFilePathName(vFilePathNames[lCount]) + "~" + ConvertDoubleToString((double)((double)vTotalMissingEntries[lCount]/(double)vTotalEntries[lCount])*(double)100.0f).substr(0, 6) + "~" + ConvertIntToString(vTotalMissingEntries[lCount]) + "~" + ConvertIntToString(vTotalEntries[lCount]) + "\n";
												}
												else
												{
													omp_set_lock(&lockList);
													ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Virtual ORF Parse Failed");
													omp_unset_lock(&lockList);
												}
											}
										}
									}

									//  Destroy time stamp lock
									omp_destroy_lock(&lockList);

									//  Report prependix
									string strPrepend = "";
									//  ORF total
									long lORFTotal = 0;
									//  ORF missing total
									long lORFMissingTotal = 0;

									//  Iterate list file vector and concatenate file
									for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
									{
										if (!vMissingPORFEntries[lCount].empty())
											strMissingPORFListFileText += vMissingPORFEntries[lCount];

										if (!vMissingORFEntries[lCount].empty())
											strMissingORFListFileText += vMissingORFEntries[lCount];

										if (!vAnalyticalOutputEntries[lCount].empty())
											strAnalyticalOutputFileText += vAnalyticalOutputEntries[lCount];

										lORFTotal += vTotalEntries[lCount];
										lORFMissingTotal += vTotalMissingEntries[lCount];
									}

									//  Prepend totals to analytical output
									strPrepend = "Total Missing ORF:~" + ConvertLongToString(lORFMissingTotal) + "\n";
									strPrepend += "Total ORF:~" + ConvertLongToString(lORFTotal) + "\n";
									strPrepend += "Percent Missing ORF:~" + ConvertDoubleToString((double)((double)((double)lORFMissingTotal/(double)lORFTotal)*(double)100.0f)).substr(0,6) + "%\n\n";
									strAnalyticalOutputFileText = strPrepend + strAnalyticalOutputFileText;

									//  Write pORF list file
									if (!strMissingPORFListFilePathName.empty())
									{
										if (!WriteFileText(strMissingPORFListFilePathName, strMissingPORFListFileText))
											ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Output .pORF List File [" + strMissingPORFListFilePathName + "] Write Failed");
									}
									//  Write ORF list file
									if (!strMissingORFListFilePathName.empty())
									{
										if (!WriteFileText(strMissingORFListFilePathName, strMissingORFListFileText))
											ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Output .ORF List File [" + strMissingORFListFilePathName + "] Write Failed");
									}
									//  Write analytical output file
									if (!strAnalyticalOutputFilePathName.empty())
									{
										if (!WriteFileText(strAnalyticalOutputFilePathName, strAnalyticalOutputFileText))
											ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Analytical Output List File [" + strAnalyticalOutputFilePathName + "] Write Failed");
									}

									ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ANALYTICAL SUMMARY:  \n" + ReplaceInString(strPrepend, "~", "\t", false));

									return true;
								}
								else
								{
									ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
								}
							}
							else
							{
								ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
							}
						}
						else
						{
							ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Analytical Output File Path Name is Empty");
						}
					}
					else
					{
						ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Output .ORF List File Path Name is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Output .pORF List File Path Name is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Output File Path Name Transforms is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListConfirmFoldOutputFiles]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListConfirmFoldOutputFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Folds .ORF BIG Format Files
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [vector<string>&] vORFFiles       :  .ORF file path name list
//  [bool] bOverwriteFiles                    :  overwrite existing output files, if true; else, skip folds for existing output
//  [string] strThreadMode                    :  thread mode (-thread_mode_process, -thread_mode_system, -thread_mode_popen)
//  [string] strApplicationFilePathName       :  command line, program file path name
//  [string] strApplicationParameters         :  command parameters (with string replacements, see Base123 help)
//  [string] strOutputFilePathNameTransform   :  output file path name transform (with string replacements, see Base123 help)
//  [string] strOverwriteFilePathNameTransform:  output file path name transform (with string replacements, see Base123 help)
//  [string] strAfterFilePathNameTransforms   :  file path name transforms, after-creation; renames output files according to patterns (delimited in~out^in~out^...) (with string replacements, see Base123 help)
//  [int] nLengthMultiplierFactor             :  cycle-generating length mutliplier factor
//  [string] strOutputListFileNameSuffix      :  output list file name suffix (for individual .pORF fold output files)
//  [string] strOutputListFilePathName        :  output list file path name
//  [string] strErrorFilePathName             :  error file path name
//  [int] nMaxProcs                           :  maximum processors for openMP
//                                            :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool FoldORFFiles(vector<string>& vORFFiles, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory, string strApplicationFilePathName,
	string strApplicationParameters, string strOutputFilePathNameTransform, string strOverwriteFilePathNameTransform, string strAfterFilePathNameTransforms, 
	int nLengthMultiplierFactor, string strOutputListFileNameSuffix, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockProc;
	//  Process list entries
	vector<string> vListEntries;
	//  Output list file text
	string strOutputListFileText = "";
	//  Process error entries
	vector<string> vErrorEntries;
	//  Output list file text
	string strErrorFileText = "";

	try
	{
		//ReportTimeStamp("[FoldORFFiles]", "NOTE:  OFPNT =  " + strOutputFilePathNameTransform);

		//  If .ORF file path name list is not empty
		if (vORFFiles.size() > 0)
		{
			//  If application file path name is not empty
			if (!strApplicationFilePathName.empty())
			{
				//  If application parameters is not empty
				if (!strApplicationParameters.empty())
				{
					//  If output file path name transform is not empty
					if (!strOutputFilePathNameTransform.empty())
					{
						//  Initialize time stamp lock
						omp_init_lock(&lockProc);

						//  Resize process list entries
						vListEntries.resize(vORFFiles.size());

						//  Resize process error entries
						vErrorEntries.resize(vORFFiles.size());

						//  Declare omp parallel
						#pragma omp parallel num_threads(nMaxProcs)
						{
							//  omp loop
							//  Iterate virtual ORFs and fold
							#pragma omp for
							for (long lCount = 0; lCount < (long)vORFFiles.size(); lCount++)
							{
								//  Test max procs
								if (lCount == 0)
								{
									omp_set_lock(&lockProc);
									ReportTimeStamp("[FoldORFFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
									omp_unset_lock(&lockProc);
								}

								//  Update for timestamp every 100 files
								if (lCount % 100 == 0)
								{
									omp_set_lock(&lockProc);
									ReportTimeStamp("[FoldORFFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vORFFiles[lCount] + "]");
									omp_unset_lock(&lockProc);
								}

								//  If the ORF file path name is not empty
								if (!vORFFiles[lCount].empty())
								{
									//  If true, delete one-off ORF file
									bool bRemoveORFFile = false;
									//  ViennaRNA .fold file name
									string strVRNAFoldFileName = "";
									//  ViennaRNA .ps file name
									string strVRNAPSFileName = "";
									//  Output file path name
									string strOutputFilePathName = "";
									//  Overwrite file path name transform
									string strOverwriteFilePathName = "";
									//  ORF orientation [f/r]
									string strORFOrientation = "";
									//  Length 
									int nLength = 0;
									//  Length multiplier
									int nLengthMultiplier = 0;
									//  Execution parameters
									string strExecutionParameters = "";
									//  After file path name transforms
									string strAfterOutputFilePathNameTransforms = "";

									//  Get ORF orientation
									if ((vORFFiles[lCount].find(".F1_") != string::npos) || (vORFFiles[lCount].find(".F2_") != string::npos) ||
										(vORFFiles[lCount].find(".F3_") != string::npos))
										strORFOrientation = "f";
									else
										strORFOrientation = "r";

									//  Transform output file path name (create pseudo file name with ORF extension to get correct file name)
									strOutputFilePathName = TransformFilePathName(vORFFiles[lCount], strOutputFilePathNameTransform, "");
									strOutputFilePathName = ReplaceInString(strOutputFilePathName, "^ORF_ORIENTATION^", strORFOrientation, true);
									strOutputFilePathName = ReplaceInString(strOutputFilePathName, "^FNELEAS^", GetFileNameExceptLastExtension(ReplaceInString(vORFFiles[lCount], "." + strOutputListFileNameSuffix, "", false)), true);

									//omp_set_lock(&lockProc);
									//ReportTimeStamp("[FoldORFFiles]", "NOTE: OFPN = " + strOutputFilePathName);
									//omp_unset_lock(&lockProc);

									//  If output file path name is not empty
									if (!strOutputFilePathName.empty())
									{
										//  Transform overwrite file path name (create pseudo file name with ORF extension to get correct file name)
										if (!strOverwriteFilePathNameTransform.empty())
											strOverwriteFilePathName = TransformFilePathName(strOutputFilePathName, strOverwriteFilePathNameTransform, "");
										else
											strOverwriteFilePathName = TransformFilePathName(strOutputFilePathName, strOutputFilePathNameTransform, "");
										strOverwriteFilePathName = ReplaceInString(strOverwriteFilePathName, "^ORF_ORIENTATION^", strORFOrientation, true);
										strOverwriteFilePathName = ReplaceInString(strOverwriteFilePathName, "^FNELEAS^", GetFileNameExceptLastExtension(ReplaceInString(vORFFiles[lCount], "." + strOutputListFileNameSuffix, "", false)), true);

										if ((bOverwriteFiles) || ((!bOverwriteFiles) && (!IsFilePresent(strOverwriteFilePathName))))
										{
											//  If ORF file is not present, create it
											if (!IsFilePresent(vORFFiles[lCount]))
											{
												if (CreateORFFile(vORFFiles[lCount]))
													bRemoveORFFile = true;
												else
												{
													//  Update console
													omp_set_lock(&lockProc);
													ReportTimeStamp("[FoldORFFiles]", "ERROR:  .ORF File [" + vORFFiles[lCount] + "] Creation Failed");
													omp_unset_lock(&lockProc);
												}
											}

											//  Get length 
											nLength = GetLengthFromORFFilePathName(vORFFiles[lCount]);

											//  Get length multiplier
											nLengthMultiplier = nLength * nLengthMultiplierFactor;

											//  Concatenate ViennaRNA fold file name
											strVRNAFoldFileName = ReplaceInString(GetFileNameExceptLastExtension(vORFFiles[lCount]), "." + strOutputListFileNameSuffix, "", false);
											strVRNAFoldFileName += "_" + strVRNAFoldFileName;

											//  Concatenate ViennaRNA ps file name
											strVRNAPSFileName = ReplaceInString(GetFileNameExceptLastExtension(vORFFiles[lCount]), "." + strOutputListFileNameSuffix, "", false);
											//strVRNAPSFileName += "_" + strVRNAPSFileName;

											//  Update console
											//omp_set_lock(&lockProc);
											//ReportTimeStamp("[FoldORFFiles]", "NOTE:  " + strVRNAFileName);
											//omp_unset_lock(&lockProc);

											//  Transform execution parameters
											strExecutionParameters = TransformFilePathName(vORFFiles[lCount], strApplicationParameters, "");
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^INPUT_FILE_PATH_NAME^", vORFFiles[lCount], true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^INPUT_FILE_NAME^", GetFileName(vORFFiles[lCount]), true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^OUTPUT_FILE_PATH_NAME^", strOutputFilePathName, true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^OUTPUT_FILE_NAME^", GetFileName(strOutputFilePathName), true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^LENGTH_MULTIPLIER^", ConvertIntToString(nLengthMultiplier), true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^VRNA_FOLD_FILE_NAME^", strVRNAFoldFileName, true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^VRNA_PS_FILE_NAME^", strVRNAPSFileName, true);

											//  Execute command/parameters
											int nResult = -1;
											//  Working directory base path
											string strOutputWorkingDirectory = "";

											//  Get base path  name
											if (!strWorkingDirectory.empty())
												strOutputWorkingDirectory = TransformFilePathName(vORFFiles[lCount], strWorkingDirectory, "");

											//  Update console
											//omp_set_lock(&lockProc);
											//ReportTimeStamp("[FoldORFFiles]", "NOTE:  \r\n\r\n" + strApplicationFilePathName + " " + strExecutionParameters + "\r\n");
											//omp_unset_lock(&lockProc);

											if (ConvertStringToLowerCase(strThreadMode) == "-thread_mode_process")
												nResult = ProcessExternalExecute(strApplicationFilePathName, strExecutionParameters, strOutputWorkingDirectory, vErrorEntries[lCount]);
											else if (ConvertStringToLowerCase(strThreadMode) == "-thread_mode_system")
												nResult = POpenExternalExecute(strApplicationFilePathName, strExecutionParameters, vErrorEntries[lCount]);
											else if (ConvertStringToLowerCase(strThreadMode) == "-thread_mode_popen")
												nResult = SystemExternalExecute(strApplicationFilePathName, strExecutionParameters, vErrorEntries[lCount]);
											else
											{
												//  Update local error
												vErrorEntries[lCount] = vORFFiles[lCount] + "~Thread Mode [" + strThreadMode + "] is Unknown\n";

												//  Update console
												omp_set_lock(&lockProc);
												ReportTimeStamp("[FoldORFFiles]", "ERROR:  Thread Mode [" + strThreadMode + "] is Unknown");
												omp_unset_lock(&lockProc);
											}

											if (nResult > 0)
											{
												//  Concatenate list text, relative path from base
												vListEntries[lCount] = ReplaceInString(strOutputFilePathName, GetBasePath(vORFFiles[lCount]), "", false) + "\n";

												//  Rename after output files by transforms
												if (!strAfterFilePathNameTransforms.empty())
												{
													//  Transorm after file path names
													strAfterOutputFilePathNameTransforms = TransformFilePathName(strOutputFilePathName, strAfterFilePathNameTransforms, "");
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^ORF_ORIENTATION^", strORFOrientation, true);
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^WORKING_DIRECTORY^", strOutputWorkingDirectory, true);
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^FNELEAS^", GetFileNameExceptLastExtension(ReplaceInString(vORFFiles[lCount], "." + strOutputListFileNameSuffix, "", false)), true);
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^VRNA_FOLD_FILE_NAME^", strVRNAFoldFileName, true);
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^VRNA_PS_FILE_NAME^", strVRNAPSFileName, true);

													//  Set after transforms
													if (!RenameFilesByTransformSet(strAfterOutputFilePathNameTransforms))
													{
														//  Update local error
														vErrorEntries[lCount] += GetFileName(vORFFiles[lCount]) + "~Fold Output File Path Name Transforms Failed\n";

														//  Update console
														omp_set_lock(&lockProc);
														ReportTimeStamp("[FoldORFFiles]", "ERROR:  [" + GetFileName(vORFFiles[lCount]) + "] Fold Output File Path Name Transforms Failed.");
														omp_unset_lock(&lockProc);
													}
												}
											}
											else
											{
												//  Update local error
												vErrorEntries[lCount] += GetFileName(vORFFiles[lCount]) + "~Fold Failed\n";

												//  Update console
												omp_set_lock(&lockProc);
												ReportTimeStamp("[FoldORFFiles]", "ERROR:  [" + GetFileName(vORFFiles[lCount]) + "] Fold Failed.");
												omp_unset_lock(&lockProc);
											}

											//  Remove one-off ORF file
											if (bRemoveORFFile)
											{
												if (!RemoveFile(vORFFiles[lCount]))
												{
													//  Update console
													omp_set_lock(&lockProc);
													ReportTimeStamp("[FoldORFFiles]", "ERROR:  .ORF File [" + vORFFiles[lCount] + "] Removal Failed.");
													omp_unset_lock(&lockProc);
												}
											}
										}
									}
									else
									{
										//  Update local error entry
										vErrorEntries[lCount] += vORFFiles[lCount] + "~Output File Path Name is Empty\n";

										//  Update console
										omp_set_lock(&lockProc);
										ReportTimeStamp("[FoldORFFiles]", "ERROR:  Output File [" + vORFFiles[lCount] + "] Path Name is Empty");
										omp_unset_lock(&lockProc);
									}
								}
							}
						}
						
						//  Destroy time stamp lock
						omp_destroy_lock(&lockProc);

						//  Concatenate output list file text
						for (long lCount = 0; lCount < (long)vORFFiles.size(); lCount++)
						{
							if (!vListEntries[lCount].empty())
								strOutputListFileText += vListEntries[lCount];

							if (!vErrorEntries[lCount].empty())
								strErrorFileText += vErrorEntries[lCount];
						}

						//  If output list file path name is not empty
						if (!strOutputListFilePathName.empty())
						{
							//  Write output list file
							if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
								ReportTimeStamp("[FoldORFFiles]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
						}

						//  If output list file path name is not empty
						if (!strErrorFilePathName.empty())
						{
							//  Write output list file
							if (!WriteFileText(strErrorFilePathName, strErrorFileText))
								ReportTimeStamp("[FoldORFFiles]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
						}

						return true;
					}
					else
					{
						ReportTimeStamp("[FoldORFFiles]", "ERROR:  Output File Path Name Transform is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[FoldORFFiles]", "ERROR:  Application Parameter List is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[FoldORFFiles]", "ERROR:  Application File Path Name is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[FoldORFFiles]", "ERROR:  .ORF File List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [FoldORFFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Folds .pORF BIG Format File
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName             :  input file path name
//  [bool] bOverwriteFiles                    :  overwrite existing output files, if true; else, skip folds for existing output
//  [string] strThreadMode                    :  thread mode (-thread_mode_process, -thread_mode_system, -thread_mode_popen)
//  [string] strApplicationFilePathName       :  command line, program file path name
//  [string] strApplicationParameters         :  command parameters (with string replacements, see Base123 help)
//  [string] strOutputFilePathNameTransform   :  output file path name transform (with string replacements, see Base123 help)
//  [string] strOverwriteFilePathNameTransform:  output file path name transform (with string replacements, see Base123 help)
//  [string] strAfterFilePathNameTransforms   :  file path name transforms, after-creation; renames output files according to patterns (delimited in~out^in~out^...) (with string replacements, see Base123 help)
//  [int] nLengthMultiplierFactor             :  cycle-generating length mutliplier factor
//  [string] strORFFolderName                 :  folder name for temporary storage of .ORF file output
//  [int] nMinORFLength                       :  minimum sequence length for ORF parse
//  [int] nMaxORFLength                       :  maximum sequence length for ORF parse
//  [string] strOutputListFileNameSuffix      :  output list file name suffix (for individual .pORF fold output files)
//  [int] nMaxProcs                           :  maximum processors for openMP
//                                            :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool FoldPORFFile(string strInputFilePathName, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory, string strApplicationFilePathName,
	string strApplicationParameters, string strOutputFilePathNameTransform, string strOverwriteFilePathNameTransform, string strAfterFilePathNameTransforms, int nLengthMultiplierFactor, 
	string strORFFolderName, int nMinORFLength, int nMaxORFLength, string strOutputListFileNameSuffix, int nMaxProcs)
{
	//  Virtual ORF vector
	vector<structORF> vORFs;
	//  .ORF file path name list
	vector<string> vORFFiles;
	//  List entry
	string strParsePORFListEntry = "";
	//  Error entry
	string strParsePORFErrorEntry = "";
	//  Output list file path name
	string strOutputListFilePathName = "";
	//  Error file path name
	string strErrorFilePathName = "";

	try
	{
		//  If input file path name is not empty
		if (!strInputFilePathName.empty())
		{
			//  If application file path name is not empty
			if (!strApplicationFilePathName.empty())
			{
				//  If application parameters is not empty
				if (!strApplicationParameters.empty())
				{
					//  If output file path name transform is not empty
					if (!strOutputFilePathNameTransform.empty())
					{
						//  Fold the resultant ORF list
						if (ParsePORFtoORF(strInputFilePathName, strORFFolderName, nMinORFLength, nMaxORFLength, true, vORFs, strParsePORFListEntry, strParsePORFErrorEntry))
						{
							for (long lCount = 0; lCount < (long)vORFs.size(); lCount++)
							{
								//  If the ORF is properly set
								if ((!vORFs[lCount].strName.empty()) && (!vORFs[lCount].strSequence.empty()))
								{
									//  ORF file path name
									string strORFFilePathName = "";
									//  ORF file text
									string strORFFileText = "";

									//  Concatenate ORF file path name
									strORFFilePathName = GetBasePath(strInputFilePathName) + strPathDelimiter;
									strORFFilePathName += strORFFolderName + strPathDelimiter;
									if (!strOutputListFileNameSuffix.empty())
										strORFFilePathName += GetBaseFileName(strInputFilePathName) + "." + vORFs[lCount].strName + "." + strOutputListFileNameSuffix + ".ORF";
									else
										strORFFilePathName += GetBaseFileName(strInputFilePathName) + "." + vORFs[lCount].strName + ".ORF";

									//  Concatenate ORF file text (remove .suffix and replace remaining . with _ to form extended BIG extension)
									strORFFileText = ">_\n" + vORFs[lCount].strSequence;

									//  If ORF file path name is not empty
									if (!strORFFilePathName.empty())
									{
										//  Write ORF file
										if (WriteFileText(strORFFilePathName, strORFFileText))
										{
											//  Update console
											//ReportTimeStamp("[FoldPORFFile]", "NOTE:  " + strORFFilePathName );

											//  Add .ORF file path name to list
											vORFFiles.push_back(strORFFilePathName);
										}
										else
										{
											//  Update console
											ReportTimeStamp("[FoldPORFFile]", "ERROR:  .ORF File [" + strORFFilePathName + "] Write Failed");
										}
									}
									else
									{
										//  Update console
										ReportTimeStamp("[FoldPORFFile]", "ERROR:  ORF File Path Name for [" + vORFs[lCount].strName + "] is Empty");
									}
								}
							}

							if (!FoldORFFiles(vORFFiles, bOverwriteFiles, strThreadMode, strWorkingDirectory, strApplicationFilePathName, strApplicationParameters,
								strOutputFilePathNameTransform, strOverwriteFilePathNameTransform, strAfterFilePathNameTransforms, nLengthMultiplierFactor, strOutputListFileNameSuffix,
								strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
							{
								ReportTimeStamp("[FoldPORFFile]", "ERROR:  List Fold .ORF Files [" + strInputFilePathName + "] Failed");
							}

							//  Remove ORF files
							for (long lCount = 0; lCount < (long)vORFFiles.size(); lCount++)
							{
								if (!RemoveFile(vORFFiles[lCount]))
								{
									ReportTimeStamp("[FoldPORFFile]", "ERROR:  .ORF File [" + vORFFiles[lCount] + "] Removal Failed");
								}
							}

							return true;
						}
						else
						{
							ReportTimeStamp("[FoldPORFFile]", "ERROR:  Input List File [" + strInputFilePathName + "] Virtual ORF Parse Failed");
						}
					}
					else
					{
						ReportTimeStamp("[FoldPORFFile]", "ERROR:  Output File Path Name Transform is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[FoldPORFFile]", "ERROR:  Application Parameter List is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[FoldPORFFile]", "ERROR:  Application File Path Name is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[FoldPORFFile]", "ERROR:  Input File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [FoldPORFFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Performs list-based nucleotide polymer fold(s) of BIG format .pORF file(s) using ViennaRNA
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList         :  input file path name list to process
//  [bool] bPORFFiles                         :  input file lists .pORF files, if true; else, input file lists .ORF files
//  [string] strInputFilePathNameTransform    :  input file path name transform (includes string replacements, see help)
//  [bool] bOverwriteFiles                    :  overwrite existing output files, if true; else, skip folds for existing output
//  [string] strThreadMode                    :  thread mode (-thread_mode_process, -thread_mode_system, -thread_mode_popen)
//  [string] strWorkingDirectory              :  working directory
//  [string] strApplicationFilePathName       :  command line, program file path name
//  [string] strApplicationParameters         :  command parameters (with string replacements, see Base123 help)
//  [string] strOutputFilePathNameTransform   :  output file path name transform (with string replacements, see Base123 help)
//  [string] strOverwriteFilePathNameTransform:  output file path name transform (with string replacements, see Base123 help)
//  [string] strAfterFilePathNameTransforms   :  file path name transforms, after-creation; renames output files according to patterns (delimited in~out^in~out^...) (with string replacements, see Base123 help)
//  [int] nLengthMultiplierFactor             :  cycle-generating length mutliplier factor
//  [string] strORFFolderName                 :  folder name for temporary storage of .ORF file output
//  [int] nMinORFLength                       :  minimum sequence length for ORF parse
//  [int] nMaxORFLength                       :  maximum sequence length for ORF parse
//  [string] strORFOutputListFileNameSuffix   :  .ORF output list file name suffix (for individual .ORF fold output files)
//  [string] strOutputListFilePathName        :  output list file path name
//  [string] strErrorFilePathName             :  error file path name
//  [int] nMaxProcs                           :  maximum processors for openMP, .pORF list level
//                                            :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListFoldFiles(string strInputFilePathNameList, bool bPORFFiles, string strInputFilePathNameTransform, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory,
	string strApplicationFilePathName, string strApplicationParameters, string strOutputFilePathNameTransform, string strOverwriteFilePathNameTransform, 
	string strAfterFilePathNameTransforms, int nLengthMultiplierFactor, string strORFFolderName, int nMinORFLength, int nMaxORFLength, string strORFOutputListFileNameSuffix, 
	string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs)
{
	//  List file text
	string strInputListFileText = "";
	//  Input file path names
	vector<string> vFilePathNames;
	//  Output list entries
	vector<string> vListEntries;
	//  Output list file text
	string strOutputListFileText = "";
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  If application file path name is not empty
			if (!strApplicationFilePathName.empty())
			{
				//  If application parameters is not empty
				if (!strApplicationParameters.empty())
				{
					//  If output file path name transform is not empty
					if (!strOutputFilePathNameTransform.empty())
					{
						//  Get list file text
						if (GetFileText(strInputFilePathNameList, strInputListFileText))
						{
							//  Split file text into file list
							SplitString(strInputListFileText, '\n', vFilePathNames);

							//  If file path names exist
							if (vFilePathNames.size() > 0)
							{
								//  Initialize list entries vector<string>
								vListEntries.resize(vFilePathNames.size());

								//  Initialize error entries vector<string>
								vErrorEntries.resize(vFilePathNames.size());

								//  Load intel, required for some machines
								string strErrorEntry = "";
								SystemExternalExecute("module load intel", "", strErrorEntry);

								//  Change working directory
								if (((ConvertStringToLowerCase(strThreadMode) == "-thread_mode_system") || (ConvertStringToLowerCase(strThreadMode) == "-thread_mode_popen")) && (!strWorkingDirectory.empty()))
								{
									if (!ChangeWorkingFolder(strWorkingDirectory))
										ReportTimeStamp("[ListFoldFiles]", "ERROR:  Working Directory [" + strWorkingDirectory + "] Change Failed");
								}

								#ifdef _WIN64
								#else
									//  Set the umask
									umask(0007);
								#endif

								//  If the file is a BIG format pORF file
								if (bPORFFiles)
								{
									//  iterate .pORF files and fold
									for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
									{
										//  Update for timestamp every 10,000 files
										if (lCount % 10000 == 0)
										{
											ReportTimeStamp("[ListFoldFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
										}

										//  If the file path name is not empty, then proceed
										if (!vFilePathNames[lCount].empty())
										{
											//  Working file path name
											string strWorkingFilePathName = "";
											//  Path delimiter
											char chrPathDelimiter = strPathDelimiter;

											//  If input file path name transform is not empty
											if (!strInputFilePathNameTransform.empty())
												strWorkingFilePathName = TransformFilePathName(vFilePathNames[lCount], strInputFilePathNameTransform, "");
											else
												strWorkingFilePathName = vFilePathNames[lCount];

											//  If fold succeeds
											if (FoldPORFFile(strWorkingFilePathName, bOverwriteFiles, strThreadMode, strWorkingDirectory, strApplicationFilePathName, strApplicationParameters,
												strOutputFilePathNameTransform, strOverwriteFilePathNameTransform, strAfterFilePathNameTransforms, nLengthMultiplierFactor, strORFFolderName, nMinORFLength,
												nMaxORFLength, strORFOutputListFileNameSuffix, nMaxProcs))
											{
												//  Change file extension for list
												if (!strORFOutputListFileNameSuffix.empty())
													strWorkingFilePathName = GetBasePath(strWorkingFilePathName) + chrPathDelimiter + GetFileNameExceptLastExtension(strWorkingFilePathName) + "." + strORFOutputListFileNameSuffix + ".list";
												else
													strWorkingFilePathName = GetBasePath(strWorkingFilePathName) + chrPathDelimiter + GetFileNameExceptLastExtension(strWorkingFilePathName) + ".list";

												//  Get file name
												strWorkingFilePathName = GetFileName(strWorkingFilePathName);

												//  Update list entry
												vListEntries[lCount] += strWorkingFilePathName + "\n";
											}
											else
											{
												//  Update error entry
												vErrorEntries[lCount] += strWorkingFilePathName + "~.pORF Fold Failed\n";

												//  Update console
												ReportTimeStamp("[ListFoldFiles]", "ERROR:  Input File [" + strInputFilePathNameList + "] .pORF Fold Failed");
											}
										}
									}
								}
								else
								{
									if (!FoldORFFiles(vFilePathNames, bOverwriteFiles, strThreadMode, strWorkingDirectory, strApplicationFilePathName, strApplicationParameters,
										strOutputFilePathNameTransform, strOverwriteFilePathNameTransform, strAfterFilePathNameTransforms, nLengthMultiplierFactor, strORFOutputListFileNameSuffix,
										strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
									{
										ReportTimeStamp("[FoldPORFFile]", "ERROR:  List Fold .ORF Files [" + strInputFilePathNameList + "] Failed");
									}

									//  Remove ORF files
									for (long lCount = 0; lCount < (long)vFilePathNames.size(); lCount++)
									{
										if (!RemoveFile(vFilePathNames[lCount]))
										{
											ReportTimeStamp("[FoldPORFFile]", "ERROR:  .ORF File [" + vFilePathNames[lCount] + "] Removal Failed");
										}
									}
								}

								//  Iterate list vector and concatenate file
								for (long lCount = 0; lCount < (long)vFilePathNames.size(); lCount++)
								{
									if (!vListEntries[lCount].empty())
										strOutputListFileText += vListEntries[lCount];

									if (!vErrorEntries[lCount].empty())
										strErrorFileText += vErrorEntries[lCount];
								}

								//  Write list file
								if (!strOutputListFilePathName.empty())
								{
									//  Write the file
									if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
										ReportTimeStamp("[ListFoldFiles]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
								}

								//  Write error file
								if (!strErrorFilePathName.empty())
								{
									//  Write the file
									if (!WriteFileText(strErrorFilePathName, strErrorFileText))
										ReportTimeStamp("[ListFoldFiles]", "ERROR:  .pORF Error File [" + strErrorFilePathName + "] Write Failed");
								}

								return true;
							}
							else
							{
								ReportTimeStamp("[ListFoldFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
							}
						}
						else
						{
							ReportTimeStamp("[ListFoldFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
						}
					}
					else
					{
						ReportTimeStamp("[ListFoldFiles]", "ERROR:  Output File Path Name Transform is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[ListFoldFiles]", "ERROR:  Application Parameter List is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListFoldFiles]", "ERROR:  Application File Path Name is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListFoldFiles]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListFoldFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}