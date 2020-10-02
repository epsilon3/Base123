// Base123_Structureome_Mgr.cpp : Tabulates and analyzes secondary structures within ViennaRNA and Rosetta fold output files

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Structureome_Mgr Structure Analyzer (source):
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

#include "Base123.h"
#include "Base123_Utilities.h"
#include "Base123_File_Mgr.h"

#include <omp.h>
#include <sys/types.h>
#include <sys/stat.h>

////////////////////////////////////////////////////////////////////////////////
//
//  Extracts PDB from Rosetta silent (*.out) files
//
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList         :  input file path name list to process
//  [string] strInputFilePathNameTransform    :  input file path name transform (includes string replacements, see help)
//  [bool] bOverwriteFiles                    :  overwrite existing output files, if true; else, skip folds for existing output
//  [string] strThreadMode                    :  thread mode (-thread_mode_process, -thread_mode_system, -thread_mode_popen)
//  [string] strWorkingDirectory              :  working directory
//  [string] strApplicationFilePathName       :  command line, program file path name
//  [string] strApplicationParameters         :  command parameters (with string replacements, see Base123 help)
//  [string] strOverwriteFilePathNameTransform:  overwrite file path name transform (with string replacements, see Base123 help)
//  [string] strAfterFilePathNameTransforms   :  file path name transforms, after-creation; renames output files according to patterns (delimited in~out^in~out^...) (with string replacements, see Base123 help)
//  [string] strOutputListFilePathName        :  output list file path name
//  [string] strErrorFilePathName             :  error file path name
//  [int] nMaxProcs                           :  maximum processors for openMP, .pORF list level
//                                            :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListExtractPDBFromSilentFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, bool bOverwriteFiles, string strThreadMode, string strWorkingDirectory, 
	string strApplicationFilePathName, string strApplicationParameters, string strOverwriteFilePathNameTransform, string strAfterFilePathNameTransforms, string strOutputListFilePathName, 
	string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Output list file entry text
	vector<string> vOutputListEntries;
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
					//  Get list file text
					if (GetFileText(strInputFilePathNameList, strInputListFileText))
					{
						//  Split file text into file list
						SplitString(strInputListFileText, '\n', vFilePathNames);

						//  If file path names exist
						if (vFilePathNames.size() > 0)
						{
							//  Initialize list entries vector<string>
							vOutputListEntries.resize(vFilePathNames.size());

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

							//  Initialize time stamp lock
							omp_init_lock(&lockList);

							//  Declare omp parallel
							#pragma omp parallel num_threads(nMaxProcs)
							{
								//  omp loop
								//  Iterate virtual ORFs and fold
								#pragma omp for
								for (long lCount = 0; lCount < (long)vFilePathNames.size(); lCount++)
								{
									//  Test max procs
									if (lCount == 0)
									{
										omp_set_lock(&lockList);
										ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
										omp_unset_lock(&lockList);
									}

									//  Update for timestamp every 100 files
									if (lCount % 100 == 0)
									{
										omp_set_lock(&lockList);
										ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
										omp_unset_lock(&lockList);
									}

									//omp_set_lock(&lockList);
									//ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "NOTE:  " + vFilePathNames[lCount]);
									//omp_unset_lock(&lockList);

									//  If the file path name is not empty
									if (!vFilePathNames[lCount].empty())
									{
										//  Overwrite file path name transform
										string strOverwriteFilePathName = "";
										//  ORF orientation [f/r]
										string strORFOrientation = "";
										//  Execution parameters
										string strExecutionParameters = "";
										//  After file path name transforms
										string strAfterOutputFilePathNameTransforms = "";

										//  Get ORF orientation
										if ((vFilePathNames[lCount].find(".F1_") != string::npos) || (vFilePathNames[lCount].find(".F2_") != string::npos) ||
											(vFilePathNames[lCount].find(".F3_") != string::npos))
											strORFOrientation = "f";
										else
											strORFOrientation = "r";

											//  Transform overwrite file path name (create pseudo file name with ORF extension to get correct file name)
										if (!strOverwriteFilePathNameTransform.empty())
										{
											strOverwriteFilePathName = TransformFilePathName(vFilePathNames[lCount], strOverwriteFilePathNameTransform, "");
											strOverwriteFilePathName = ReplaceInString(strOverwriteFilePathName, "^ORF_ORIENTATION^", strORFOrientation, true);
											strOverwriteFilePathName = ReplaceInString(strOverwriteFilePathName, "^FNELEAS^", GetFileNameExceptLastExtension(vFilePathNames[lCount]), true);
										}

										if ((bOverwriteFiles) || ((!bOverwriteFiles) && (!strOverwriteFilePathName.empty()) && (!IsFilePresent(strOverwriteFilePathName))))
										{
											//  Transform execution parameters
											strExecutionParameters = TransformFilePathName(vFilePathNames[lCount], strApplicationParameters, "");
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^INPUT_FILE_PATH_NAME^", vFilePathNames[lCount], true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^INPUT_FILE_NAME^", GetFileName(vFilePathNames[lCount]), true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^ORF_ORIENTATION^", strORFOrientation, true);
											strExecutionParameters = ReplaceInString(strExecutionParameters, "^FNELEAS^", GetFileNameExceptLastExtension(vFilePathNames[lCount]), true);

											//  Execute command/parameters
											int nResult = -1;
											//  Working directory base path
											string strOutputWorkingDirectory = "";

											//  Get base path  name
											if (!strWorkingDirectory.empty())
												strOutputWorkingDirectory = TransformFilePathName(vFilePathNames[lCount], strWorkingDirectory, "");

											//  Update console
											//omp_set_lock(&lockList);
											//ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "NOTE:  \n" + strApplicationFilePathName + " " + strExecutionParameters + "\n\n");
											//omp_unset_lock(&lockList);

											omp_set_lock(&lockList);
											if (ConvertStringToLowerCase(strThreadMode) == "-thread_mode_process")
												nResult = ProcessExternalExecute(strApplicationFilePathName, strExecutionParameters, strOutputWorkingDirectory, vErrorEntries[lCount]);
											else if (ConvertStringToLowerCase(strThreadMode) == "-thread_mode_system")
												nResult = POpenExternalExecute(strApplicationFilePathName, strExecutionParameters, vErrorEntries[lCount]);
											else if (ConvertStringToLowerCase(strThreadMode) == "-thread_mode_popen")
												nResult = SystemExternalExecute(strApplicationFilePathName, strExecutionParameters, vErrorEntries[lCount]);
											else
											{
												//  Update local error
												vErrorEntries[lCount] = vFilePathNames[lCount] + "~Thread Mode [" + strThreadMode + "] is Unknown\n";

												//  Update console
												//omp_set_lock(&lockList);
												ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Thread Mode [" + strThreadMode + "] is Unknown");
												//omp_unset_lock(&lockList);
											}
											omp_unset_lock(&lockList);

											if (nResult > 0)
											{
												//  Concatenate list text, relative path from base
												vOutputListEntries[lCount] = strOverwriteFilePathName + "\n";

												//  Rename after output files by transforms
												if (!strAfterFilePathNameTransforms.empty())
												{
													//  Transorm after file path names
													strAfterOutputFilePathNameTransforms = TransformFilePathName(strOverwriteFilePathName, strAfterFilePathNameTransforms, "");
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^ORF_ORIENTATION^", strORFOrientation, true);
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^WORKING_DIRECTORY^", strOutputWorkingDirectory, true);
													strAfterOutputFilePathNameTransforms = ReplaceInString(strAfterOutputFilePathNameTransforms, "^FNELEAS^", GetFileNameExceptLastExtension(vFilePathNames[lCount]), true);

													//  Set after transforms
													if (!RenameFilesByTransformSet(strAfterOutputFilePathNameTransforms))
													{
														//  Update local error
														vErrorEntries[lCount] += GetFileName(vFilePathNames[lCount]) + "~.pdb Output File Path Name Transforms Failed\n";

														//  Update console
														omp_set_lock(&lockList);
														ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  [" + GetFileName(vFilePathNames[lCount]) + "] .pdb Output File Path Name Transforms Failed.");
														omp_unset_lock(&lockList);
													}
												}
											}
											else
											{
												//  Update local error
												vErrorEntries[lCount] += GetFileName(vFilePathNames[lCount]) + "~.pdb Extract Failed\n";

												//  Update console
												omp_set_lock(&lockList);
												ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  [" + GetFileName(vFilePathNames[lCount]) + "] .pdb Extract Failed.");
												omp_unset_lock(&lockList);
											}
										}
									}
								}
							}

							//  Destroy time stamp lock
							omp_destroy_lock(&lockList);

							//  Concatenate output list file text
							for (long lCount = 0; lCount < (long)vFilePathNames.size(); lCount++)
							{
								if (!vOutputListEntries[lCount].empty())
									strOutputListFileText += vOutputListEntries[lCount];

								if (!vErrorEntries[lCount].empty())
									strErrorFileText += vErrorEntries[lCount];
							}

							//  If output list file path name is not empty
							if (!strOutputListFilePathName.empty())
							{
								//  Write output list file
								if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
									ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
							}

							//  If output list file path name is not empty
							if (!strErrorFilePathName.empty())
							{
								//  Write output list file
								if (!WriteFileText(strErrorFilePathName, strErrorFileText))
									ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
							}

							return true;
						}
						else
						{
							ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
						}
					}
					else
					{
						ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
					}
				}
				else
				{
					ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Application Parameter List is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Application File Path Name is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListExtractPDBFromSilentFiles]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListExtractPDBFromSilentFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Converts PDB to Base123 file format
