// Base123_Shuffler.cpp : Function definitions

////////////////////////////////////////////////////////////////////////////////
//
//  Base123_Shuffler:  stores .fa BIG format sequence in frame-codons collections
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
#include "Base123_Shuffler.h"

#include <stdlib.h> 
#include <math.h>
#include <time.h>

//  Initialization

////////////////////////////////////////////////////////////////////////////////
//
//  Constructs the CBase123_Shuffler class object
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

CBase123_Shuffler::CBase123_Shuffler()
{
	try
	{
		//  Set defaults
		m_nMaxBases = 4;
		m_nMaxFrames = 3;
		m_dBaseSimilarities = 0;
	}
	catch (exception ex)
	{
		cout << "ERROR [CBase123_Shuffler] Exception Code:  " << ex.what() << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//  Destructs the CBase123_Shuffler class object
//
////////////////////////////////////////////////////////////////////////////////
//
//
//         
////////////////////////////////////////////////////////////////////////////////

CBase123_Shuffler::~CBase123_Shuffler()
{
	try
	{
	}
	catch (exception ex)
	{
		cout << "ERROR [~CBase123_Shuffler] Exception Code:  " << ex.what() << "\n";
	}
}

//  Interface (public)

////////////////////////////////////////////////////////////////////////////////
//
//  shuffles the loaded sequence
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence              :  sequence to shuffle
//  [vector<structStartStop>&] vStartsStops:  sorted CDS starts/stops
//                                    :  returns shuffled sequence, if successful; else, an empty string
//         
////////////////////////////////////////////////////////////////////////////////

string CBase123_Shuffler::shuffleSequence(string& strSequence, vector<structStartStop>& vStartsStops)
{
	//  shuffle to return
	string strshuffle = "";
	//  Max shuffle attempts to break while loop in case of no solution
	int nMaxshuffleAttempts = 100000;
	//  Max shuffle counter
	int nshuffleCount = 0;
	//  Sub-sequence to shuffle
	string strSubSequence = "";
	//  Codon shuffle
	string strCodonshuffle = "";
	//  Base shuffle
	string strBaseshuffle = "";

	try
	{
		//  If sequence contains at least one CDS start/stop pair
		if (vStartsStops.size() >= 1)
		{
			//  Iterate starts/stops, parse and shuffle sequence
			for (int nCount = 0; nCount < vStartsStops.size(); nCount++)
			{
				//  CDS sub-sequence
				strSubSequence = strSequence.substr(vStartsStops[nCount].lStart - 1, (vStartsStops[nCount].lStop - vStartsStops[nCount].lStart) + 1);

				//  If depth is zero, base shuffle
				if (vStartsStops[nCount].nDepth == 0)
				{
					strBaseshuffle = GetBaseshuffle(strSubSequence);

					strshuffle += strBaseshuffle;
				}
				//  Else codon shuffle
				else
				{
					strCodonshuffle = "";
					nshuffleCount = 0;
					while ((strCodonshuffle.empty()) && (nshuffleCount < nMaxshuffleAttempts))
					{
						strCodonshuffle = GetCodonshuffle(strSubSequence);

						//  Reject same-sequence shuffle
						if (strCodonshuffle == strSubSequence)
						{
							strCodonshuffle = "";

							//  Accelerate shuffle count, as a same-sequence return indicates a short sequence and unlikely prospects for true shuffle
							nshuffleCount += 10000;
						}

						//  Increment counter
						nshuffleCount++;
					}
					
					//  Last pass base shuffle is better than nothing
					if (strCodonshuffle.empty())
						strCodonshuffle = GetBaseshuffle(strSubSequence);

					strshuffle += strCodonshuffle;
				}
			}

			//  Return shuffle
			return strshuffle;
		}
		else
		{
			ReportTimeStamp("[shuffleSequence]", "ERROR:  Sequence CDS Collection is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [shuffleSequence] Exception Code:  " << ex.what() << "\n";
	}

	return "";
}

////////////////////////////////////////////////////////////////////////////////
//
//  Gets base similarities calculation
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns base similarities, if successful; else, zero
//         
////////////////////////////////////////////////////////////////////////////////

double CBase123_Shuffler::GetBaseSimilarities()
{
	try
	{
		return m_dBaseSimilarities;
	}
	catch (exception ex)
	{
		cout << "ERROR [GetBaseSimilarities] Exception Code:  " << ex.what() << "\n";
	}

	return 0;
}

//  Implementation (private)

////////////////////////////////////////////////////////////////////////////////
//
//  Resets the Shuffler
//         
////////////////////////////////////////////////////////////////////////////////
//
//  :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool CBase123_Shuffler::ZeroEdgeCounts()
{
	try
	{
		//  Reset all edge counts to zero
		for (int nCountEdges = 0; nCountEdges < pow(m_nMaxBases,2); nCountEdges++)
		{
			for (int nCountBases = 0; nCountBases < m_nMaxBases; nCountBases++)
			{
				for (int nCountFrames = 0; nCountFrames < m_nMaxFrames; nCountFrames++)
					m_arlEdges[nCountEdges][nCountBases][nCountFrames] = 0;
			}
		}

		return true;
	}
	catch (exception ex)
	{
		cout << "ERROR [ZeroEdgeCounts] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Loads the edges collection for a random shuffle
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence:  sequence to shuffle, character by character
//                      :  returns true, if successful; else, false
//         
////////////////////////////////////////////////////////////////////////////////

bool CBase123_Shuffler::LoadEdges(string& strSequence)
{
	//  Edge selectors
	int nSelect1 = 0;
	int nSelect2 = 0;
	int nSelect3 = 0;
	//  Frame
	int nFrame = 0;

	try
	{
		//  Reset edges
		if (ZeroEdgeCounts())
		{
			//  If sequence is not empty
			if (!strSequence.empty())
			{
				//  Iterate sequence, codon by codon
				for (long lCountSequence = 0; lCountSequence < strSequence.length() - 2; lCountSequence++)
				{
					//  Set frame
					if (lCountSequence % 3 == 2)
						nFrame = 2;
					else if (lCountSequence % 3 == 1)
						nFrame = 1;
					else
						nFrame = 0;

					//  Set edge selector 1 according to codon base 1
					if (strSequence[lCountSequence] == 'a')
						nSelect1 = 0;
					else if (strSequence[lCountSequence] == 'c')
						nSelect1 = 1;
					else if (strSequence[lCountSequence] == 'g')
						nSelect1 = 2;
					else if (strSequence[lCountSequence] == 'u')
						nSelect1 = 3;

					//  Set edge selector 2 according to codon base 2
					if (strSequence[lCountSequence+1] == 'a')
						nSelect2 = 0;
					else if (strSequence[lCountSequence + 1] == 'c')
						nSelect2 = 1;
					else if (strSequence[lCountSequence + 1] == 'g')
						nSelect2 = 2;
					else if (strSequence[lCountSequence + 1] == 'u')
						nSelect2 = 3;

					//  Set edge selector 3 according to codon base 3
					if (strSequence[lCountSequence+2] == 'a')
						nSelect3 = 0;
					else if (strSequence[lCountSequence + 2] == 'c')
						nSelect3 = 1;
					else if (strSequence[lCountSequence + 2] == 'g')
						nSelect3 = 2;
					else if (strSequence[lCountSequence + 2] == 'u')
						nSelect3 = 3;

					//Edges[eval(S1[b]) * 4 + eval(S1[b + 1])][eval(S1[b + 2])][b % 3] += 1
					m_arlEdges[(nSelect1 * 4) + nSelect2][nSelect3][nFrame]++;

				}

				return true;
			}
			else
			{
				ReportTimeStamp("[LoadEdges]", "ERROR:  Input Sequence is Empty");
			}
		}
		else
		{
			ReportTimeStamp("[LoadEdges]", "ERROR:  Shuffler Reset Failed");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [LoadEdges] Exception Code:  " << ex.what() << "\n";
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//  shuffles a sequence, codon by codon
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence:  sequence to shuffle, codon by codon
//                      :  returns the shuffled sequence, if successful; else, an empty string
//         
////////////////////////////////////////////////////////////////////////////////

string CBase123_Shuffler::GetCodonshuffle(string& strSequence)
{
	//  shuffled sequence
	string strshuffle = "";
	//  Base selector
	int nBaseSelect = 0;
	//  Base index
	int nBaseIndex = 0;
	//  Edge selectors
	int nSelect1 = 0;
	int nSelect2 = 0;
	//  Next base choice
	string strNextBaseChoice = "";
	//  Next base
	char chrNextBase = '\0';
	//  Frame
	int nFrame = 0;

	try
	{
		//  If sequence is not empty
		if (!strSequence.empty())
		{
			//  Reset edges
			if (LoadEdges(strSequence))
			{
				//  First two bases always return
				//  S2 = S1[:2]
				strshuffle = strSequence.substr(0, 2);

				//  Iterate sequence, codon by codon
				//  for b in range(0, len(S1) - 2) :
				for (long lCountSequence = 0; lCountSequence < strSequence.length() - 2; lCountSequence++)
				{
					//  Set frame
					if (lCountSequence % 3 == 2)
						nFrame = 2;
					else if (lCountSequence % 3 == 1)
						nFrame = 1;
					else
						nFrame = 0;

					//  Set edge selector 1 according to codon base 1
					if (strshuffle[lCountSequence] == 'a')
						nSelect1 = 0;
					else if (strshuffle[lCountSequence] == 'c')
						nSelect1 = 1;
					else if (strshuffle[lCountSequence] == 'g')
						nSelect1 = 2;
					else if (strshuffle[lCountSequence] == 'u')
						nSelect1 = 3;

					//  Set edge selector 2 according to codon base 2
					if (strshuffle[lCountSequence + 1] == 'a')
						nSelect2 = 0;
					else if (strshuffle[lCountSequence + 1] == 'c')
						nSelect2 = 1;
					else if (strshuffle[lCountSequence + 1] == 'g')
						nSelect2 = 2;
					else if (strshuffle[lCountSequence + 1] == 'u')
						nSelect2 = 3;
						
					//  Clear next base choice
					//  nextBase = ''
					strNextBaseChoice = "";

					//  Iterate bases
					//  for i in range(4) :
					for (int nCountBases = 0; nCountBases < m_nMaxBases; nCountBases++)
					{
						if (nCountBases == 0)
							chrNextBase = 'a';
						else if (nCountBases == 1)
							chrNextBase = 'c';
						else if (nCountBases == 2)
							chrNextBase = 'g';
						else if (nCountBases == 3)
							chrNextBase = 'u';

						//  Iterate frames, concatenate next base choice
						//  for j in range(Edges[eval(S2[b]) * 4 + eval(S2[b + 1])][i][b % 3]) :
						for (int nCountEdges = 0; nCountEdges < m_arlEdges[(nSelect1 * 4) + nSelect2][nCountBases][nFrame]; nCountEdges++)
						{
							// nextBase += Bases[i]
							strNextBaseChoice += chrNextBase;
						}
					}

					//  If edge choices remain
					if (!strNextBaseChoice.empty())
					{
						//  Select one of the available edges randomly
						//  B = random.choice(nextBase)
						nBaseSelect = int((strNextBaseChoice.length() * rand()) / (RAND_MAX + 1.0));

						//  Concatenate the shuffle
						//  S2 += B
						strshuffle += strNextBaseChoice[nBaseSelect];

						//  Decrement edges, identify base index
						if (strNextBaseChoice[nBaseSelect] == 'a')
							nBaseIndex = 0;
						else if (strNextBaseChoice[nBaseSelect] == 'c')
							nBaseIndex = 1;
						else if (strNextBaseChoice[nBaseSelect] == 'g')
							nBaseIndex = 2;
						else if (strNextBaseChoice[nBaseSelect] == 'u')
							nBaseIndex = 3;

						//  Decrement edges for the given base choice
						m_arlEdges[(nSelect1 * 4) + nSelect2][nBaseIndex][nFrame]--;
					}
					else
					{
						//  Return empty sequence
						strshuffle = "";

						break;
					}
				}

				//  Reset Shuffler
				ZeroEdgeCounts();
			}
			else
			{
				ReportTimeStamp("[GetCodonshuffle]", "ERROR:  Edge Load Failed");
			}
		}
		else
		{
			ReportTimeStamp("[GetCodonshuffle]", "ERROR:  Input Sequence is Empty");
		}
	}
	catch (exception ex)
	{
		//  Make sure to return an empty sequence
		strshuffle = "";

		cout << "ERROR [GetCodonshuffle] Exception Code:  " << ex.what() << "\n";
	}

	return strshuffle;
}

////////////////////////////////////////////////////////////////////////////////
//
//  shuffles a sequence, base by base
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence:  sequence to shuffle, character by character
//                      :  returns the shuffled sequence, if successful; else, an empty string
//         
////////////////////////////////////////////////////////////////////////////////

string CBase123_Shuffler::GetBaseshuffle(string& strSequence)
{
	//  shuffled sequence
	string strshuffle = "";
	//  Character vector
	vector<char> vSequence;
	//  Character selector
	int nSelect = 0;

	try
	{
		//  If sequence is not empty
		if (!strSequence.empty())
		{
			//  Fill options vector<char>
			for (int nCount = 0; nCount < strSequence.length(); nCount++)
				vSequence.push_back(strSequence[nCount]);
			
			//  Randomly select characters from the sequence
			while (vSequence.size() > 0)
			{
				//  Select a random base from the options vector
				nSelect = (int)((vSequence.size() * rand()) / (RAND_MAX + 1.0));

				//  Concatenate shuffle
				strshuffle += vSequence[nSelect];

				//  Remove the selected base from the options vector
				vSequence.erase(vSequence.begin() + nSelect);
			}
		}
		else
		{
			ReportTimeStamp("[GetBaseshuffle]", "ERROR:  Input Sequence is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [GetBaseshuffle] Exception Code:  " << ex.what() << "\n";
	}

	return strshuffle;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Counts base-frequencies
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence  :  original sequence to analyze
//  [long&] arlBaseCount[4]:  base count array
//         
////////////////////////////////////////////////////////////////////////////////

void CBase123_Shuffler::CountBases(string& strSequence, long(&arlBaseCount)[4])
{
	//  Frame selector
	int nFrame = 0;
	//  Base selectors
	int nBase = 0;

	try
	{
		//  If sequence is not empty
		if (!strSequence.empty())
		{
			//  Iterate and count sequence
			for (long lCountSequence = 0; lCountSequence < strSequence.length(); lCountSequence++)
			{
				//  Set base, pos 1
				if (strSequence[lCountSequence] == 'a')
					nBase = 0;
				else if (strSequence[lCountSequence] == 'c')
					nBase = 1;
				else if (strSequence[lCountSequence] == 'g')
					nBase = 2;
				else if (strSequence[lCountSequence] == 'u')
					nBase = 3;

				arlBaseCount[nBase]++;
			}
		}
		else
		{
			ReportTimeStamp("[CountBases]", "ERROR:  Input Sequence is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [CountBases] Exception Code:  " << ex.what() << "\n";
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Counts codon-frequencies
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence             :  original sequence to analyze
//  [long&] arlCodonCounts[4][4][4][4]:  codon count array
//         
////////////////////////////////////////////////////////////////////////////////

void CBase123_Shuffler::CountCodons(string& strSequence, long (&arlCodonCounts)[4][4][4])
{
	//  Frame selector
	int nFrame = 0;
	//  Base selectors
	int nSelect1 = 0;
	int nSelect2 = 0;
	int nSelect3 = 0;

	try
	{
		//  If sequence is not empty
		if (!strSequence.empty())
		{
			//  Iterate and count sequence
			for (long lCountSequence = 0; lCountSequence < strSequence.length(); lCountSequence++)
			{
				//  Set frame
				if (lCountSequence % 3 == 2)
					nFrame = 2;
				else if (lCountSequence % 3 == 1)
					nFrame = 1;
				else
					nFrame = 0;

				//  Set base, pos 1
				if (strSequence[lCountSequence] == 'a')
					nSelect1 = 0;
				else if (strSequence[lCountSequence] == 'c')
					nSelect1 = 1;
				else if (strSequence[lCountSequence] == 'g')
					nSelect1 = 2;
				else if (strSequence[lCountSequence] == 'u')
					nSelect1 = 3;

				//  Set base, pos 2
				if (lCountSequence + 1 < strSequence.length())
				{
					if (strSequence[lCountSequence + 1] == 'a')
						nSelect2 = 0;
					else if (strSequence[lCountSequence + 1] == 'c')
						nSelect2 = 1;
					else if (strSequence[lCountSequence + 1] == 'g')
						nSelect2 = 2;
					else if (strSequence[lCountSequence + 1] == 'u')
						nSelect2 = 3;
				}

				//  Set base, pos 3
				if (lCountSequence + 2 < strSequence.length())
				{
					if (strSequence[lCountSequence + 2] == 'a')
						nSelect3 = 0;
					else if (strSequence[lCountSequence + 2] == 'c')
						nSelect3 = 1;
					else if (strSequence[lCountSequence + 2] == 'g')
						nSelect3 = 2;
					else if (strSequence[lCountSequence + 2] == 'u')
						nSelect3 = 3;
				}

				//  Count codons
				if (lCountSequence + 2 < strSequence.length())
					arlCodonCounts[nSelect1][nSelect2][nSelect3]++;
			}
		}
		else
		{
			ReportTimeStamp("[CountCodons]", "ERROR:  Input Sequence is Empty");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [CountCodons] Exception Code:  " << ex.what() << "\n";
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Zeros codong count array
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [long&] arlCodonCounts[4][4][4][4]:  codon count array
//         
////////////////////////////////////////////////////////////////////////////////

void CBase123_Shuffler::ZeroCodonCounts(long(&arlCodonCounts)[4][4][4])
{
	try
	{
		//  Zero codon counts
		for (int nCountF1 = 0; nCountF1 < 4; nCountF1++)
		{
			for (int nCountF2 = 0; nCountF2 < 4; nCountF2++)
			{
				for (int nCountF3 = 0; nCountF3 < 4; nCountF3++)
					arlCodonCounts[nCountF1][nCountF2][nCountF3] = 0;
			}
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [ZeroCodonCounts] Exception Code:  " << ex.what() << "\n";
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Zeros codong count array
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence:  original sequence to analyze
//  [string&] strshuffle :  shuffle to analyze
//                      :  returns count of base similarities
//         
////////////////////////////////////////////////////////////////////////////////

long CBase123_Shuffler::AnalyzeBaseSimilarites(string& strSequence, string& strshuffle)
{
	//  Base similarity counts
	long lCountBaseSimilarities = 0;

	try
	{
		//  Reset similarity double
		m_dBaseSimilarities = 0;

		//  Count base positional differences
		if (strSequence.length() == strshuffle.length())
		{
			for (long lCountSequence = 0; lCountSequence < strSequence.length(); lCountSequence++)
			{
				if ((strSequence[lCountSequence] == strshuffle[lCountSequence]))
					lCountBaseSimilarities++;
			}

			//  Calculate base similarities
			m_dBaseSimilarities = (double)((double)lCountBaseSimilarities / (double)strSequence.length());
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [AnalyzeBaseSimilarites] Exception Code:  " << ex.what() << "\n";
	}

	return lCountBaseSimilarities;
}

////////////////////////////////////////////////////////////////////////////////
//
//  Analyzes and compares shuffle input and output sequences
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [string&] strSequence:  original sequence to analyze
//  [string&] strshuffle :  shuffle to analyze
//         
////////////////////////////////////////////////////////////////////////////////

void CBase123_Shuffler::AnalyzeOutput(string& strSequence, string& strshuffle)
{
	//  Sequence codon counts
	long arlSequenceF1Counts[4][4][4];
	long arlSequenceF2Counts[4][4][4];
	long arlSequenceF3Counts[4][4][4];
	//  Sequence base counts
	long arlSequenceBaseCounts[4];

	//  shuffle codon counts
	long arlshuffleF1Counts[4][4][4];
	long arlshuffleF2Counts[4][4][4];
	long arlshuffleF3Counts[4][4][4];
	//  shuffle base counts
	long arlshuffleBaseCounts[4];

	//  Sub-sequence
	string strSubSequence = "";

	//  Base conversion
	string strBase1 = "";
	string strBase2 = "";
	string strBase3 = "";
	//  Timestamp message
	string strMessage = "";
	//  Total codon difference
	long lCodonDiff = 0;
	//  Total failed codon(s)
	int nCountCodonFails = 0;

	try
	{
		//  Zero codon counts
		ZeroCodonCounts(arlSequenceF1Counts);
		ZeroCodonCounts(arlSequenceF2Counts);
		ZeroCodonCounts(arlSequenceF3Counts);
		ZeroCodonCounts(arlshuffleF1Counts);
		ZeroCodonCounts(arlshuffleF2Counts);
		ZeroCodonCounts(arlshuffleF3Counts);

		//  Zero base counts
		for (int nCount = 0; nCount < 4; nCount++)
		{
			arlSequenceBaseCounts[nCount] = 0;
			arlshuffleBaseCounts[nCount] = 0;
		}

		//  Analyze sequence
		CountBases(strSequence, arlSequenceBaseCounts);
		CountCodons(strSequence, arlSequenceF1Counts);
		strSubSequence = strSequence.substr(1, strSequence.length() - 1);
		CountCodons(strSubSequence, arlSequenceF2Counts);
		strSubSequence = strSequence.substr(2, strSequence.length() - 2);
		CountCodons(strSubSequence, arlSequenceF3Counts);

		//  Analyze shuffle
		CountBases(strshuffle, arlshuffleBaseCounts);
		CountCodons(strshuffle, arlshuffleF1Counts);
		strSubSequence = strshuffle.substr(1, strshuffle.length() - 1);
		CountCodons(strSubSequence, arlshuffleF2Counts);
		strSubSequence = strSequence.substr(2, strshuffle.length() - 2);
		CountCodons(strSubSequence, arlshuffleF3Counts);

		//  Report codon counts
		//  Select pos 1
		for (int nCountF1 = 0; nCountF1 < 4; nCountF1++)
		{
			//  Convert to base, F1
			if (nCountF1 == 0)
				strBase1 = "a";
			else if (nCountF1 == 1)
				strBase1 = "c";
			else if (nCountF1 == 2)
				strBase1 = "g";
			else if (nCountF1 == 3)
				strBase1 = "u";

			//  Select pos 2
			for (int nCountF2 = 0; nCountF2 < 4; nCountF2++)
			{
				//  Convert to base, F2
				if (nCountF2 == 0)
					strBase2 = "a";
				else if (nCountF2 == 1)
					strBase2 = "c";
				else if (nCountF2 == 2)
					strBase2 = "g";
				else if (nCountF2 == 3)
					strBase2 = "u";

				for (int nCountF3 = 0; nCountF3 < 4; nCountF3++)
				{
					//  Convert to base, F3
					if (nCountF3 == 0)
						strBase3 = "a";
					else if (nCountF3 == 1)
						strBase3 = "c";
					else if (nCountF3 == 2)
						strBase3 = "g";
					else if (nCountF3 == 3)
						strBase3 = "u";

					//  Report counts
					if (arlSequenceF1Counts[nCountF1][nCountF2][nCountF3] == arlshuffleF1Counts[nCountF1][nCountF2][nCountF3])
						strMessage = "PASS:  Codon [] [i/o] [i-o] [";
					else
					{
						strMessage = "FAIL:  Codon [] [i/o] [i-o] ["; 
						
						//  Increment codon fail count
						nCountCodonFails++;
					}

					strMessage += strBase1 + strBase2 + strBase3 + "] [";
					strMessage += ConvertLongToString(arlSequenceF1Counts[nCountF1][nCountF2][nCountF3]);
					strMessage += "/";
					strMessage += ConvertLongToString(arlshuffleF1Counts[nCountF1][nCountF2][nCountF3]);
					strMessage += "] [";
					strMessage += ConvertLongToString(arlSequenceF1Counts[nCountF1][nCountF2][nCountF3] - arlshuffleF1Counts[nCountF1][nCountF2][nCountF3]);
					strMessage += "]";

					//  Total codon difference
					lCodonDiff += arlSequenceF1Counts[nCountF1][nCountF2][nCountF3] - arlshuffleF1Counts[nCountF1][nCountF2][nCountF3];

					ReportTimeStamp("[AnalyzeOutput]", strMessage);
				}
			}
		}

		//  Report bases
		for (int nCountBases = 0; nCountBases < 4; nCountBases++)
		{
			//  Convert to base, F3
			if (nCountBases == 0)
				strBase1 = "a";
			else if (nCountBases == 1)
				strBase1 = "c";
			else if (nCountBases == 2)
				strBase1 = "g";
			else if (nCountBases == 3)
				strBase1 = "u";

			//  Report counts
			if (arlSequenceBaseCounts[nCountBases] == arlshuffleBaseCounts[nCountBases])
				strMessage = "PASS:  Base [] [i/o] [i-o] [";
			else
				strMessage = "FAIL:  Base [] [i/o] [i-o] [";

			strMessage += strBase1 + "] [";
			strMessage += ConvertLongToString(arlSequenceBaseCounts[nCountBases]);
			strMessage += "/";
			strMessage += ConvertLongToString(arlshuffleBaseCounts[nCountBases]);
			strMessage += "] [";
			strMessage += ConvertLongToString(arlSequenceBaseCounts[nCountBases] - arlshuffleBaseCounts[nCountBases]);
			strMessage += "]";

			ReportTimeStamp("[AnalyzeOutput]", strMessage);
		}
		
		//  Count base positional differences
		if (strSequence.length() == strshuffle.length())
		{
			AnalyzeBaseSimilarites(strSequence, strshuffle);

			ReportTimeStamp("[AnalyzeOutput]", "NOTE:  Positional Base Similarities = " + ConvertDoubleToString(m_dBaseSimilarities) + "]");
		}

		//  Report length
		if (strSequence.length() == strshuffle.length())
			ReportTimeStamp("[AnalyzeOutput]", "PASS:  Length [i/o] [i-o] [" + ConvertLongToString((long)strSequence.length()) + "/" + ConvertLongToString((long)strshuffle.length()) + "] [" + ConvertLongToString((long)strSequence.length() - (long)strshuffle.length()) + "]");
		else
			ReportTimeStamp("[AnalyzeOutput]", "FAIL:  Length [i/o] [i-o] [" + ConvertLongToString((long)strSequence.length()) + "/" + ConvertLongToString((long)strshuffle.length()) + "] [" + ConvertLongToString((long)strSequence.length() - (long)strshuffle.length()) + "]");

		//  Report codon difference
		if (lCodonDiff == 0)
			ReportTimeStamp("[AnalyzeOutput]", "PASS:  Codon Difference  [0]");
		else
			ReportTimeStamp("[AnalyzeOutput]", "FAIL:  Codon Difference [" + ConvertLongToString(lCodonDiff) + "]");

		//  Report codon difference
		ReportTimeStamp("[AnalyzeOutput]", "NOTE:  Codon Fails [" + ConvertLongToString(nCountCodonFails) + "]");

	}
	catch (exception ex)
	{
		cout << "ERROR [AnalyzeOutput] Exception Code:  " << ex.what() << "\n";
	}

	return;
}
