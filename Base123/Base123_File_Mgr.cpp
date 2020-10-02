// Base123_File_Mgr.cpp : Defines the entry point for the console application.

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

#include "Base123.h"
#include "Base123_File_Mgr.h"
#include "Base123_Utilities.h"

#include <sstream>
#include <omp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <iterator>
#include <set>

#ifdef _WIN64
#else
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#endif

////////////////////////////////////////////////////////////////////////////////
//
//  Calls system and executes an external program
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strApplicationFilePathName:  file path name of executable
//  [string] strApplicationParameters  :  executable parameters
//  [string&] strErrorEntry            :  error file entry
//                                     :  returns execution status, 1 for success; else, 0 for failure;
//         
////////////////////////////////////////////////////////////////////////////////

int SystemExternalExecute(string strApplicationFilePathName, string strApplicationParameters, string& strErrorEntry)
{
	try
	{
		//  If application file path name is not empty
		if (!strApplicationFilePathName.empty())
		{
			#ifdef _WIN64
			#else
				
				//  Return status
				int nStatus = 0;
				//  Command + parameters
				string strCommandParameters = "";

				//  Concatenate command and parameters
				strCommandParameters = strApplicationFilePathName + " " + strApplicationParameters;

				//  Update console
				//ReportTimeStamp("[SystemExternalExecute]", "NOTE:  " + strCommandParameters);

				//  Execute
				nStatus = system(strCommandParameters.c_str());

				//  Report status
				if (nStatus < 0)
				{
					//  Update error entry
					strErrorEntry += strApplicationParameters + "~Exit Error [" + GetErrorMessage(errno) + "]\n";

					//  Update console
					ReportTimeStamp("[SystemExternalExecute]", "ERROR:  External Command Execution [" + strApplicationParameters + "] Failed [" + GetErrorMessage(errno) + "]");

					return 0;
				}

			#endif

			//  Return success
			return 1;
		}
		else
		{
			ReportTimeStamp("[SystemExternalExecute]", "ERROR:  Application File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [SystemExternalExecute] Exception Code:  " << ex.what() << "\n";
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Forks a child process and popens an external program
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strApplicationFilePathName:  file path name of executable
//  [string] strApplicationParameters  :  executable parameters
//  [string&] strErrorEntry            :  error file entry
//                                     :  returns execution status, 1 for success; else, 0 for failure;
//         
////////////////////////////////////////////////////////////////////////////////

int POpenExternalExecute(string strApplicationFilePathName, string strApplicationParameters, string& strErrorEntry)
{
	try
	{
		//  If application file path name is not empty
		if (!strApplicationFilePathName.empty())
		{
			int nReturn = -1;

			#ifdef _WIN64
			#else

				//  Command + parameters
				string strCommandParameters = "";
				FILE *fpPOpen;
				char buffGet[512];

				//  Concatenate command and parameters
				strCommandParameters = strApplicationFilePathName + " " + strApplicationParameters;

				//ReportTimeStamp("[POpenExternalExecute]", "NOTE:  CP = " + strCommandParameters + "\n");

				umask(0007);

				fpPOpen = popen(strCommandParameters.c_str(), "r");
				if (fpPOpen == NULL)
				{
					//  Update error entry
					strErrorEntry += strApplicationParameters + "~POpen [" + strCommandParameters + "] Failed [" + GetErrorMessage(errno) + "]";

					return 0;
				}
				else
				{
					if (fgets(buffGet, sizeof(buffGet), fpPOpen) != NULL)
						puts(buffGet);
					pclose(fpPOpen);

					string strOutput(buffGet);

					if (strOutput.find_first_of("ERROR") != string::npos)
					{
						//ReportTimeStamp("[POpenExternalExecute]", "NOTE:  FAILURE!  CP = " + strCommandParameters + "\n");

						//cin.get();

						return 0;
					}
					else
					{
						//ReportTimeStamp("[POpenExternalExecute]", "NOTE:  SUCCESS!  CP = " + strCommandParameters + "\n");

						//cin.get();

						return 1;
					}
				}

			#endif
		}
		else
		{
			ReportTimeStamp("[POpenExternalExecute]", "ERROR:  Application File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [POpenExternalExecute] Exception Code:  " << ex.what() << "\n";
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Forks a child process and executes an external program
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strApplicationFilePathName:  file path name of executable
//  [string] strApplicationParameters  :  executable parameters
//  [string] strWorkingDirectory       :  working directory for child process (if not empty, child process calls chdir(strWorkingDirectory) prior to execution
//  [string&] strErrorEntry            :  error file entry
//                                     :  returns execution status, 1 for success; else, 0 for failure;
//         
////////////////////////////////////////////////////////////////////////////////

int ProcessExternalExecute(string strApplicationFilePathName, string strApplicationParameters, string strWorkingDirectory, string& strErrorEntry)
{
	try
	{
		//  Parameters/arguments
		vector<string> vParameters;
		//  Parameters/arguments
		vector<string> vParameter;
		//  Parameters/arguments in execv format
		const char** pParameters = NULL;

		//  If application file path name is not empty
		if (!strApplicationFilePathName.empty())
		{
			SplitString(strApplicationParameters, ';', vParameters);

			for (int nCountP = 0; nCountP < vParameters.size(); nCountP++)
			{
				//  Split parameters
				SplitString(vParameters[nCountP], ' ', vParameter);

				//  Declare parameters in execv format
				pParameters = new const char*[vParameter.size() + 2];

				//  Fill parameters
				if (pParameters != NULL)
				{
					//  First parameter is application file path name
					pParameters[0] = strApplicationFilePathName.c_str();

					//  Iterate application parameters 
					for (int nCount = 0; nCount < vParameter.size(); nCount++)
					{
						// Set char*
						pParameters[nCount + 1] = vParameter[nCount].c_str();
					}
					//  Last parameter is NULL
					pParameters[vParameter.size() + 1] = NULL;
				}

				#ifdef _WIN64
				#else

					//  Child process ID
					pid_t pidChild = -1;
					//  Child process ID
					pid_t pidEnd = -1;
					//  Return status
					int nStatus = -1;

					umask(0007);

					//  Fork child
					pidChild = fork();

					//  If forck succeeded
					if (pidChild >= 0) /* fork succeeded */
					{
						//  Return 0 for the child process
						if (pidChild == 0)
						{
							//  If working directory is not empty
							if (!strWorkingDirectory.empty())
							{
								//  If change working directory failse
								if (!ChangeWorkingFolder(strWorkingDirectory))
								{
									//  Update error entry
									strErrorEntry += "External Command Execution [" + strApplicationParameters + "] Child Process Working Directory [" + strWorkingDirectory + "] Change Failed [" + GetErrorMessage(errno) + "]";

									//  Update console
									//ReportTimeStamp("[ProcessExternalExecute]", "ERROR:  External Command Execution [" + strApplicationParameters + "] Child Process Working Directory [" + strWorkingDirectory + "] Change Failed [" + GetErrorMessage(errno) + "]");

									return 0;
								}
								//else
								//{
								//	char* pCWD = NULL;

								//	pCWD = new char[PATH_MAX];
								//	if (pCWD != NULL)
								//	{
								//		getcwd(pCWD, PATH_MAX);
								//		string strCWD(pCWD);

								//		//  Update console
								//		ReportTimeStamp("[ExternalExecute]", "NOTE:  Current Working Directory is [" + strCWD + "]");
								//	}
								//}
							}

							//  Execute the command, and if fails
							if (execv(strApplicationFilePathName.c_str(), (char **)pParameters) < 0)//, NULL) < 0)
							{
								//  Update error entry
								strErrorEntry += "External Command Execution [" + strApplicationParameters + "] Child Process Working Directory [" + strWorkingDirectory + "] Change Failed [" + GetErrorMessage(errno) + "]";

								//  Update console
								//ReportTimeStamp("[ProcessExternalExecute]", "ERROR:  External Command Execution [" + strApplicationParameters + "] Failed [" + GetErrorMessage(errno) + "]");

								//  Return failure
								return 0;
							}
						}
						//  Else, return is for the parent process
						else
						{
							//  Wait for child exit and get exit status
							while ((wait(&nStatus)) > 0);

							//  Return success
							if (WIFEXITED(nStatus))
							{
								return 1;
							}
							//  Else return error state
							else
							{
								//  Update error entry
								strErrorEntry += "External Command Execution [" + strApplicationParameters + "] Child Process Execution Failed [" + GetErrorMessage(errno) + "]";

								return 0;
							}
						}
					}
					//  Else fork failed
					else
					{
						//  Update error entry
						strErrorEntry += "External Command Execution [" + strApplicationParameters + "] Fork Failed [" + GetErrorMessage(errno) + "]";

						//  Update console
						//ReportTimeStamp("[ProcessExternalExecute]", "ERROR:  External Command Execution [" + strApplicationParameters + "] Fork Failed [" + GetErrorMessage(errno) + "]");

						return 0;
					}

				#endif
			}
			//  Return success
			return 1;
		}
		else
		{
			ReportTimeStamp("[ProcessExternalExecute]", "ERROR:  Application File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ProcessExternalExecute] Exception Code:  " << ex.what() << "\n";
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Splits the input file path name list into multiple lists for MPI, substituting node number for ^NODE^ in input file path name list
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList          :  input file path name list (actual node number replaces ^NODE^ in list, original list path name is this path name with ^NODE^ removed)
//  [string] strOutputListFilePathNameTransform:  output list file path name transform
//  [string] strProjectPathName                :  project path name
//  [int] nMaxBatches                          :  maximum nodes for MPI
//                                             :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ParseFileListByBatch(string strInputFilePathNameList, string strOutputListFilePathNameTransform, string strProjectPathName, int nMaxBatches)
{
	//  List lock
	omp_lock_t lockList;
	//  File path names
	vector<string> vFilePathNames;
	//  List file text
	string strInputListFileText = "";
	//  Output list file texts
	vector<string> vOutputListFileTexts;

	try
	{
		// If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  Get list file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If file path names exist
				if (vFilePathNames.size() > 0)
				{
					//  Resize output list file texts
					vOutputListFileTexts.resize(nMaxBatches);

					//  Initialize time stamp lock
					omp_init_lock(&lockList);

					//  Declare omp parallel
					#pragma omp parallel num_threads(nMaxBatches)
					{
						//  omp loop
						#pragma omp for
						for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
						{
							vOutputListFileTexts[omp_get_thread_num()] += vFilePathNames[lCount] + "\n";

							//omp_set_lock(&lockList);
							//ReportTimeStamp("[ParseFileListByBatch]", "NOTE:  \n" + vFilePathNames[lCount] + "\n" + vOutputListFileTexts[omp_get_thread_num()]);
							//omp_unset_lock(&lockList);

							//  
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Write output lists
					for (int nCountBatches = 0; nCountBatches < nMaxBatches; nCountBatches++)
					{
						//  Output list file path name
						string strOutputListFilePathName = "";

						//  Transform output list file path anem
						strOutputListFilePathName = TransformFilePathName(strInputFilePathNameList, strOutputListFilePathNameTransform, "");
						strOutputListFilePathName = ReplaceInString(strOutputListFilePathName, "^PROJECT_PATH_NAME^", strProjectPathName, false);
						strOutputListFilePathName = ReplaceInString(strOutputListFilePathName, "^BATCH_NUMBER^", ConvertIntToString(nCountBatches), false);
						strOutputListFilePathName = ReplaceInString(strOutputListFilePathName, "^PAD1_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 1, true), false);
						strOutputListFilePathName = ReplaceInString(strOutputListFilePathName, "^PAD2_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 2, true), false);
						strOutputListFilePathName = ReplaceInString(strOutputListFilePathName, "^PAD3_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 3, true), false);
						strOutputListFilePathName = ReplaceInString(strOutputListFilePathName, "^PAD4_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 4, true), false);

						if (!WriteFileText(strOutputListFilePathName, vOutputListFileTexts[nCountBatches]))
						{
							ReportTimeStamp("[ParseFileListByBatch]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
						}
						//else
						//	ReportTimeStamp("[ParseFileListByBatch]", "NOTE:  " + strOutputListFilePathName + " : " + vOutputListFileTexts[nCountBatches].substr(0, 100) + "\n");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ParseFileListByBatch]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ParseFileListByBatch]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ParseFileListByBatch]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ParseFileListByBatch] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Creates an HPC distributed batch job from a file list
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList          :  input file path name list
//  [string] strOutputListFilePathNameTransform:  output list file path name transform
//  [string] strQueueName                      :  PBS queue name
//  [string] strWallTime                       :  PBS walltime [HH:MM:SS]
//  [string] strJobName                        :  PBS job name
//  [string] strAccountID                      :  HPC account ID
//  [string] strApplicationName                :  PBS application name
//  [string] strApplicationParameters          :  Base123 application and parameters
//  [string] strProjectPathName                :  project path name
//  [int] nMaxBatches                          :  maximum batches (one batch per node)
//  [bool] bUseAprun                           :  use 'aprun' syntax, if true; else, use standard qsub syntax
//  [bool] bMakeList                           :  create the list files, if true; else, create batch files, only
//  [int] nMaxProcs                            :  maximum processors for openMP
//                                             :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool CreateDistributedBatchJob(string strInputFilePathNameList, string strOutputListFilePathNameTransform, string strQueueName, string strWallTime, string strJobName, string strAccountID, 
	string strApplicationName, string strApplicationParameters, string strProjectPathName, int nMaxBatches, bool bUseAprun, bool bMakeList, int nMaxProcs)
{
	//  List file text
	string strInputListFileText = "";
	//  File path names extracted from the file path name list file
	vector<string> vFilePathNames;
	//  Batch file path name
	string strBatchFilePathName = "";
	//  Batch file text
	string strBatchFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (((bMakeList) && (!strInputFilePathNameList.empty())) || (!bMakeList))
		{
			//  If output list file path name transform is not empty
			if (!strOutputListFilePathNameTransform.empty())
			{
				//  If queue name is not empty
				if (!strQueueName.empty())
				{
					//  If wall time is not empty
					if (!strWallTime.empty())
					{
						//  If job name is not empty
						if (!strJobName.empty())
						{
							//  If account ID is not empty
							if (!strAccountID.empty())
							{
								//  If application and parameters is not empty
								if (!strApplicationParameters.empty())
								{
									//  If project path name is not empty
									if (!strProjectPathName.empty())
									{
										if(((bMakeList) && (ParseFileListByBatch(strInputFilePathNameList, strOutputListFilePathNameTransform, strProjectPathName, nMaxBatches))) || (!bMakeList))
										{
											//  Iterate and create batches
											for (int nCountBatches = 0; nCountBatches < nMaxBatches; nCountBatches++)
											{
												// Batch job
												string strBatchJob = "";
												// Batch job
												string strBatchJobName = "";
												// Batch application paramaters
												string strBatchApplicationParameters = "";

												//  Transform batch job name
												strBatchJobName = ReplaceInString(strJobName, "^BATCH_NUMBER^", ConvertIntToString(nCountBatches), false);
												strBatchJobName = ReplaceInString(strBatchJobName, "^PAD1_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 1, true), false);
												strBatchJobName = ReplaceInString(strBatchJobName, "^PAD2_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 2, true), false);
												strBatchJobName = ReplaceInString(strBatchJobName, "^PAD3_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 3, true), false);
												strBatchJobName = ReplaceInString(strBatchJobName, "^PAD4_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 4, true), false);

												//  Tranfsorm batch application parameters
												strBatchApplicationParameters = ReplaceInString(strApplicationParameters, "^PROJECT_PATH_NAME^", strProjectPathName, false);
												strBatchApplicationParameters = ReplaceInString(strBatchApplicationParameters, "^DQ^^DQ^", "\"^MT^\"", false);
												strBatchApplicationParameters = ReplaceInString(strBatchApplicationParameters, "^DQ^", "\"", false);
												strBatchApplicationParameters = ReplaceInString(strBatchApplicationParameters, "^BATCH_NUMBER^", ConvertIntToString(nCountBatches), false);
												strBatchApplicationParameters = ReplaceInString(strBatchApplicationParameters, "^PAD1_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 1, true), false);
												strBatchApplicationParameters = ReplaceInString(strBatchApplicationParameters, "^PAD2_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 2, true), false);
												strBatchApplicationParameters = ReplaceInString(strBatchApplicationParameters, "^PAD3_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 3, true), false);
												strBatchApplicationParameters = ReplaceInString(strBatchApplicationParameters, "^PAD4_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 4, true), false);

												//qsub -q standard -l walltime=36:00:00 -l ncpus=360 -j oe -o /work2/projects/BIG/Base123/temp -l job_type=MPI -N v_g_vf_0_1 -A AFHEW34813043 -l application=base123m -V -- 
												strBatchJob += "qsub -q " + strQueueName + " ";
												strBatchJob += "-l walltime=" + strWallTime + " ";
												strBatchJob += "-l ncpus=" + ConvertIntToString(nMaxProcs) + " ";
												strBatchJob += "-j oe -o " + strProjectPathName + " ";
												strBatchJob += "-l job_type=SMP ";
												strBatchJob += "-N " + strBatchJobName + " ";
												strBatchJob += "-A " + strAccountID + " ";
												if(!strApplicationName.empty())
													strBatchJob += "-l application=" + strApplicationName + " ";
												if (bUseAprun)
												{
													strBatchJob += "-V <<EOF\n";
													strBatchJob += "cd\n";
													strBatchJob += "aprun -n " + ConvertIntToString(nMaxProcs) + " ";
													strBatchJob += strBatchApplicationParameters + "\nEOF";
												}
												else
												{
													//  Concatenate batch file path name
													strBatchFilePathName = strProjectPathName + strPathDelimiter;
													strBatchFilePathName += ReplaceInString(strJobName, "^BATCH_NUMBER^", ConvertIntToString(nCountBatches), false);
													strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD1_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 1, true), false);
													strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD2_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 2, true), false);
													strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD3_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 3, true), false);
													strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD4_BATCH_NUMBER^", PadString(ConvertIntToString(nCountBatches), "0", 4, true), false);
													strBatchFilePathName += ".qsub.bash";

													//  Write batch file
													string strWrite = "#!/bin/bash\n" + strBatchApplicationParameters + "\n";
													if (WriteFileText(strBatchFilePathName, strWrite))
													{
														#ifdef _WIN64
														#else
															//  Set the umask
															umask(0007);

															//  S_IRWXU = Read-Write-Execute-Search (Owner)
															//  S_IRWXG = Read-Write-Execute-Search (Group)
															chmod(strBatchFilePathName.c_str(), S_IRWXU | S_IRWXG);

														#endif
													}
													else
													{
														ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  QSub Batch File [" + strBatchFilePathName + "] Write Failed");
													}

													strBatchJob += strBatchFilePathName;
												}
												
												//  Concatenate batch file text
												strBatchFileText += strBatchJob + "\n";
											}

											//  Concatenate batch file path name
											strBatchFilePathName = strProjectPathName + strPathDelimiter;
											strBatchFilePathName += ReplaceInString(strJobName, "^BATCH_NUMBER^", "X", false);
											strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD1_BATCH_NUMBER^", "X", false);
											strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD2_BATCH_NUMBER^", "X", false);
											strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD3_BATCH_NUMBER^", "X", false);
											strBatchFilePathName = ReplaceInString(strBatchFilePathName, "^PAD4_BATCH_NUMBER^", "X", false);
											strBatchFilePathName += ".bash";

											//  Write batch file
											if (WriteFileText(strBatchFilePathName, strBatchFileText))
											{
												#ifdef _WIN64
												#else
													//  Set the umask
													umask(0007);

													//  S_IRWXU = Read-Write-Execute-Search (Owner)
													//  S_IRWXG = Read-Write-Execute-Search (Group)
													chmod(strBatchFilePathName.c_str(), S_IRWXU | S_IRWXG);
												#endif
											}
											else
											{
												ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  Batch File [" + strBatchFilePathName + "] Write Failed");
											}

											return true;
										}
										else
										{
											ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  Input List [" + strInputFilePathNameList + "] Batch Parse Failed");
										}
									}
									else
									{
										ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  Project Path Name is Empty");
									}
								}
								else
								{
									ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  Application and Parameters Transform is Empty");
								}
							}
							else
							{
								ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  HPC Account ID is Empty");
							}
						}
						else
						{
							ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  Job name is Empty");
						}
					}
					else
					{
						ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  PBS Wall Time is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  PBS Queue Name is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  Output List File Path Name Tranform is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[CreateDistributedBatchJob]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [CreateDistributedBatchJob] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Deletes ALL files in a list
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList     :  input file path name list
//  [string] strInputFilePathNameTransform:  input file path name transform (includes string replacements, see help)
//  [string] strErrorFilePathName         :  error file path name
//  [int] nMaxProcs                       :  maximum processors for openMP
//                                        :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListDeleteFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  List file text
	string strInputListFileText = "";
	//  File path names extracted from the file path name list file
	vector<string> vFilePathNames;
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  Get list file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If file path names exist
				if (vFilePathNames.size() > 0)
				{
					//  Initialize errof file vector<string>
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
								ReportTimeStamp("[ListDeleteFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListDeleteFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
								omp_unset_lock(&lockList);
							}

							//  If the file path name is not empty, then proceed
							if (!vFilePathNames[lCount].empty())
							{
								//  Working file path name
								string strWorkingFilePathName = "";

								//  If input file path name transform is not empty
								if (!strInputFilePathNameTransform.empty())
									strWorkingFilePathName = TransformFilePathName(vFilePathNames[lCount], strInputFilePathNameTransform, "");
								else
									strWorkingFilePathName = vFilePathNames[lCount];

								//  Remove file
								if (!RemoveFile(strWorkingFilePathName))
								{
									//  Update error entry
									vErrorEntries[lCount] = vFilePathNames[lCount] + "~Parse Failed~" + GetErrorMessage(errno) + "\n";

									//  Update console
									omp_set_lock(&lockList);
									ReportTimeStamp("[ListDeleteFiles]", "ERROR:  File [" + strInputFilePathNameList + "] Removal Failed [" + GetErrorMessage(errno) + "]");
									omp_unset_lock(&lockList);
								}
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Iterate list file vector and concatenate file
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListDeleteFiles]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListDeleteFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListDeleteFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListDeleteFiles]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListDeleteFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Deletes ALL files in a directory by list
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName      :  input file path name list
//  [string] strDeletePathNameTransform:  delete path name transform (includes string replacements, see help)
//  [string] strErrorFilePathName      :  error file path name
//  [int] nMaxProcs                    :  maximum processors for openMP
//                                     :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListDeleteFilesInDirectory(string strInputFilePathNameList, string strDeletePathNameTransform, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  List file text
	string strInputListFileText = "";
	//  File path names extracted from the file path name list file
	vector<string> vFilePathNames;
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  Get list file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If file path names exist
				if (vFilePathNames.size() > 0)
				{
					//  Initialize errof file vector<string>
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
								ReportTimeStamp("[ListDeleteFilesInDirectory]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListDeleteFilesInDirectory]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
								omp_unset_lock(&lockList);
							}

							//  If the file path name is not empty, then proceed
							if (!vFilePathNames[lCount].empty())
							{
								//  Working file path name
								string strWorkingFilePathName = "";
								//  Command and parameters
								string strCommandParameters = "";

								//  If input file path name transform is not empty
								if (!strDeletePathNameTransform.empty())
									strWorkingFilePathName = TransformFilePathName(vFilePathNames[lCount], strDeletePathNameTransform, "");
								else
									strWorkingFilePathName = vFilePathNames[lCount];

								//  If working path name is not empty
								if (!strWorkingFilePathName.empty())
								{
									//  Concatenate command parameters
									strCommandParameters = "rm " + strWorkingFilePathName;

									//  If command execute fails
									if (SystemExternalExecute("rm", strCommandParameters, vErrorEntries[lCount]) <= 0)
									{
										//  Update error entry
										vErrorEntries[lCount] = vFilePathNames[lCount] + "~Remove Failed~" + strCommandParameters + "~" + GetErrorMessage(errno) + "\n";

										//  Update console
										omp_set_lock(&lockList);
										ReportTimeStamp("[ListDeleteFilesInDirectory]", "ERROR:  File [" + vFilePathNames[lCount] + "] Remove [" + strCommandParameters + "] Failed [" + GetErrorMessage(errno) + "]");
										omp_unset_lock(&lockList);
									}
								}
								else
								{
									//  Update error entry
									vErrorEntries[lCount] = vFilePathNames[lCount] + "~Delete Path Name is Empty\n";

									//  Update console
									omp_set_lock(&lockList);
									ReportTimeStamp("[ListDeleteFilesInDirectory]", "ERROR:  File [" + vFilePathNames[lCount] + "] Delete Path Name is Empty");
									omp_unset_lock(&lockList);
								}
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Iterate list file vector and concatenate file
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListDeleteFilesInDirectory]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListDeleteFilesInDirectory]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListDeleteFilesInDirectory]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListDeleteFilesInDirectory]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListDeleteFilesInDirectory] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Converts a full-path file list to a list containing file name (only)
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList      :  input file path name list
//  [string] strOutputFilePathNameTransform:  output file path name transform (includes string replacements, see help)
//  [string] strOutputListFilePathName     :  output list file path name
//  [int] nMaxProcs                        :  maximum processors for openMP
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListConvertPath(string strInputFilePathNameList, string strOutputFilePathNameTransform, string strOutputListFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Output list entries
	vector<string> vListEntries;
	//  Output list file text
	string strOutputListFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  If output file path name transform is not empty
			if (!strOutputFilePathNameTransform.empty())
			{
				//  If output list file path name is not empty
				if (!strOutputListFilePathName.empty())
				{
					//  Get input file text
					if (GetFileText(strInputFilePathNameList, strInputListFileText))
					{
						//  Split file text into file list
						SplitString(strInputListFileText, '\n', vFilePathNames);

						//  If input file text is not empty
						if (vFilePathNames.size() > 0)
						{
							//  Initialize list file vector<string>
							vListEntries.resize(vFilePathNames.size());

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
										ReportTimeStamp("[ListConvertPath]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
										omp_unset_lock(&lockList);
									}

									//  Update for timestamp every 10,000 files
									if (lCount % 10000 == 0)
									{
										omp_set_lock(&lockList);
										ReportTimeStamp("[ListConvertPath]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
										omp_unset_lock(&lockList);
									}

									//  If the file path name is not empty, then proceed
									if (!vFilePathNames[lCount].empty())
									{
										//  Working file path name
										string strWorkingFilePathName = "";

										//  If input file path name transform is not empty
										if (!strOutputFilePathNameTransform.empty())
											strWorkingFilePathName = TransformFilePathName(vFilePathNames[lCount], strOutputFilePathNameTransform, "");
										else
											strWorkingFilePathName = vFilePathNames[lCount];
										strWorkingFilePathName = ReplaceInString(strWorkingFilePathName, "^ORF_ORIENTATION^", GetORFOrientationFromFilePathName(strWorkingFilePathName), false);

										//  If file name is not empty, list it
										if (!strWorkingFilePathName.empty())
											vListEntries[lCount] = strWorkingFilePathName + "\n";
										//  Else, list error
										else
										{
											//  Update console
											omp_set_lock(&lockList);
											ReportTimeStamp("[ListConvertPath]", "ERROR:  File [" + vFilePathNames[lCount] + "] Name Parse Failed");
											omp_unset_lock(&lockList);
										}
									}
								}
							}

							//  Destroy time stamp lock
							omp_destroy_lock(&lockList);

							//  Iterate list file vector and concatenate file
							for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
							{
								if (!vListEntries[lCount].empty())
									strOutputListFileText += vListEntries[lCount];
							}

							//  Write list file
							if (!strOutputListFilePathName.empty())
							{
								if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
									ReportTimeStamp("[ListConvertPath]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
							}

							return true;
						}
						else
						{
							ReportTimeStamp("[ListConvertPath]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
						}
					}
					else
					{
						ReportTimeStamp("[ListConvertPath]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
					}
				}
				else
				{
					ReportTimeStamp("[ListConvertPath]", "ERROR:  Output List File Path Name is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListConvertPath]", "ERROR:  Output File Path Name Transform is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListConvertPath]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListConvertPath] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Renames ALL files in a list
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName         :  input file path name list
//  [string] strInputFilePathNameTransform:  input file path name transform (includes string replacements, see help)
//  [string] strFilePathNameTransforms    :  transforms describing rename operations (includes string replacements, see help)
//  [string] strErrorFilePathName         :  error file path name
//  [int] nMaxProcs                       :  maximum processors for openMP
//                                        :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListTransformRenameFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strFilePathNameTransforms, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  If file path name transforms is not empty
			if (!strFilePathNameTransforms.empty())
			{
				//  Get input file text
				if (GetFileText(strInputFilePathNameList, strInputListFileText))
				{
					//  Split file text into file list
					SplitString(strInputListFileText, '\n', vFilePathNames);

					//  If input file text is not empty
					if (vFilePathNames.size() > 0)
					{
						//  Initialize errof file vector<string>
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
									ReportTimeStamp("[ListTransformRenameFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
									omp_unset_lock(&lockList);
								}

								//  Update for timestamp every 10,000 files
								if (lCount % 10000 == 0)
								{
									omp_set_lock(&lockList);
									ReportTimeStamp("[ListTransformRenameFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
									omp_unset_lock(&lockList);
								}

								//  If the file path name is not empty, then proceed
								if (!vFilePathNames[lCount].empty())
								{
									//  Output file path name transforms (pluralized)
									string strOutputFilePathNameTransforms = "";
									//  Working file path name
									string strWorkingFilePathName = "";

									//  If input file path name transform is not empty
									if (!strInputFilePathNameTransform.empty())
										strWorkingFilePathName = TransformFilePathName(vFilePathNames[lCount], strInputFilePathNameTransform, "");
									else
										strWorkingFilePathName = vFilePathNames[lCount];

									strOutputFilePathNameTransforms = TransformFilePathName(strWorkingFilePathName, strFilePathNameTransforms, "");

									//  Transform output files
									if (!RenameFilesByTransformSet(strOutputFilePathNameTransforms))
									{
										//  Update error entry
										vErrorEntries[lCount] = vFilePathNames[lCount] + "~Output File Transforms [" + strOutputFilePathNameTransforms + "] Failed\n";

										//  Update console
										omp_set_lock(&lockList);
										ReportTimeStamp("[ListTransformRenameFiles]", "ERROR:  Output File [" + vFilePathNames[lCount] + "] Transforms [" + strOutputFilePathNameTransforms + "] Failed");
										omp_unset_lock(&lockList);
									}
								}
							}
						}

						//  Destroy time stamp lock
						omp_destroy_lock(&lockList);

						//  Iterate list file vector and concatenate file
						for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
						{
							if (!vErrorEntries[lCount].empty())
								strErrorFileText += vErrorEntries[lCount];
						}

						//  Write error file
						if (!strErrorFilePathName.empty())
						{
							//  Write the file
							if (!WriteFileText(strErrorFilePathName, strErrorFileText))
								ReportTimeStamp("[ListTransformRenameFiles]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
						}

						return true;
					}
					else
					{
						ReportTimeStamp("[ListTransformRenameFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[ListTransformRenameFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
				}
			}
			else
			{
				ReportTimeStamp("[ListTransformRenameFiles]", "ERROR:  File Path Name Transform Is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListTransformRenameFiles]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListTransformRenameFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Renames ALL files in a list using match-replace
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName         :  input file path name list
//  [string] strInputFilePathNameTransform:  input file path name transform (includes string replacements, see help)
//  [string] strMatchAndReplace           :  match and replace string set, delimited:  match_1~replace_1&match_2~replace_2&...
//  [string] strErrorFilePathName         :  error file path name
//  [int] nMaxProcs                       :  maximum processors for openMP
//                                        :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListMatchReplaceRenameFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strMatchAndReplace, 	string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  If match-and-replace set is not empty
			if (!strMatchAndReplace.empty())
			{
				//  Get input file text
				if (GetFileText(strInputFilePathNameList, strInputListFileText))
				{
					//  Split file text into file list
					SplitString(strInputListFileText, '\n', vFilePathNames);

					//  If input file text is not empty
					if (vFilePathNames.size() > 0)
					{
						//  Initialize errof file vector<string>
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
									ReportTimeStamp("[ListMatchReplaceRenameFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
									omp_unset_lock(&lockList);
								}

								//  Update for timestamp every 10,000 files
								if (lCount % 10000 == 0)
								{
									omp_set_lock(&lockList);
									ReportTimeStamp("[ListMatchReplaceRenameFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
									omp_unset_lock(&lockList);
								}

								//  If the file path name is not empty, then proceed
								if (!vFilePathNames[lCount].empty())
								{
									//  Working file path name
									string strWorkingFilePathName = "";
									//  Output file path name
									string strOutputFilePathName = "";
									//  Set vector
									vector<string> vMatchAndReplaceSet;

									//  If input file path name transform is not empty
									if (!strInputFilePathNameTransform.empty())
										strWorkingFilePathName = TransformFilePathName(vFilePathNames[lCount], strInputFilePathNameTransform, "");
									else
										strWorkingFilePathName = vFilePathNames[lCount];
									strOutputFilePathName = strWorkingFilePathName;

									//  Split set
									SplitString(strMatchAndReplace, '&', vMatchAndReplaceSet);

									//  If set is not empty
									if (vMatchAndReplaceSet.size() > 0)
									{
										//  Loop set and match/replace
										for (int nCount = 0; nCount < vMatchAndReplaceSet.size(); nCount++)
										{
											//  Match/replace strings
											vector<string> vMatchAndReplace;

											//  Split match/replace
											SplitString(strMatchAndReplace, '~', vMatchAndReplace);

											//  If match/replace is not empty
											if (vMatchAndReplace.size() > 0)
											{
												//  Match and replace
												if (vMatchAndReplace.size() > 1)
													strOutputFilePathName = ReplaceInString(strOutputFilePathName, vMatchAndReplace[0], vMatchAndReplace[1], false);
												else
													strOutputFilePathName = ReplaceInString(strOutputFilePathName, vMatchAndReplace[0], "", false);
											}
										}

										if ((IsFilePresent(strWorkingFilePathName)) && (!RenameFile(strWorkingFilePathName, strOutputFilePathName)))
										{
											//  Update error entry
											vErrorEntries[lCount] = vFilePathNames[lCount] + "~Match-and-Replace Rename File [" + strWorkingFilePathName + " => " + strOutputFilePathName + "] Failed\n";

											//  Update console
											omp_set_lock(&lockList);
											ReportTimeStamp("[ListMatchReplaceRenameFiles]", "ERROR:  Match-and-Replace Rename File [" + strWorkingFilePathName + " => " + strOutputFilePathName + "] Failed");
											omp_unset_lock(&lockList);
										}
									}
								}
							}
						}

						//  Destroy time stamp lock
						omp_destroy_lock(&lockList);

						//  Iterate list file vector and concatenate file
						for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
						{
							if (!vErrorEntries[lCount].empty())
								strErrorFileText += vErrorEntries[lCount];
						}

						//  Write error file
						if (!strErrorFilePathName.empty())
						{
							//  Write the file
							if (!WriteFileText(strErrorFilePathName, strErrorFileText))
								ReportTimeStamp("[ListMatchReplaceRenameFiles]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
						}

						return true;
					}
					else
					{
						ReportTimeStamp("[ListMatchReplaceRenameFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[ListMatchReplaceRenameFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
				}
			}
			else
			{
				ReportTimeStamp("[ListMatchReplaceRenameFiles]", "ERROR:  Match-and-Replace Set is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListMatchReplaceRenameFiles]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListMatchReplaceRenameFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Confirms file output via transforms
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName          :  input file path name list
//  [string] strInputFilePathNameTransform :  input file path name transform (includes string replacements, see help)
//  [string] strOutputFilePathNameTransform:  output file path name transform (includes string replacements, see help)
//  [string] strMissingListFilePathName    :  output list file path name (files missing output)
//  [int] nMaxProcs                        :  maximum processors for openMP
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListConfirmOutputFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strOutputFilePathNameTransform, string strMissingListFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Output list entries
	vector<string> vListEntries;
	//  Output list file text
	string strOutputListFileText = "";

	try
	{
		//  If input file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  If output file path name transforms is not empty
			if (!strOutputFilePathNameTransform.empty())
			{
				//  If output list file path name is not empty
				if (!strMissingListFilePathName.empty())
				{
					//  Get input file text
					if (GetFileText(strInputFilePathNameList, strInputListFileText))
					{
						//  Split file text into file list
						SplitString(strInputListFileText, '\n', vFilePathNames);

						//  If input file text is not empty
						if (vFilePathNames.size() > 0)
						{
							//  Initialize list file vector<string>
							vListEntries.resize(vFilePathNames.size());

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
										ReportTimeStamp("[ListConfirmOutputFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
										omp_unset_lock(&lockList);
									}

									//  Update for timestamp every 10,000 files
									if (lCount % 10000 == 0)
									{
										omp_set_lock(&lockList);
										ReportTimeStamp("[ListConfirmOutputFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
										omp_unset_lock(&lockList);
									}

									//  If the file path name is not empty, then proceed
									if (!vFilePathNames[lCount].empty())
									{
										//  Output file path name
										string strOutputFilePathName = "";
										//  Working file path name
										string strWorkingFilePathName = "";

										//  If input file path name transform is not empty
										if (!strInputFilePathNameTransform.empty())
											strWorkingFilePathName = TransformFilePathName(vFilePathNames[lCount], strInputFilePathNameTransform, "");
										else
											strWorkingFilePathName = vFilePathNames[lCount];

										//  Tranform output file paths
										strOutputFilePathName = TransformFilePathName(strWorkingFilePathName, strOutputFilePathNameTransform, "");
										strOutputFilePathName = ReplaceInString(strOutputFilePathName, "^ORF_ORIENTATION^", GetORFOrientationFromFilePathName(vFilePathNames[lCount]), false);

										//ReportTimeStamp("[ListConfirmOutputFiles]", "NOTE:  Output File Path Name [" + strOutputFilePathName + "]");

										//  Transform output files
										if (!IsFilePresent(strOutputFilePathName))
											vListEntries[lCount] = vFilePathNames[lCount] + "\n";
									}
								}
							}

							//  Destroy time stamp lock
							omp_destroy_lock(&lockList);

							//  Iterate list file vector and concatenate file
							for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
							{
								if (!vListEntries[lCount].empty())
									strOutputListFileText += vListEntries[lCount];
							}

							//  Write list file
							if (!strMissingListFilePathName.empty())
							{
								if (!WriteFileText(strMissingListFilePathName, strOutputListFileText))
									ReportTimeStamp("[ListConfirmOutputFiles]", "ERROR:  Output List File [" + strMissingListFilePathName + "] Write Failed");
							}

							return true;
						}
						else
						{
							ReportTimeStamp("[ListConfirmOutputFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
						}
					}
					else
					{
						ReportTimeStamp("[ListConfirmOutputFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
					}
				}
				else
				{
					ReportTimeStamp("[ListConfirmOutputFiles]", "ERROR:  Output List File Path Name is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListConfirmOutputFiles]", "ERROR:  Output File Path Name Transforms is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListConfirmOutputFiles]", "ERROR:  Input File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListConfirmOutputFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Compares from-list to to-list and outputs a differential file list
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameListFrom :  input file path name list (from) (original list)
//  [string] strInputFilePathNameListTo   :  input file path name list (to) (comparison list)
//  [string] strInputFilePathNameTransform:  to file path name transform (includes string replacements, see help)
//  [string] strDiffMethod                :  vector differentiation method (-msd [multiset diff], -sd [set diff], -vd [vector diff])
//  [string] strOutputListFilePathName    :  output list file path name (differential file list)
//  [int] nMaxProcs                       :  maximum processors for openMP
//                                        :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListCompareDifferentialFiles(string strInputFilePathNameListFrom, string strInputFilePathNameListTo, string strFilePathNameTransform, string strDiffMethod, string strOutputListFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  From input list file text
	string strFromInputListFileText = "";
	//  From file path name vector<string>
	vector<string> vFromFilePathNames;
	//  To input list file text
	string strToInputListFileText = "";
	//  To file path name vector<string>
	vector<string> vToFilePathNames;
	//  Output list entries
	vector<string> vListEntries;
	//  Output list file text
	string strOutputListFileText = "";
	//  From-file is in to-file list, if true
	bool bIsFromPresentInTo = false;

	try
	{
		//  If from-input file path name list is not empty
		if (!strInputFilePathNameListFrom.empty())
		{
			//  If to-input file path name list is not empty
			if (!strInputFilePathNameListTo.empty())
			{
				//  If output list file path name is not empty
				if (!strOutputListFilePathName.empty())
				{
					if ((ConvertStringToLowerCase(strDiffMethod) == "-shell_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-shd") ||
						(ConvertStringToLowerCase(strDiffMethod) == "-list_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-ld") ||
						(ConvertStringToLowerCase(strDiffMethod) == "-multiset_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-msd") || 
						(ConvertStringToLowerCase(strDiffMethod) == "-set_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-sd") ||
						(ConvertStringToLowerCase(strDiffMethod) == "-vector_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-vd"))
					{
						if ((ConvertStringToLowerCase(strDiffMethod) == "-shell_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-shd"))
						{
							//  shell command string
							string strCommand = "";
							//  Error string
							string strError = "";

							//  Format shell command
							strCommand = "bash -c \"comm -13 <(sort " + strInputFilePathNameListFrom + ") <(sort " + strInputFilePathNameListTo + ") > " + strOutputListFilePathName + "\"";
							
							if (SystemExternalExecute(strCommand, "", strError) != 1)
							{
								ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  System Command [" + strCommand + "] Failed; " + strError);
							}
							else
								return true;
						}
						else
						{
							//  Get from-input file text
							if (GetFileText(strInputFilePathNameListFrom, strFromInputListFileText))
							{
								//  Get to-input file text
								if (GetFileText(strInputFilePathNameListTo, strToInputListFileText))
								{
									//  Split from-file text into file list
									SplitString(strFromInputListFileText, '\n', vFromFilePathNames);

									//  Split to-file text into file list
									SplitString(strToInputListFileText, '\n', vToFilePathNames);

									//  If from- and to- input file text is not empty
									if ((vFromFilePathNames.size() > 0) && (vToFilePathNames.size() > 0))
									{
										if (!strFilePathNameTransform.empty())
										{
											//  Initialize time stamp lock
											omp_init_lock(&lockList);

											//  Declare omp parallel
											#pragma omp parallel num_threads(nMaxProcs)
											{
												//  Transform to-list
												//  omp loop
												#pragma omp for
												for (long lCountTo = 0; lCountTo < vToFilePathNames.size(); lCountTo++)
												{
													//  Test max procs
													if (lCountTo == 0)
													{
														omp_set_lock(&lockList);
														ReportTimeStamp("[ListCompareDifferentialFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
														omp_unset_lock(&lockList);
													}

													//  Update for timestamp every 10,000 files
													if (lCountTo % 10000 == 0)
													{
														omp_set_lock(&lockList);
														ReportTimeStamp("[ListCompareDifferentialFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCountTo) + "] [" + vToFilePathNames[lCountTo] + "]");
														omp_unset_lock(&lockList);
													}

													//  If the file path name is not empty, then proceed
													if (!vToFilePathNames[lCountTo].empty())
													{
														//  Transformed to file path name
														string strWorkingFilePathName = "";

														//  Transform to file path name
														if (!strFilePathNameTransform.empty())
															strWorkingFilePathName = TransformFilePathName(vToFilePathNames[lCountTo], strFilePathNameTransform, "");
														else
															strWorkingFilePathName = vToFilePathNames[lCountTo];
														strWorkingFilePathName = ReplaceInString(strWorkingFilePathName, "^ORF_ORIENTATION^", GetORFOrientationFromFilePathName(vToFilePathNames[lCountTo]), false);

														//omp_set_lock(&lockList);
														//ReportTimeStamp("[ListCompareDifferentialFiles]", "NOTE:  " + strWorkingFilePathName);
														//omp_unset_lock(&lockList);

														vToFilePathNames[lCountTo] = strWorkingFilePathName;
													}
												}
											}
										}

										//  Destroy time stamp lock
										omp_destroy_lock(&lockList);

										if ((ConvertStringToLowerCase(strDiffMethod) == "-list_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-ld"))
										{
											// Remove common items from both containers based on the smallest
											if (vFromFilePathNames.size() <= vToFilePathNames.size())
												ListDiffVectors(vFromFilePathNames, vToFilePathNames, vListEntries);
											else
												ListDiffVectors(vToFilePathNames, vFromFilePathNames, vListEntries);
										}
										else if ((ConvertStringToLowerCase(strDiffMethod) == "-multiset_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-msd"))
										{
											// Remove common items from both containers based on the smallest
											if (vFromFilePathNames.size() <= vToFilePathNames.size())
												MultisetDiffVectors(vFromFilePathNames, vToFilePathNames, vListEntries);
											else
												MultisetDiffVectors(vToFilePathNames, vFromFilePathNames, vListEntries);
										}
										else if ((ConvertStringToLowerCase(strDiffMethod) == "-set_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-sd"))
										{
											// Remove common items from both containers based on the smallest
											if (vFromFilePathNames.size() <= vToFilePathNames.size())
												SetDiffVectors(vFromFilePathNames, vToFilePathNames, vListEntries);
											else
												SetDiffVectors(vToFilePathNames, vFromFilePathNames, vListEntries);
										}
										else if ((ConvertStringToLowerCase(strDiffMethod) == "-vector_diff") || (ConvertStringToLowerCase(strDiffMethod) == "-vd"))
										{
											// Remove common items from both containers based on the smallest
											if (vFromFilePathNames.size() <= vToFilePathNames.size())
												VectorDiffVectors(vFromFilePathNames, vToFilePathNames, vListEntries);
											else
												VectorDiffVectors(vToFilePathNames, vFromFilePathNames, vListEntries);
										}

										//  Iterate list file vector and concatenate file
										for (long lCount = 0; lCount < vListEntries.size(); lCount++)
										{
											if (!vListEntries[lCount].empty())
											{
												strOutputListFileText += vListEntries[lCount] + "\n";
											}
										}

										//  Write list file
										if (!strOutputListFilePathName.empty())
										{
											if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
												ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
										}

										return true;
									}
									else if (vToFilePathNames.size() <= 0)
									{
										ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  To-List Input File [" + strInputFilePathNameListTo + "] File Text is Empty");
									}
									else if (vFromFilePathNames.size() <= 0)
									{
										ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  From-List Input File [" + strInputFilePathNameListFrom + "] File Text is Empty");
									}
								}
								else
								{
									ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  To-List Input File [" + strInputFilePathNameListTo + "] Open Failed");
								}
							}
							else
							{
								ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  From-List Input File [" + strInputFilePathNameListFrom + "] Open Failed");
							}
						}
					}
					else
					{
						ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  Diff Method is Unknown - Valid Selections Are (-list_diff [-ld], -multiset_diff [-msd], -set_diff [-sd], -vector_diff [-vd])");
					}
				}
				else
				{
					ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  Output List File Path Name is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  Input To-List File Path Name is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListCompareDifferentialFiles]", "ERROR:  Input From-List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListCompareDifferentialFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}