//
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName          :  input file path name list
//  [string] strInputFilePathNameTransform :  input (*.out) file path name transform (includes string replacements, see help)
//  [string] strOutputFilePathNameTransform:  output (*.b123) file path name transform (includes string replacements, see help)
//  [string] strOutputListFilePathName     :  output list file path name
//  [string] strErrorFilePathName          :  error file path name
//  [int] nMaxProcs                        :  maximum processors for openMP
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListConvertPDBtoB123Files(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strOutputListFilePathName, 
	string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Output list file entry text
	vector<string> vOutputListEntries;
	//  Output list file text
	string strOutputListFileText = "";
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		if (!strInputFilePathNameList.empty())
		{
			//  Get input file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If input file text is not empty
				if (vFilePathNames.size() > 0)
				{
					//  Initialize output list file vector<string>
					vOutputListEntries.resize(vFilePathNames.size());

					//  Initialize erro file vector<string>
					vErrorEntries.resize(vFilePathNames.size());

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
								ReportTimeStamp("[ListConvertPDBtoB123Files]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListConvertPDBtoB123Files]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
								omp_unset_lock(&lockList);
							}

							//  If the file path name is not empty, then proceed
							if (!vFilePathNames[lCount].empty())
							{
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Iterate list file vector and concatenate file
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vOutputListEntries[lCount].empty())
							strOutputListFileText += vOutputListEntries[lCount];

						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  Write output list file
					if (!strOutputListFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
							ReportTimeStamp("[ListConvertPDBtoB123Files]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListConvertPDBtoB123Files]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListConvertPDBtoB123Files]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListConvertPDBtoB123Files]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListConvertPDBtoB123Files]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListConvertPDBtoB123Files] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Converts ViennaRNA fold output file(s) (*.fold) to Base123 (*.b123) file(s)
//
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName          :  input file path name list
//  [string] strInputFilePathNameTransform :  input (*.out) file path name transform (includes string replacements, see help)
//  [string] strOutputFilePathNameTransform:  output (*.b123) file path name transform (includes string replacements, see help)
//  [string] strOutputListFilePathName     :  output list file path name
//  [string] strErrorFilePathName          :  error file path name
//  [int] nMaxProcs                        :  maximum processors for openMP
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListConvertDBtoB123Files(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strOutputListFilePathName, 
	string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Output list file entry text
	vector<string> vOutputListEntries;
	//  Output list file text
	string strOutputListFileText = "";
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		if (!strInputFilePathNameList.empty())
		{
			//  Get input file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If input file text is not empty
				if (vFilePathNames.size() > 0)
				{
					//  Initialize output list file vector<string>
					vOutputListEntries.resize(vFilePathNames.size());

					//  Initialize erro file vector<string>
					vErrorEntries.resize(vFilePathNames.size());

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
								ReportTimeStamp("[ListConvertDBtoB123Files]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListConvertDBtoB123Files]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
								omp_unset_lock(&lockList);
							}

							//  If the file path name is not empty, then proceed
							if (!vFilePathNames[lCount].empty())
							{
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Iterate list file vector and concatenate file
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vOutputListEntries[lCount].empty())
							strOutputListFileText += vOutputListEntries[lCount];

						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  Write output list file
					if (!strOutputListFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
							ReportTimeStamp("[ListConvertDBtoB123Files]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListConvertDBtoB123Files]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListConvertDBtoB123Files]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListConvertDBtoB123Files]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListConvertDBtoB123Files]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListConvertDBtoB123Files] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Tabulates secondary structures found within Base123 (*.b123) output file(s)
//
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName          :  input file path name list
//  [string] strInputFilePathNameTransform :  input (*.b123) file path name transform (includes string replacements, see help)
//  [string] strOutputTableFilePathName    :  Base123 structureome table output list file path name
//  [string] strErrorFilePathName          :  error file path name
//  [int] nMaxProcs                        :  maximum processors for openMP
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListTabulateB123Files(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputTableFilePathName, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Output list file entry text
	vector<string> vOutputListEntries;
	//  Output list file text
	string strOutputListFileText = "";
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		if (!strInputFilePathNameList.empty())
		{
			//  Get input file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If input file text is not empty
				if (vFilePathNames.size() > 0)
				{
					//  Initialize output list file vector<string>
					vOutputListEntries.resize(vFilePathNames.size());

					//  Initialize erro file vector<string>
					vErrorEntries.resize(vFilePathNames.size());

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
								ReportTimeStamp("[ListTabulateB123Files]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListTabulateB123Files]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
								omp_unset_lock(&lockList);
							}

							//  If the file path name is not empty, then proceed
							if (!vFilePathNames[lCount].empty())
							{
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Iterate list file vector and concatenate file
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vOutputListEntries[lCount].empty())
							strOutputListFileText += vOutputListEntries[lCount];

						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  Write output list file
					if (!strOutputTableFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strOutputTableFilePathName, strOutputListFileText))
							ReportTimeStamp("[ListTabulateB123Files]", "ERROR:  Output Table File [" + strOutputTableFilePathName + "] Write Failed");
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListTabulateB123Files]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListTabulateB123Files]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListTabulateB123Files]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListTabulateB123Files]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListTabulateB123Files] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

