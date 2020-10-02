// Base123_NCBI_Mgr.cpp : Defines the entry point for the console application.

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

#include "Base123.h"
#include "Base123_NCBI_Mgr.h"
#include "Base123_Utilities.h"
#include "Base123_Catalog_Entry.h"
#include "Base123_Catalog.h"

#include <sstream>
#include <omp.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN64
#else
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#endif


////////////////////////////////////////////////////////////////////////////////
//
//  Creates a .ORF BIG Format File Based on File Name
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strORFFilePathName:  .ORF file path name (should be full path name)
//                             :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool CreateORFFile(string strORFFilePathName)
{
	try
	{
		//  NCBI .fa file path name
		string strFAFilePathName = "";
		//  NCBI .fa file text
		string strFAFileText = "";
		//  ORF file text
		string strORFFileText = "";
		//  Sequence
		string strSequence = "";
		//  ORF Orientation and frame (F1,F2,F3,R1,R2,R3)
		string strOrientation = "";
		//  ORF start
		long lStart = 0;
		//  ORF start
		long lStop = 0;
		//  ORF length
		long lLength = 0;
		//  ORF sequence
		string strORFSequence = "";

		//  If the .ORF is properly set
		if ((!strORFFilePathName.empty()))
		{
			//  Get ORF length
			if (ParseORFFilePathName(strORFFilePathName, strOrientation, lStart, lStop, lLength))
			{
				//  Get .fa file path name
				strFAFilePathName = ConvertORFToFAFilePathName(strORFFilePathName);

				// If .fa file path name is not empty
				if (!strFAFilePathName.empty())
				{
					//  If get the .fa file text
					if(GetFileText(strFAFilePathName, strFAFileText))
					{
						//  Get NCBI sequence
						strSequence = GetSequenceFromFAFile(strFAFileText);

						//  If NCBI sequence is not empty
						if (!strSequence.empty())
						{
							//  If reverse orientation, get compliment
							if (ConvertStringToLowerCase(strOrientation).substr(0, 1) == "r")
								strSequence = ConvertToReverseCompliment(strSequence);

							//  Get ORF sequence
							strORFSequence = strSequence.substr(lStart, lLength);

							//  If ORF sequence is not empty
							if (!strORFSequence.empty())
							{
								//  Concatenate ORF file text (remove .suffix and replace remaining . with _ to form extended BIG extension)
								strORFFileText = ">_\n" + strORFSequence;

								//  Write ORF file
								if (!WriteFileText(strORFFilePathName, strORFFileText))
								{
									//  Update console
									ReportTimeStamp("[CreateORFFile]", "ERROR:  .ORF File [" + strORFFilePathName + "] Write Failed");
								}
								else
									return true;
							}
							else
							{
								//  Update console
								ReportTimeStamp("[CreateORFFile]", "ERROR:  .ORF Sequence for [" + strFAFilePathName + "] is Empty");
							}
						}
						else
						{
							//  Update console
							ReportTimeStamp("[CreateORFFile]", "ERROR:  .FA File Path Name [" + strFAFilePathName + "] Sequence Retrieval Failed");
						}
					}
					else
					{
						//  Update console
						ReportTimeStamp("[CreateORFFile]", "ERROR:  .FA File [" + strFAFilePathName + "] Open Failed");
					}
				}
				else
				{
					//  Update console
					ReportTimeStamp("[CreateORFFile]", "ERROR:  .FA File Path Name [" + strORFFilePathName + "] is Empty");
				}
			}
			else
			{
				//  Update console
				ReportTimeStamp("[CreateORFFile]", "ERROR:  .ORF File Path Name [" + strORFFilePathName + "] Parse Failed");
			}
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [CreateORFFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Parses a .gbk container file into individual files
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathName          :  .gbk file path name to process
//  [string] strOutputFilePathNameTransform:  output folder path name [optional]
//  [string&] strListEntry                 :  list entry
//  [string&] strErrorEntry                :  error entry
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ParseGBKContainerFile(string strInputFilePathName, string strOutputFilePathNameTransform, string& strListEntry, string& strErrorEntry)
{
	//  The container file text
	stringstream ssContainerFileText;
	//  Input file text line
	string strLine = "";
	//  The .gbk file accession
	string strAccession = "";
	//  The output .gbk file path name
	string strGBKFilePathName = "";
	//  The gbk file text
	string strGBKFileText = "";
	//  Line counter
	long lCountLines = 0;

	try
	{
		//  If file text is not empty
		if (!strInputFilePathName.empty())
		{
			//  Parse individual container file
			if (GetFileText(strInputFilePathName, ssContainerFileText))
			{
				//  Read container and parse to file
				while (getline(ssContainerFileText, strLine))
				{
					//  Increment line count (error reporting)
					lCountLines++;

					//  End of file
					if (strLine.substr(0, 2) == "//")
					{
						//  Complete the file
						strGBKFileText += "//";

						//  If file path name is not empty
						if (!strGBKFilePathName.empty())
						{
							//  Write the file
							if (WriteFileText(strGBKFilePathName, strGBKFileText))
								strListEntry += GetFileName(strGBKFilePathName) + "\n";
							else
							{
								strErrorEntry += strGBKFilePathName + "~Write Failed\n";

								ReportTimeStamp("[ParseGBKContainerFile]", "ERROR:  Output .gbk File [" + strGBKFilePathName + "] Write Failed");
							}
						}
						else
						{
							ReportTimeStamp("[ParseGBKContainerFile]", "ERROR:  Output .gbk File [" + strAccession + "] / [" + ConvertLongToString(lCountLines) + "] File Path Name is Empty");
						}

						//  Clear the file
						strGBKFileText = "";
						strAccession = "";
						strGBKFilePathName = "";
}
					//  Concatenate file text
					else
						strGBKFileText += strLine + '\n';

					//  LOCUS line, get accession
					if (ConvertStringToLowerCase(strLine.substr(0, 5)) == "locus")
					{
						//  LOCUS vector<string>
						vector<string> vLocus;

						//  Split locus to get accession
						SplitString(strLine, ' ', vLocus);

						//  If locus vector<string> is not empty
						if (vLocus.size() >= 2)
						{
							//  Get Accession
							strAccession = vLocus[1];

							//  Format accession for file path name
							ReplaceInString(strAccession, ".", "_", false);

							//  If input file path name transform is not empty
							if (!strOutputFilePathNameTransform.empty())
								strGBKFilePathName = TransformFilePathName(strAccession + ".", strOutputFilePathNameTransform, "gbk");
						}
						else
						{
							strErrorEntry += strGBKFilePathName + "~Locus Format Error~" + strLine + "\n";

							ReportTimeStamp("[ParseGBKContainerFile]", "ERROR:  Output .gbk File [" + ConvertLongToString(lCountLines) + "] Locus [" + strLine + "] is Not Properly Formatted");
						}
					}

					//  Clear the line
					strLine = "";
				}

				return true;
			}
			else
			{
				ReportTimeStamp("[ParseGBKContainerFile]", "ERROR:  Input .gbk File [" + strInputFilePathName + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ParseGBKContainerFile]", "ERROR:  Input .gbk File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ParseGBKContainerFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
						}

////////////////////////////////////////////////////////////////////////////////
//
//  Parses ORFs to file (or virtual ORF vector)
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strAccession     :  NCBI accession number
//  [string] strBasePathName  :  output file base path name
//  [string] strSequence      :  sequence to parse
//  [string] strDirection     :  sequence direction
//  [string] strFrameNumber   :  frame number
//  [string] strStarts        :  starts ('|' delimited)
//  [string] strStops         :  stops ('|' delimited)
//  [bool] bIsVirtualParse    :  virtual parse to vORFs vector, if true; else, parse to file(s)
//  [vector<structORF>&] vORFs:  virtual parse ORF structure vector (filled only when bIsVirtualParse is true)
//  [string&] strListEntry    :  list entry
//  [string&] strErrorEntry   :  error file entry
//                            :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ParseORFs(string strAccession, string strBasePathName, string strSequence, string strDirection, string strFrameNumber, string strStarts, string strStops,
	int nMinORFLength, int nMaxORFLength, bool bIsVirtualParse, vector<structORF>& vORFs, string& strListEntry, string& strErrorEntry)
{
	//  Starts vector
	vector<int> vStarts;
	//  Stops vector
	vector<int> vStops;

	try
	{
		//  If required input is not empty
		if ((!strBasePathName.empty()) && (!strSequence.empty()) && (!strDirection.empty()) && (!strFrameNumber.empty()) && (nMinORFLength > 0) && (nMaxORFLength > 0))
		{
			// Fill starts vector
			ParseStringToIntVector(strStarts, '|', vStarts);

			// If starts is set
			if (vStarts.size() > 0)
			{
				// Fill stops vector
				ParseStringToIntVector(strStops, '|', vStops);

				//  If stops is set
				if (vStops.size() > 0)
				{
					//  Process, starts
					for (int nCountStarts = 0; nCountStarts < vStarts.size(); nCountStarts++)
					{
						//  Process, stops
						for (int nCountStops = 0; nCountStops < vStops.size(); nCountStops++)
						{
							//  Only those stops greater than starts
							if (vStarts[nCountStarts] < vStops[nCountStops])
							{
								//  ORF length
								int nLength = vStops[nCountStops] - vStarts[nCountStarts];

								//  Must be within length filter specs
								if ((nLength >= nMinORFLength) && (nLength <= nMaxORFLength))
								{
									//  ORF file path name
									string strORFFilePathName = "";

									//  Start string
									string strStart = ConvertIntToString(vStarts[nCountStarts]);

									//  Stop string
									string strStop = ConvertIntToString(vStops[nCountStops]);

									//  ORF sequence
									string strORF = strSequence.substr(vStarts[nCountStarts], nLength);

									//  If virtual parse
									if (bIsVirtualParse)
									{
										//  Virtual ORF
										structORF stGet;

										//  Initiated ORF
										stGet.strName = strDirection + strFrameNumber + "_" + strStart + "_" + strStop;
										stGet.strSequence = strORF;

										//  If both ORF features are set, push back the ORF
										if ((!stGet.strName.empty()) && (!stGet.strSequence.empty()))
											vORFs.push_back(stGet);
									}
									//  Else, parse to file(s)
									else
									{
										//  ORF file path name, contains <output_folder>/<temp>/<accession_#>
										strORFFilePathName = strBasePathName + "." + strDirection + strFrameNumber + "_" + strStart + "_" + strStop + ".ORF";

										//  Output file text
										string strOutFileText = ">" + strAccession + "\n" + strORF;
										//string strOutFileText = ">_\n" + strORF;

										//  Write the ORF file
										if (WriteFileText(strORFFilePathName, strOutFileText))
											strListEntry += GetFileName(strORFFilePathName) + "\n";
										else
										{
											strErrorEntry += strORFFilePathName + "~Write Failed\n";

											ReportTimeStamp("[ParseORFs]", "ERROR:  ORF File [" + strORFFilePathName + "] Write Failed");
										}
									}
								}

								//  First stop is last stop for each start
								break;
							}
						}
					}
				}
				//else
				//{
				//	ReportTimeStamp("[ParseORFs]", "ERROR:  Stops Container is Not Set");
				//}
			}
			//else
			//{
			//	ReportTimeStamp("[ParseORFs]", "ERROR:  Starts Container is Not Set");
			//}

			return true;
		}
		else if (strBasePathName.empty())
		{
			ReportTimeStamp("[ParseORFs]", "ERROR:  Output File(s) Base Path Name is Empty");
		}
		else if (!strSequence.empty())
		{
			ReportTimeStamp("[ParseORFs]", "ERROR:  Sequence is Empty");
		}
		else if (strDirection.empty())
		{
			ReportTimeStamp("[ParseORFs]", "ERROR:  Direction is Empty");
		}
		else if (strFrameNumber.empty())
		{
			ReportTimeStamp("[ParseORFs]", "ERROR:  Frame Number is Empty");
		}
		else if (nMinORFLength <= 0)
		{
			ReportTimeStamp("[ParseORFs]", "ERROR:  Minimum Sequence Filter Length is Not Set");
		}
		else if (nMaxORFLength <= 0)
		{
			ReportTimeStamp("[ParseORFs]", "ERROR:  Maximum Sequence Filter Length is Not Set");
		}
								}
	catch (exception ex)
	{
		cout << "ERROR [ParseORFs] Exception Code:  " << ex.what() << "\n";
	}

	return false;
							}

////////////////////////////////////////////////////////////////////////////////
//
//  Parses the pORF file into individual ORF files
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strPORFFilePathName:  input file path name
//  [string] strORFFolderName   :  ORF output folder
//  [int] nMinORFLength         :  minimum sequence length for ORF parse
//  [int] nMaxORFLength         :  maximum sequence length for ORF parse
//  [bool] bIsVirtualParse      :  virtual parse to vORFs vector, if true; else, parse to file(s)
//  [vector<structORF>&] vORFs  :  virtual parse ORF structure vector (filled only when bIsVirtualParse is true)
//  [string&] strListEntry      :  list entry
//  [string&] strErrorEntry     :  error entry
//                              :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ParsePORFtoORF(string strPORFFilePathName, string strORFFolderName, int nMinORFLength, int nMaxORFLength, bool bIsVirtualParse, vector<structORF>& vORFs,
	string& strListEntry, string& strErrorEntry)
{
	//  Return state
	bool bReturnState = true;
	//  pORF file text
	string strPORFFileText = "";
	//  Original accession
	string strAccession = "";
	//  Original FA file path name
	string strFAFilePathName = "";
	//  Original FA file text to parse
	string strFAFileText = "";
	//  Forward sequence to parse
	string strForward = "";
	//  Reverse sequence to parse
	string strReverse = "";
	//  Base path name for ORF files
	string strORFBasePathName = "";
	//  File vector<string>
	vector<string> vPORFFile;
	//  Path delimiter
	char chrPathDelimiter = strPathDelimiter;

	try
	{
		//  If the input file path name is not empty
		if (!strPORFFilePathName.empty())
		{
			//  If input file open
			if (GetFileText(strPORFFilePathName, strPORFFileText))
			{
				//  If the input file text is not empty
				if (!strPORFFileText.empty())
				{
					//  If minimum sequence length filter is greater than zero
					if (nMinORFLength > 0)
					{
						//  If maximum sequence length filter is greater than zero
						if (nMaxORFLength > 0)
						{
							// Get the accession from the pORF file text
							strAccession = GetAccessionFromFileHeader(strPORFFileText);

							//  If the accession is not empty
							if (!strAccession.empty())
							{
								//  Get original FA file path name
								strFAFilePathName = GetBasePath(strPORFFilePathName) + chrPathDelimiter + GetFileNameExceptLastExtension(strPORFFilePathName) + ".fa";

								//  If the original FA file path name is not empty
								if (!strFAFilePathName.empty())
								{
									//  Get original FA file text
									if (GetFileText(strFAFilePathName, strFAFileText))
									{
										//  Strip fa file header to produce forward sequence, only
										strForward = strFAFileText.substr(strFAFileText.find("\n", 0) + 1, strFAFileText.length());

										//  If forward sequence is not empty
										if (!strForward.empty())
										{
											//  Get reverse compliment
											strReverse = ConvertToReverseCompliment(strForward);

											//  If reverse sequence is not empty
											if (!strReverse.empty())
											{
												//  Get ORF base path name
												strORFBasePathName = GetBasePath(strFAFilePathName) + strPathDelimiter;
												strORFBasePathName += strORFFolderName + strPathDelimiter;
												strORFBasePathName += GetBaseFileName(strFAFilePathName);

												//  If base path name is not empty
												if (!strORFBasePathName.empty())
												{
													//  Split the pORF file into vector<string>
													SplitStringAllowEmptyEntries(strPORFFileText, "\n", vPORFFile);

													//  If file is set, should be thirteen lines (header + six start/stop line pairs for both forward and reverse), may have trailing line-feed
													if (vPORFFile.size() >= 13)
													{
														//  Parse forward frame 1
														if (!ParseORFs(strAccession, strORFBasePathName, strForward, "F", "1", vPORFFile[1], vPORFFile[2], nMinORFLength, nMaxORFLength, bIsVirtualParse, vORFs, strListEntry, strErrorEntry))
															bReturnState = false;

														//  Parse forward frame 2
														if (!ParseORFs(strAccession, strORFBasePathName, strForward, "F", "2", vPORFFile[3], vPORFFile[4], nMinORFLength, nMaxORFLength, bIsVirtualParse, vORFs, strListEntry, strErrorEntry))
															bReturnState = false;

														//  Parse forward frame 3
														if (!ParseORFs(strAccession, strORFBasePathName, strForward, "F", "3", vPORFFile[5], vPORFFile[6], nMinORFLength, nMaxORFLength, bIsVirtualParse, vORFs, strListEntry, strErrorEntry))
															bReturnState = false;

														//  Parse reverse frame 1
														if (!ParseORFs(strAccession, strORFBasePathName, strReverse, "R", "1", vPORFFile[7], vPORFFile[8], nMinORFLength, nMaxORFLength, bIsVirtualParse, vORFs, strListEntry, strErrorEntry))
															bReturnState = false;

														//  Parse reverse frame 2
														if (!ParseORFs(strAccession, strORFBasePathName, strReverse, "R", "2", vPORFFile[9], vPORFFile[10], nMinORFLength, nMaxORFLength, bIsVirtualParse, vORFs, strListEntry, strErrorEntry))
															bReturnState = false;

														//  Parse forwreverseard frame 3
														if (!ParseORFs(strAccession, strORFBasePathName, strReverse, "R", "3", vPORFFile[11], vPORFFile[12], nMinORFLength, nMaxORFLength, bIsVirtualParse, vORFs, strListEntry, strErrorEntry))
															bReturnState = false;

														return bReturnState;
													}
													else
													{
														ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  ORF File [" + strFAFilePathName + "] is Not Set or is Incomplete");
													}
												}
												else
												{
													ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Base ORF File [" + strFAFilePathName + "] Path Name is Empty");
												}
											}
											else
											{
												ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Reverse sequence [" + strFAFilePathName + "] is Empty");
											}
										}
										else
										{
											ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Forward sequence [" + strFAFilePathName + "] is Empty");
										}
									}
									else
									{
										ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Original FA File [" + strFAFilePathName + "] Open Failed");
									}
								}
								else
								{
									ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Original FA File [" + strAccession + "] Path Name is Empty");
								}
							}
							else
							{
								ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Accession is Empty");
							}
						}
						else
						{
							ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Maximum Sequence Length Filter is Not Set");
						}
					}
					else
					{
						ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Minimum Sequence Length Filter is Not Set");
					}
				}
				else
				{
					ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Input pORF File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Input pORF File [" + strPORFFilePathName + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ParsePORFtoORF]", "ERROR:  Input pORF File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ParsePORFtoORF] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Processes file text to ORF file; input file text must be in fa format
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strFAFilePathName      :  original fa file path name
//  [int] nMinORFLength             :  minimum sequence length for ORF parse
//  [int] nMaxORFLength             :  maximum sequence length for ORF parse
//  [string&] strListEntry          :  output list file entry
//  [string&] strErrorEntry         :  error file entry
//                                  :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ParseFAtoPORF(string strFAFilePathName, int nMinORFLength, int nMaxORFLength, string& strListEntry, string& strErrorEntry)
{
	//  FA file text
	string strFAFileText = "";
	//  Header
	string strHeader = "";
	//  Forward sequence
	string strForward = "";
	//  Reverse sequence
	string strReverse = "";
	//  Output file text, forward frame 1, starts
	string strFF1Starts = "";
	//  Output file text, forward frame 2, starts
	string strFF2Starts = "";
	//  Output file text, forward frame 3, starts
	string strFF3Starts = "";
	//  Output file text, reverse frame 1, starts
	string strRF1Starts = "";
	//  Output file text, reverse frame 2, starts
	string strRF2Starts = "";
	//  Output file text, reverse frame 3, starts
	string strRF3Starts = "";
	//  Output file text, forward frame 1, stops
	string strFF1Stops = "";
	//  Output file text, forward frame 2, stops
	string strFF2Stops = "";
	//  Output file text, forward frame 3, stops
	string strFF3Stops = "";
	//  Output file text, reverse frame 1, stops
	string strRF1Stops = "";
	//  Output file text, reverse frame 2, stops
	string strRF2Stops = "";
	//  Output file text, reverse frame 3, stops
	string strRF3Stops = "";
	//  The pORF file path name
	string strPORFFilePathName = "";
	//  Output file text
	string strPORFFileText = "";
	//  Path delimiter
	char chrPathDelimiter = strPathDelimiter;

	try
	{
		//  If the FA file path name is not empty
		if (!strFAFilePathName.empty())
		{
			//  If the FA file open
			if (GetFileText(strFAFilePathName, strFAFileText))
			{
				//  If the FA file text is not empty, then process the file
				if (!strFAFileText.empty())
				{
					//  Strip the sequence to produce the header, only
					strHeader = strFAFileText.substr(0, strFAFileText.find("\n", 0));

					//  If header is not empty
					if (!strHeader.empty())
					{
						//  Strip header to produce forward sequence, only
						strForward = strFAFileText.substr(strFAFileText.find("\n", 0) + 1, strFAFileText.length());

						//  If forward sequence is not empty
						if (!strForward.empty())
						{
							//  Get reverse compliment
							strReverse = ConvertToReverseCompliment(strForward);

							//  If reverse sequence is not empty
							if (!strReverse.empty())
							{
								//  Get the pORF file path name
								strPORFFilePathName = GetBasePath(strFAFilePathName) + chrPathDelimiter + GetFileNameExceptLastExtension(strFAFilePathName) + ".pORF";

								//  If the output file path name is not empty, then process the file
								if (!strPORFFilePathName.empty())
								{
									//  Process sequences
									for (int nCount = 0; nCount < strForward.length() && nCount < strReverse.length(); nCount += 3)
									{
										// Start codon: aug (bacterial start codons: gug, uug); stop codons: uag, uga, uaa

										//  Process forward sequence, frame 1
										if (nCount + 2 < strForward.length())
										{
											//  Start codon, frame 1
											if (strForward.substr(nCount, 3) == "aug")
											{
												//  Delimit the frame string
												if (!strFF1Starts.empty())
													strFF1Starts += "|";

												//  Concatenate the frame string
												strFF1Starts += ConvertIntToString(nCount);
											}
											//  stop codons, frame 1
											else if ((strForward.substr(nCount, 3) == "uag") || (strForward.substr(nCount, 3) == "uga") || (strForward.substr(nCount, 3) == "uaa"))
											{
												//  Delimit the frame string
												if (!strFF1Stops.empty())
													strFF1Stops += "|";

												//  Concatenate the frame string
												strFF1Stops += ConvertIntToString(nCount);
											}
										}

										//  Process forward sequence, frame 2
										if (nCount + 3 < strForward.length())
										{
											//  Start codon, frame 1
											if (strForward.substr(nCount + 1, 3) == "aug")
											{
												//  Delimit the frame string
												if (!strFF2Starts.empty())
													strFF2Starts += "|";

												//  Concatenate the frame string
												strFF2Starts += ConvertIntToString(nCount + 1);
											}
											//  stop codons, frame 1
											else if ((strForward.substr(nCount + 1, 3) == "uag") || (strForward.substr(nCount + 1, 3) == "uga") || (strForward.substr(nCount + 1, 3) == "uaa"))
											{
												//  Delimit the frame string
												if (!strFF2Stops.empty())
													strFF2Stops += "|";

												//  Concatenate the frame string
												strFF2Stops += ConvertIntToString(nCount + 1);
											}
										}

										//  Process forward sequence, frame 3
										if (nCount + 4 < strForward.length())
										{
											//  Start codon, frame 1
											if (strForward.substr(nCount + 2, 3) == "aug")
											{
												//  Delimit the frame string
												if (!strFF3Starts.empty())
													strFF3Starts += "|";

												//  Concatenate the frame string
												strFF3Starts += ConvertIntToString(nCount + 2);
											}
											//  stop codons, frame 1
											else if ((strForward.substr(nCount + 2, 3) == "uag") || (strForward.substr(nCount + 2, 3) == "uga") || (strForward.substr(nCount + 2, 3) == "uaa"))
											{
												//  Delimit the frame string
												if (!strFF3Stops.empty())
													strFF3Stops += "|";

												//  Concatenate the frame string
												strFF3Stops += ConvertIntToString(nCount + 2);
											}
										}

										//  Process reverse sequence, frame 1
										if (nCount + 2 < strReverse.length())
										{
											//  Start codon, frame 1
											if (strReverse.substr(nCount, 3) == "aug")
											{
												//  Delimit the frame string
												if (!strRF1Starts.empty())
													strRF1Starts += "|";

												//  Concatenate the frame string
												strRF1Starts += ConvertIntToString(nCount);
											}
											//  stop codons, frame 1
											else if ((strReverse.substr(nCount, 3) == "uag") || (strReverse.substr(nCount, 3) == "uga") || (strReverse.substr(nCount, 3) == "uaa"))
											{
												//  Delimit the frame string
												if (!strRF1Stops.empty())
													strRF1Stops += "|";

												//  Concatenate the frame string
												strRF1Stops += ConvertIntToString(nCount);
											}
										}

										//  Process reverse sequence, frame 2
										if (nCount + 3 < strReverse.length())
										{
											//  Start codon, frame 1
											if (strReverse.substr(nCount + 1, 3) == "aug")
											{
												//  Delimit the frame string
												if (!strRF2Starts.empty())
													strRF2Starts += "|";

												//  Concatenate the frame string
												strRF2Starts += ConvertIntToString(nCount + 1);
											}
											//  stop codons, frame 1
											else if ((strReverse.substr(nCount + 1, 3) == "uag") || (strReverse.substr(nCount + 1, 3) == "uga") || (strReverse.substr(nCount + 1, 3) == "uaa"))
											{
												//  Delimit the frame string
												if (!strRF2Stops.empty())
													strRF2Stops += "|";

												//  Concatenate the frame string
												strRF2Stops += ConvertIntToString(nCount + 1);
											}
										}

										//  Process reverse sequence, frame 3
										if (nCount + 4 < strReverse.length())
										{
											//  Start codon, frame 1
											if (strReverse.substr(nCount + 2, 3) == "aug")
											{
												//  Delimit the frame string
												if (!strRF3Starts.empty())
													strRF3Starts += "|";

												//  Concatenate the frame string
												strRF3Starts += ConvertIntToString(nCount + 2);
											}
											//  stop codons, frame 1
											else if ((strReverse.substr(nCount + 2, 3) == "uag") || (strReverse.substr(nCount + 2, 3) == "uga") || (strReverse.substr(nCount + 2, 3) == "uaa"))
											{
												//  Delimit the frame string
												if (!strRF3Stops.empty())
													strRF3Stops += "|";

												//  Concatenate the frame string
												strRF3Stops += ConvertIntToString(nCount + 2);
											}
										}
									}

									//  Concatenate output file text, add header and pipe delimit line ends
									strPORFFileText = strHeader + "\n";
									strPORFFileText += strFF1Starts + "|\n";
									strPORFFileText += strFF1Stops + "|\n";
									strPORFFileText += strFF2Starts + "|\n";
									strPORFFileText += strFF2Stops + "|\n";
									strPORFFileText += strFF3Starts + "|\n";
									strPORFFileText += strFF3Stops + "|\n";
									strPORFFileText += strRF1Starts + "|\n";
									strPORFFileText += strRF1Stops + "|\n";
									strPORFFileText += strRF2Starts + "|\n";
									strPORFFileText += strRF2Stops + "|\n";
									strPORFFileText += strRF3Starts + "|\n";
									strPORFFileText += strRF3Stops + "|\n";

									//  Write file
									if (WriteFileText(strPORFFilePathName, strPORFFileText))
									{
										strListEntry += GetFileName(strPORFFilePathName) + "\n";

										return true;
									}
									else
									{
										strErrorEntry += strPORFFilePathName + "~Write Failed\n";

										ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  pORF File [" + strPORFFilePathName + "] Write Failed");
									}
								}
								else
								{
									ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  pORF File Path Name is Empty");
								}
							}
							else
							{
								ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  Reverse sequence is Empty");
							}
						}
						else
						{
							ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  Forward sequence is Empty");
						}
					}
					else
					{
						ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  Header is Empty");
					}
				}
				else
				{
					ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  Input FA File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  Input FA File [" + strFAFilePathName + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ParseFAtoPORF]", "ERROR:  Input FA File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ParseFAtoPORF] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Processes an FNA [container] file to individual FA file(s)
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strFNAFilePathName            :  FNA [container] file path name
//  [string] strOutputFilePathNameTransform:  output file path name transform (includes string replacements, see help)
//  [vector<string>] vSubFolders           :  sub-folders to create, in nested order
//  [string&] strFNAListEntry              :  FNA list entry
//  [string&] strFAListEntry               :  FA list entry
//  [string&] strErrorEntry                :  error file entry
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ProcessFNAFile(string strFNAFilePathName, string strOutputFilePathNameTransform, vector<string> vSubFolders, string& strFNAListEntry, string& strFAListEntry, string& strErrorEntry)
{
	//  FNA container file text
	string strInputFNAFileText = "";
	//  Individual FNA file text
	string strFNAFileText = "";

	try
	{
		//  If the FA file path name is not empty
		if (!strFNAFilePathName.empty())
		{
			//  If the FA file open
			if (GetFileText(strFNAFilePathName, strInputFNAFileText))
			{
				//  If FNA container file text is not empty, then read file text
				if (!strInputFNAFileText.empty())
				{
					//  Append final delimiter to ensure processing of last file, if container, or single file
					strInputFNAFileText += ">";

					//  Split file contents into individual FNA file(s)
					for (long lCount = 0; lCount < (long)strInputFNAFileText.length(); lCount++)
					{
						//  Start a new FNA file
						if (strInputFNAFileText[lCount] == '>')
						{
							//  If not empty, save the previous file
							if ((!strFNAFileText.empty()) && (strFNAFileText != ">"))
							{
								//  FNA file accession
								string strAccession = "";
								//  Base path name
								string strBasePathName = "";
								//  FNA file path name
								string strFNAFilePathName = "";

								//  Get accession from file text
								strAccession = GetAccessionFromFileHeader(strFNAFileText);

								//  If input file path name transform is not empty
								if (!strOutputFilePathNameTransform.empty())
									strFNAFilePathName = TransformFilePathName(strAccession + ".", strOutputFilePathNameTransform, "fna");
								else
									strFNAFilePathName = strAccession + ".fna";

								//  Get base path nam
								strBasePathName = GetBasePath(strFNAFilePathName);

								//  Create the base folder path
								if (!CreateFolderPath(strBasePathName))
									ReportTimeStamp("[ProcessFNAFile]", "ERROR:  Folder Base Path Creation [" + strBasePathName + "] Failed");

								//  If sub-folder creations are requested, then create these sub-folders
								if (vSubFolders.size() > 0)
								{
									//  Iterate through the list<string>
									for (unsigned int unCount = 0; unCount < vSubFolders.size(); unCount++)
									{
										//  The output sub-folder path
										string strOutputSubFolderPath = strBasePathName + strPathDelimiter;
										strOutputSubFolderPath += vSubFolders[unCount];

										//  Create the output sub-folder path
										if (!CreateFolderPath(strOutputSubFolderPath))
											ReportTimeStamp("[ProcessFNAFile]", "ERROR:  Folder Creation [" + strOutputSubFolderPath + "] Failed");
									}
								}

								//  Write the FNA output file
								if (WriteFileText(strFNAFilePathName, strFNAFileText))
								{
									//  Individual FA File text
									string strFAFileText = "";

									//  Concatenate FNA list entry
									strFNAListEntry += GetFileName(strFNAFilePathName) + "\n";

									//  Convert FNA file format to FA file format
									if (ConvertFNAtoFA(strFNAFileText, strFAFileText))
									{
										//  Individual FA fie path name
										string strFAFilePathName = "";

										//  If input file path name transform is not empty
										if (!strOutputFilePathNameTransform.empty())
											strFAFilePathName = TransformFilePathName(strAccession + ".", strOutputFilePathNameTransform, "fa");
										else
											strFAFilePathName = strAccession + ".fa";

										//  Write the FA output file
										if (WriteFileText(strFAFilePathName, strFAFileText))
										{
											//  Concatenate FA list entry
											strFAListEntry += GetFileName(strFAFilePathName) + "\n";
										}
										else
										{
											strErrorEntry += strFAFilePathName + "~.fa Write Failed\n";

											ReportTimeStamp("[ProcessFNAFile]", "ERROR:  FA File [" + strFAFilePathName + "] Write Failed");
										}
									}
									else
									{
										strErrorEntry += strFNAFilePathName + "~.fa Conversion Failed\n";

										ReportTimeStamp("[ProcessFNAFile]", "ERROR:  FA File [" + strFNAFilePathName + "] Conversion Failed");
									}
								}
								else
								{
									strErrorEntry += strFNAFilePathName + "~.fna Write Failed\n";

									ReportTimeStamp("[ProcessFNAFile]", "ERROR:  FNA File [" + strFNAFilePathName + "] Write Failed");
								}
							}

							//  Rest file text
							strFNAFileText = ">";
						}
						//  Concatenate file text
						else
							strFNAFileText += strInputFNAFileText[lCount];
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ProcessFNAFile]", "ERROR:  Input FNA File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ProcessFNAFile]", "ERROR:  Input FNA File [" + strFNAFilePathName + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ProcessFNAFile]", "ERROR:  Input FNA File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ProcessFNAFile] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Processes a list of NCBI .fna/fa files into BIG format .fa files
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList      :  input file path name list
//  [string] strOutputFilePathNameTransform:  input file path name transform (includes string replacements, see help)
//  [vector<string>] vSubFolders           :  sub-folders to create, in nested order
//  [string] strFNAOutputListFilePathName  :  FNA output list file path name
//  [string] strFAOutputListFilePathName   :  FA output list file path name
//  [string] strErrorFilePathName          :  error file path name
//  [int] nMaxProcs                        :  maximum processors for openMP
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListProcessFNAtoFA(string strInputFilePathNameList, string strOutputFilePathNameTransform, vector<string> vSubFolders, string strFNAOutputListFilePathName,
	string strFAOutputListFilePathName, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  List file text
	string strInputListFileText = "";
	//  File path names extracted from the file path name list file
	vector<string> vFilePathNames;
	//  FNA list file entries
	vector<string> vFNAListEntries;
	//  FNA list file text
	string strFNAOutputListFileText = "";
	//  FA list file entries
	vector<string> vFAListEntries;
	//  FA list file text
	string strFAOutputListFileText = "";
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
					//  Initialize FNA list entries
					vFNAListEntries.resize(vFilePathNames.size());

					//  Initialize FA list entries
					vFAListEntries.resize(vFilePathNames.size());

					//  Initialize error file vector<string>
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
								ReportTimeStamp("[ListProcessFNAtoFA]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListProcessFNAtoFA]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
								omp_unset_lock(&lockList);
							}

							//  If the file path name is not empty, then proceed
							if (!vFilePathNames[lCount].empty())
							{
								//  Process file
								if (!ProcessFNAFile(vFilePathNames[lCount], strOutputFilePathNameTransform, vSubFolders, vFNAListEntries[lCount], vFAListEntries[lCount], vErrorEntries[lCount]))
								{
									vErrorEntries[lCount] += vFilePathNames[lCount] + "~FNA File Process Failed\n";

									omp_set_lock(&lockList);
									ReportTimeStamp("[ListProcessFNAtoFA]", "ERROR:  [" + vFilePathNames[lCount] + "] FNA File Process Failed");
									omp_unset_lock(&lockList);
								}
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Concatenate list/error files
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vFNAListEntries[lCount].empty())
							strFNAOutputListFileText += vFNAListEntries[lCount];

						if (!vFAListEntries[lCount].empty())
							strFAOutputListFileText += vFAListEntries[lCount];

						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  If FNA list file path name is not empty
					if (!strFNAOutputListFilePathName.empty())
					{
						//  Write list file
						if (!WriteFileText(strFNAOutputListFilePathName, strFNAOutputListFileText))
							ReportTimeStamp("[ListProcessFNAtoFA]", "ERROR:  .fna Output List File [" + strFNAOutputListFilePathName + "] Write Failed");
					}

					//  If FA list file path name is not empty
					if (!strFAOutputListFilePathName.empty())
					{
						//  Write list file
						if (!WriteFileText(strFAOutputListFilePathName, strFAOutputListFileText))
							ReportTimeStamp("[ListProcessFNAtoFA]", "ERROR:  .fa Output List File [" + strFAOutputListFilePathName + "] Write Failed");
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListProcessFNAtoFA]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListProcessFNAtoFA]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListProcessFNAtoFA]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListProcessFNAtoFA]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListProcessFNAtoFA] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Parses a list of BIG format .fa files into BIG format .pORF files
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList     :  input file path name list
//  [string] strInputFilePathNameTransform:  input file path name transform (includes string replacements, see help)
//  [int] nMinORFLength                   :  minimum sequence length for ORF parse
//  [int] nMaxORFLength                   :  maximum sequence length for ORF parse
//  [string] strOutputListFilePathName    :  list file path name
//  [string] strErrorFilePathName         :  error file path name
//  [int] nMaxProcs                       :  maximum processors for openMP
//                                        :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListParseFAtoPORF(string strInputFilePathNameList, string strInputFilePathNameTransform, int nMinORFLength, int nMaxORFLength, string strOutputListFilePathName,
	string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  List file text
	string strInputListFileText = "";
	//  File path names extracted from the file path name list file
	vector<string> vFilePathNames;
	//  Outupt list entries
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
			//  Get list file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If file path names exist
				if (vFilePathNames.size() > 0)
				{
					//  Initialize list entries
					vListEntries.resize(vFilePathNames.size());

					//  Initialize error file vector<string>
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
								ReportTimeStamp("[ListParseFAtoPORF]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListParseFAtoPORF]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
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

								//  Parse file
								if (!ParseFAtoPORF(strWorkingFilePathName, nMinORFLength, nMaxORFLength, vListEntries[lCount], vErrorEntries[lCount]))
								{
									vErrorEntries[lCount] += strWorkingFilePathName + "~.fa to .pORF Parse Failed\n";

									omp_set_lock(&lockList);
									ReportTimeStamp("[ListParseFAtoPORF]", "ERROR:  .fa [" + strWorkingFilePathName + "] to .pORF Parse Failed");
									omp_unset_lock(&lockList);
								}
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Concatenate list/error files
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vListEntries[lCount].empty())
							strOutputListFileText += vListEntries[lCount];

						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  If list file path name is not empty
					if (!strOutputListFilePathName.empty())
					{
						//  Write list file
						if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
							ReportTimeStamp("[ListParseFAtoPORF]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListParseFAtoPORF]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListParseFAtoPORF]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListParseFAtoPORF]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListParseFAtoPORF]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListParseFAtoPORF] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Processes a list of BIG format .pORF files into BIF format .ORF files
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList     :  input file path name list
//  [string] strInputFilePathNameTransform:  input file path name transform (includes string replacements, see help)
//  [string] strORFFolderName             :  ORF output folder
//  [int] nMinORFLength                   :  minimum sequence length for ORF parse
//  [int] nMaxORFLength                   :  maximum sequence length for ORF parse
//  [string] strOutputListFilePathName    :  list file path name
//  [string] strErrorFilePathName         :  error file path name
//  [int] nMaxProcs                       :  maximum processors for openMP
//                                        :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListParsePORFtoORF(string strInputFilePathNameList, string strInputFilePathNameTransform, string strORFFolderName, int nMinORFLength, int nMaxORFLength,
	string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs)
{
	//  List lock
	omp_lock_t lockList;
	//  List file text
	string strInputListFileText = "";
	//  File path names extracted from the file path name list file
	vector<string> vFilePathNames;
	//  FNA list entries
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
			//  Get list file text
			if (GetFileText(strInputFilePathNameList, strInputListFileText))
			{
				//  Split file text into file list
				SplitString(strInputListFileText, '\n', vFilePathNames);

				//  If file path names exist
				if (vFilePathNames.size() > 0)
				{
					//  Initialize list entries
					vListEntries.resize(vFilePathNames.size());

					//  Initialize error file vector<string>
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
								ReportTimeStamp("[ListParsePORFtoORF]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListParsePORFtoORF]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
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

								//  Parse file
								vector<structORF> vTemp;
								if (!ParsePORFtoORF(strWorkingFilePathName, strORFFolderName, nMinORFLength, nMaxORFLength, false, vTemp, vListEntries[lCount], vErrorEntries[lCount]))
								{
									vErrorEntries[lCount] += strWorkingFilePathName + "~.pORF to .ORF Parse Failed\n";

									omp_set_lock(&lockList);
									ReportTimeStamp("[ListParsePORFtoORF]", "ERROR:  .pORF [" + strWorkingFilePathName + "] to .ORF Parse Failed");
									omp_unset_lock(&lockList);
								}
							}
						}
					}

					//  Destroy time stamp lock
					omp_destroy_lock(&lockList);

					//  Concatenate list/error files
					for (long lCount = 0; lCount < vFilePathNames.size(); lCount++)
					{
						if (!vListEntries[lCount].empty())
							strOutputListFileText += vListEntries[lCount];

						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  If list file path name is not empty
					if (!strOutputListFilePathName.empty())
					{
						//  Write list file
						if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
							ReportTimeStamp("[ListParsePORFtoORF]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListParsePORFtoORF]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListParsePORFtoORF]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListParsePORFtoORF]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListParsePORFtoORF]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListParsePORFtoORF] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Parses a list of .gbk container files into individual .gbk files
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string] strInputFilePathNameList      :  input file path name list (in NCBI .gbk container file format)
//  [string] strOutputFilePathNameTransform:  output file path name transform (includes string replacements, see help)
//  [string] strOutputFolderPathName       :  output folder path name [optional]
//  [string] strOutputListFilePathName     :  output list file path name
//  [string] strErrorFilePathName          :  error file path name
//  [int] nMaxProcs                        :  maximum processors for openMP
//                                         :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool ListParseGBKContainerFiles(string strInputFilePathNameList, string strOutputFilePathNameTransform, string strOutputListFilePathName, string strErrorFilePathName, int nMaxProcs)
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
	//  Error list file entry text
	vector<string> vErrorEntries;
	//  Error file text
	string strErrorFileText = "";

	try
	{
		//  If file text is not empty
		if (!strInputFilePathNameList.empty())
		{
			//  Process a list of container files
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
								ReportTimeStamp("[ListParseGBKContainerFiles]", "NOTE:  Thread Count = " + ConvertIntToString(omp_get_num_threads()));
								omp_unset_lock(&lockList);
							}

							//  Update for timestamp every 10,000 files
							if (lCount % 10000 == 0)
							{
								omp_set_lock(&lockList);
								ReportTimeStamp("[ListParseGBKContainerFiles]", "NOTE:  Processing Entry [" + ConvertLongToString(lCount) + "] [" + vFilePathNames[lCount] + "]");
								omp_unset_lock(&lockList);
							}

							//  If the file path name is not empty, then proceed
							if (!vFilePathNames[lCount].empty())
							{
								if (!ParseGBKContainerFile(vFilePathNames[lCount], strOutputFilePathNameTransform, vListEntries[lCount], vErrorEntries[lCount]))
								{
									//  Update error entry
									vErrorEntries[lCount] = vFilePathNames[lCount] + "~Parse Failed\n";

									//  Update console
									omp_set_lock(&lockList);
									ReportTimeStamp("[ListParseGBKContainerFiles]", "ERROR:  GBK Container File [" + vFilePathNames[lCount] + "] Parse Failed");
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

						if (!vErrorEntries[lCount].empty())
							strErrorFileText += vErrorEntries[lCount];
					}

					//  Write list file
					if (!strOutputListFilePathName.empty())
					{
						if (!WriteFileText(strOutputListFilePathName, strOutputListFileText))
							ReportTimeStamp("[ListParseGBKContainerFiles]", "ERROR:  Output List File [" + strOutputListFilePathName + "] Write Failed");
					}

					//  Write error file
					if (!strErrorFilePathName.empty())
					{
						//  Write the file
						if (!WriteFileText(strErrorFilePathName, strErrorFileText))
							ReportTimeStamp("[ListParseGBKContainerFiles]", "ERROR:  Error File [" + strErrorFilePathName + "] Write Failed");
					}

					return true;
				}
				else
				{
					ReportTimeStamp("[ListParseGBKContainerFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] File Text is Empty");
				}
			}
			else
			{
				ReportTimeStamp("[ListParseGBKContainerFiles]", "ERROR:  Input List File [" + strInputFilePathNameList + "] Open Failed");
			}
		}
		else
		{
			ReportTimeStamp("[ListParseGBKContainerFiles]", "ERROR:  Input List File Path Name is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ListParseGBKContainerFiles] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

