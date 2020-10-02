// Base123_FRESH.cpp : Function definitions

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_FRESH Frame Respecting Eularian Shuffler:
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

#include "Base123.h"
#include "Base123_Utilities.h"
#include "Base123_Catalog_Entry.h"
#include "Base123_Catalog.h"
#include "Base123_Shuffler.h"
#include "Base123_FRESH.h"

#include <algorithm>
#include <ctime>
#include <omp.h>

//  Positional base similarities
double m_dBaseSimilarities;

////////////////////////////////////////////////////////////////////////////////
//
//  Compares start/stop structures for sort order
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [structStartStop& ] st1:  start/stop structure to compare
//  [structStartStop& ] st2:  start/stop structure to compare
//                    :  returns true, st1.lStart < st2.lStart
//         
////////////////////////////////////////////////////////////////////////////////

bool CompareStartsAndStops(const structStartStop& st1, const structStartStop& st2) 
{
	try
	{
		return (st1.lStart < st2.lStart);
	}
	catch (exception ex)
	{
		cout << "ERROR [CompareStartsAndStops] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Sorts sequence CDSs into start-stop codon blocks
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [structStartStop&] stSS       :  CDS start/stop to check for duplicate
//  [vector<structStartStop>&] vSS:  sorted starts and stops to search
//                           :  returns true, if duplicated; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool IsCDSStartStopStored(structStartStop& stSS, vector<structStartStop>& vSS)
{
	try
	{
		//  Iterate the vector, check for duplicate entries
		for (int nCount = 0; nCount < vSS.size(); nCount++)
		{
			if ((vSS[nCount].lStart == stSS.lStart) && (vSS[nCount].lStop == stSS.lStop))
				return true;
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [IsCDSStartStopStored] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Parse in-frame CDS molecular start/stop into individual start/stop points
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [long] lLength            :  original sequence length
//  [vector<structCDS>&] vCDSs    :  CDS collection to sort
//  [vector<structStartStop>&] vSS:  starts and stops to compare against
//                           :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ParseStartsAndStops(long lLength, vector<structCDS>& vCDSs, vector<structStartStop>& vSS)
{
	//  Sequence breaks
	int* pBreaks = NULL;
	//  Last start
	long lLastBreak = 1;
	//  Depth
	int nDepth = 0;

	try
	{
		//  Clear output vector
		vSS.clear();

		//  If length is greater than zero
		if(lLength >  0)
		{
			//  Instantiate breaks
			pBreaks = new int[lLength + 1];

			//  If sequence breaks collection is initialized
			if (pBreaks != NULL)
			{
				//  Initialize breaks
				for (long lCountSequence = 0; lCountSequence < lLength + 1; lCountSequence++)
					pBreaks[lCountSequence] = 0;

				//  Set starts and stops from CDS collection
				for (long lCountCDS = 0; lCountCDS < vCDSs.size(); lCountCDS++)
				{
					//  Set CDS start
					if ((vCDSs[lCountCDS].lStart >= 1) && (vCDSs[lCountCDS].lStart <= lLength))
						pBreaks[vCDSs[lCountCDS].lStart]++;

					//  Set CDS stop
					if ((vCDSs[lCountCDS].lStop >= 1) && (vCDSs[lCountCDS].lStop <= lLength))
						pBreaks[vCDSs[lCountCDS].lStop]--;
				}

				//  Iterate breaks and set output starts/stop (+1 because NCBI is 1-based index, inclusive on both ends)
				for (long lCountSequence = 1; lCountSequence <= lLength; lCountSequence++)
				{
					//  If break or end of sequence
					if (((pBreaks[lCountSequence] != 0) || (lCountSequence == lLength)) && (lCountSequence != lLastBreak))
					{
						//  Start/stop to add
						structStartStop stAdd;

						//  Introns are non-inclusive at either end
						if (nDepth == 0)
						{
							//  Set start and stop accordingly
							stAdd.lStart = lLastBreak;
							if (lCountSequence == lLength)
								stAdd.lStop = lCountSequence;
							else
								stAdd.lStop = lCountSequence - 1;
							
							//  Set last break
							lLastBreak = lCountSequence;
						}
						//  Exons are inclusive at BOTH ends
						else
						{
							//  Set start and stop accordingly
							stAdd.lStart = lLastBreak;
							stAdd.lStop = lCountSequence;

							//  Set last break
							lLastBreak = lCountSequence + 1;
						}
						stAdd.nDepth = nDepth;

						//  If start/stop is Not duplicate, add start/stop
						//if(!AddCDSStartStop(stAdd, vSS))
						//	ReportTimeStamp("[ParseStartsAndStops]", "ERROR:  Start/stop Addition Failed");
						if (!IsCDSStartStopStored(stAdd, vSS))
							vSS.push_back(stAdd);
					}

					//  Set depth
					nDepth += pBreaks[lCountSequence];
				}

				//  Sort output starts/stops
				sort(vSS.begin(), vSS.end(), CompareStartsAndStops);

				//  If last stop is Not end of sequence, append a final start/stop
				if (vSS[vSS.size() - 1].lStop != lLength)
				{
					//  Start/stop to add, depth = 0
					structStartStop stAdd;
					stAdd.lStart = vSS[vSS.size() - 1].lStop + 1;
					stAdd.lStop = lLength;
					stAdd.nDepth = 0;

					//  Add last start/stop
					if (!IsCDSStartStopStored(stAdd, vSS))
						vSS.push_back(stAdd);
				}

				return true;
			}
			else
			{
				ReportTimeStamp("[ParseStartsAndStops]", "ERROR:  Sequence Breaks Initialization Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ParseStartsAndStops]", "ERROR:  Length Must be Greater Than Zero");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ParseStartsAndStops] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  shuffles a BIG .fa format file into individual shuffle file(s)
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName:  .fa file path name to process
//  [CBase123_Catalog&] bCatalog :  catalog to process
//  [int] nOutputCount           :  number of shuffled file(s) to produce
//  [string&] strListEntry       :  list file entry
//  [string&] strErrorEntry      :  error file entry
//                              :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool shuffleFAFile(string strInputFilePathName, CBase123_Catalog& bCatalog, int nOutputCount, string& strListEntry, string& strErrorEntry)
{
	//  FA file text
	string strInputFileText = "";
	//  FA file text vector<string>
	vector<string> vInputFileText;
	//  FA file accession
	string strAccession = "";
	//  FA sequence
	string strSequence = "";
	//  Path delimiter
	char chrPathDelimiter = strPathDelimiter;
	
	try
	{
		//  If file text is not empty
		if (!strInputFilePathName.empty())
		{
			//  If output count greater than zero
			if (nOutputCount > 0)
			{
				//  Get .fa sequence
				if (GetFileText(strInputFilePathName, strInputFileText))
				{
					//  Split file text into header and sequence
					SplitString(strInputFileText, '\n', vInputFileText);
					
					//  If file text is properly set
					if (vInputFileText.size() == 2)
					{
						//  Get accession
						strAccession = GetAccessionFromFileHeader(vInputFileText[0]);

						//  If accession is not empty
						if(!strAccession.empty())
						{
							//  Get sequence
							strSequence = vInputFileText[1];

							//  If sequence is not empty
							if (!strSequence.empty())
							{
								//  CDS collection pointer
								vector<structCDS> vCDSs;

								//  Get CDS collection by accession
								if (bCatalog.GetCDSCollectionByAccession(strAccession, vCDSs))
								{
									//  Sorted starts and stops
									vector<structStartStop> vStartsStops;

									//  If sort starts and stops succeeds
									if (ParseStartsAndStops((long)strSequence.length(), vCDSs, vStartsStops))
									{
										//  File path name base
										string strBaseFilePathName = "";

										//  Get file path name base
										strBaseFilePathName = GetBasePath(strInputFilePathName) + chrPathDelimiter + GetFileNameExceptLastExtension(strInputFilePathName);

										//  Iterate through output count and create the shuffle files
										for (int nCount = 0; nCount < nOutputCount; nCount++)
										{
											//  FA shuffle
											CBase123_Shuffler bshuffle;
											//  shuffled sequence
											string strshuffle = "";

											//  shuffle the sequence
											strshuffle = bshuffle.shuffleSequence(strSequence, vStartsStops);

											//  Verify shuffle quality
											if ((!strshuffle.empty()) && (strshuffle.length() == strSequence.length()))
											{
												//  Output file text
												string strOutputFileText = "";
												//  Output file path name
												string strOutputFilePathName = "";

												//  Concatenate shuffle file
												strOutputFileText = vInputFileText[0] + "\n" + strshuffle;

												//  Concatenate output file path name
												strOutputFilePathName = strBaseFilePathName + ".sh_" + ConvertIntToString(nCount) + ".fa";

												if (WriteFileText(strOutputFilePathName, strOutputFileText))
													strListEntry += GetFileName(strOutputFilePathName) + "\n";
												else
												{
													//  Concatenate error entry
													strErrorEntry += strOutputFilePathName + "~Write Failed\n";

													ReportTimeStamp("[shuffleFAFile]", "ERROR:  shuffle File [" + strOutputFilePathName + "] Write Failed");
												}
											}
											else
											{
												//  Concatenate error entry
												strErrorEntry += strAccession + "~Length Check Failed\n";

												ReportTimeStamp("[shuffleFAFile]", "ERROR:  Accession [" + strAccession + "] shuffle Length Check Failed [i/o] [" + ConvertLongToString((long)strSequence.length()) + "/" + ConvertLongToString((long)strshuffle.length()) + "]");
											}
										}

										return true;
									}
									else
									{
										//  Concatenate error entry
										strErrorEntry += strAccession + "~CDS Parse Failed\n";

										ReportTimeStamp("[shuffleFAFile]", "ERROR:  Accession [" + strAccession + "] CDS Parse Failed");
									}
								}
								else
								{
									//  Concatenate error entry
									strErrorEntry += strAccession + "~Catalog Search Failed\n";

									ReportTimeStamp("[shuffleFAFile]", "ERROR:  Catalog Accession [" + strAccession + "] Search Failed");
								}
							}
							else
							{
								//  Concatenate error entry
								strErrorEntry += strAccession + "~Empty Sequence\n";

								ReportTimeStamp("[shuffleFAFile]", "ERROR:  Input .fa File [" + strInputFilePathName + "] Sequence is Empty");
							}
						}
						else
						{
							//  Concatenate error entry
							strErrorEntry += strInputFilePathName + "~Empty Accession\n";

							ReportTimeStamp("[shuffleFAFile]", "ERROR:  Input .fa File [" + strInputFilePathName + "] Accession is Empty");
						}
					}
					else
					{
						//  Concatenate error entry
						strErrorEntry += strInputFilePathName + "~Format Error\n";

						ReportTimeStamp("[shuffleFAFile]", "ERROR:  Input .fa File [" + strInputFilePathName + "] is Not Properly Formatted");
					}
				}
				else
				{
					//  Concatenate error entry
					strErrorEntry += strInputFilePathName + "~Open Failed\n";

					ReportTimeStamp("[shuffleFAFile]", "ERROR:  Input .fa File [" + strInputFilePathName + "] Open Failed");
				}
			}
			else
			{
				ReportTimeStamp("[shuffleFAFile]", "ERROR:  Output shuffle File Count Must be Greater Than Zero");
			}
		}
		else
		{
			ReportTimeStamp("[shuffleFAFile]", "ERROR:  Input .fa File Path Name List is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [shuffleFAFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Processes a .fa file list into the indicated number of shuffled output file(s)
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList     :  .fa file path name list to process
//  [string] strInputFilePathNameTransform:  input file path name transform (includes string replacements, see help)
//  [string] strCatalogFilePathName       :  catalog file path name to process
//  [int] nMaxCatalogSize                 :  maximum catalog size expected
//  [int] nOutputCount                    :  number of shuffled file(s) to produce
//  [string] strOutputListFilePathName    :  output list file path name
//  [string] strErrorFilePathName         :  error file path name
//  [int] nMaxProcs                       :  maximum processors for openMP
//  [string] strOutputFolderPathName      :  output folder path name [optional]
//                                       :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListshuffleFAFiles(string strInputFilePathNameList, string strInputFilePathNameTransform, string strCatalogFilePathName, int nMaxCatalogSize, int nOutputCount, 
	string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  Input file path name list file text
	string strInputListFileText = "";
	//  File path name vector<string>
	vector<string> vFilePathNames;
	//  Output list entries
	vector<string> vListEntries;
	//  List file text
	string strOutputListFileText = "";
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		//  Seed the randomizer
		srand((uint16_t)time(NULL));

		//  If file path name list is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  If catalog file path name is not empty
			if (!strCatalogFilePathName.empty())
			{
				//  If max catalog size is greater than zero
				if(nMaxCatalogSize > 0)
				{
					//  Catalog to process
					CBase123_Catalog bCatalog(nMaxCatalogSize);

					//  If catalog opens
					if (bCatalog.OpenCatalog(strCatalogFilePathName))
					{
						//  Parse individual container file
						if (GetFileText(strInputFilePathNameList, strInputListFileText))
						{
							//  Split file text into file list
							SplitString(strInputListFileText, '\n', vFilePathNames);

							//  If file path names exist
							if (vFilePathNames.size() > 0)
							{
								//  Initialize list file vector<string>
								vListEntries.resize(vFilePathNames.size());

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
											ReportTimeStamp("[ListshuffleFAFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
											omp_unset_lock(&lockList);
										}

										//  Update for timestamp every 10,000 files
										if (lCount % 10000 == 0)
										{
											omp_set_lock(&lockList);
											ReportTimeStamp("[ListshuffleFAFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
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

											if (!shuffleFAFile(strWorkingFilePathName, bCatalog, nOutputCount, vListEntries[lCount], vErrorEntries[lCount]))
											{
												vErrorEntries[lCount] = strWorkingFilePathName + "~shuffle Failed\n";

												omp_set_lock(&lockList);
												ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  .fa File [" + strWorkingFilePathName + "] shuffle Failed");
												omp_unset_lock(&lockList);
											}
										}
									}
								}

								//  Destroy time stamp lock
								omp_destroy_lock(&lockList);

								//  Iterate list/error entries and concatenate file text
								for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
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
										ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  shuffle List File [" + strOutputListFilePathName + "] Write Failed");
								}

								//  Write error file
								if (!strErrorFilePathName.empty())
								{
									//  Write the file
									if (!WriteFileText(strErrorFilePathName, strErrorFileText))
										ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  shuffle Error File [" + strErrorFilePathName + "] Write Failed");
								}

								return true;
							}
							else
							{
								ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  Input File [" + strInputFilePathNameList + "] List is Empty");
							}
						}
						else
						{
							ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  Input File [" + strInputFilePathNameList + "] Text is Empty");
						}

						//  Close catalog
						bCatalog.CloseCatalog();
					}
					else
					{
						ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  Catalog [" + strCatalogFilePathName + "] Open Failed");
					}
				}
				else
				{
					ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  Maximum Catalog Size Must be Greater Than Zero");
				}
			}
			else
			{
				ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  Catalog File Path Name is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[ListshuffleFAFiles]", "ERROR:  Input .fna/.fa File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListshuffleFAFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}
