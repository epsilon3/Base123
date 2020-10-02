// Base123.cpp : Defines the entry point for the Base123 application.

////////////////////////////////////////////////////////////////////////////////
//
//  Base123 main application:
//
//  Developed by Stephen Donald Huff, PhD (Stephen.Huff.3@us.af.mil)
//  Biological Informatics Group, RHDJ, 711HPW, United States Air Force Research Laboratory
//  22 June 2016
//  (All Rights Reserved)
//
////////////////////////////////////////////////////////////////////////////////

#include "Base123.h"
#include "Base123_Help.h"
#include "Base123_Utilities.h"
#include "Base123_File_Mgr.h"
#include "Base123_NCBI_Mgr.h"
#include "Base123_Catalog_Entry.h"
#include "Base123_Catalog.h"
#include "Base123_FDistance.h"
#include "Base123_FRESH.h"
#include "Base123_Fold.h"
#include "Base123_Structureome_Mgr.h"

#include <sys/stat.h>
#include <sstream>
#include <omp.h>

////////////////////////////////////////////////////////////////////////////////
//
//  See ReportBase123Help() function for algorithm details;
//         
////////////////////////////////////////////////////////////////////////////////
//
//  [int] nArgumentCount:  argument count, space delimited
//  [char*] chpArguments:  arguments, space cropped
//                     :  returns the exit or return code
//         
////////////////////////////////////////////////////////////////////////////////

int main(int nArgumentCount, char* chpArguments[])
{
	//  Parameter report
	string strReport = "";
	//  Arguments vector
	vector<string> vArgs;
	
	try
	{
		#ifdef _WIN64
		#else
			//  Set the umask
			umask(0007);
		#endif

		// Command line must contain at least (list file and output folder [or use base path as output folder])
		//    or it must call for help, only
		if (nArgumentCount < 2)
		{
			// Update console; suggest help
			ReportTimeStamp(chpArguments[0], "ERROR: Use the Following Command Switch for Assistance: -help [-h]");

			return -1;
		}
		// Process switches and parameters
		else
		{
			//  Replace empty arguments with empty strings
			for (int nCount = 0; nCount < nArgumentCount; nCount++)
			{
				if (ConvertStringToLowerCase(chpArguments[nCount]) == "^mt^")
				{
					string strMT = "";
					vArgs.push_back(strMT);
				}
				else
					vArgs.push_back(chpArguments[nCount]);
			}

			//  Report  help
			if ((ConvertStringToLowerCase(vArgs[1]) == "-help") || (ConvertStringToLowerCase(vArgs[1]) == "-h"))
			{
				ReportBase123Help();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_ncbi_management") || (ConvertStringToLowerCase(vArgs[1]) == "-hnm"))
			{
				ReportNCBIManagementHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_catalog_management") || (ConvertStringToLowerCase(vArgs[1]) == "-hcm"))
			{
				ReportCatalogManagementHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_shuffler_management") || (ConvertStringToLowerCase(vArgs[1]) == "-hsm"))
			{
				ReportShufflerManagementHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_fdistance_management") || (ConvertStringToLowerCase(vArgs[1]) == "-hfm"))
			{
				ReportFDistanceManagementHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_nucleotide_fold_management") || (ConvertStringToLowerCase(vArgs[1]) == "-hnfm"))
			{
				ReportNucleotideFoldManagementHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_structure_ome_management") || (ConvertStringToLowerCase(vArgs[1]) == "-hsom"))
			{
				ReportStructureomeManagementHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_file_system_management") || (ConvertStringToLowerCase(vArgs[1]) == "-hfsm"))
			{
				ReportFileSystemManagementHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_parse_fna_to_fa") || (ConvertStringToLowerCase(vArgs[1]) == "-hpftf"))
			{
				ReportListParseFNAtoFAHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_parse_fa_to_porf") || (ConvertStringToLowerCase(vArgs[1]) == "-hpftp"))
			{
				ReportListParseFAtoPORFHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_parse_porf_to_orf") || (ConvertStringToLowerCase(vArgs[1]) == "-hppto"))
			{
				ReportListParsePORFtoORFHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_parse_gbk_container") || (ConvertStringToLowerCase(vArgs[1]) == "-hpgc"))
			{
				ReportListParseGBKContainerHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_create_dat_catalog") || (ConvertStringToLowerCase(vArgs[1]) == "-hcdc"))
			{
				ReportDatCatalogHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_create_gbk_catalog") || (ConvertStringToLowerCase(vArgs[1]) == "-hcgc"))
			{
				ReportGBKCatalogHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_shuffle_fa_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlsff"))
			{
				ReportFRESHHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_filter_for_fdistance") || (ConvertStringToLowerCase(vArgs[1]) == "-hlfff"))
			{
				ReportFilterFDistanceListHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_contabulate_fdistance_output") || (ConvertStringToLowerCase(vArgs[1]) == "-hlcfo"))
			{
				ReportListContabulateFDistanceOutputHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_clear_fdistance_output") || (ConvertStringToLowerCase(vArgs[1]) == "-hlclfo"))
			{
				ReportListClearFDistanceOutputHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_perform_fdistance_analysis") || (ConvertStringToLowerCase(vArgs[1]) == "-hpfd"))
			{
				ReportPerformFDistanceAnalysisHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_fold_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlff"))
			{
				ReportListFoldFilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_confirm_fold_output_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlcfof"))
			{
				ReportListConfirmFoldOutputFilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_extract_pdb_from_silent_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlepfsf"))
			{
				ReportListExtractPDBFromSilentFilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_convert_pdb_to_db_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlcptdf"))
			{
				ReportListConvertPDBToB123FilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_tabulate_vrna_output_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hltvof"))
			{
				ReportListTabulateB123FilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_tabulate_rosa_output_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hltrof"))
			{
				ReportListConvertDBtoB123FilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_create_distributed_batch_job") || (ConvertStringToLowerCase(vArgs[1]) == "-hcdbj"))
			{
				ReportCreateDistributedBatchJobHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_convert_path") || (ConvertStringToLowerCase(vArgs[1]) == "-hlcp"))
			{
				ReportListConvertPathHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_file_find_replace") || (ConvertStringToLowerCase(vArgs[1]) == "-hffr"))
			{
				ReportFileFindReplaceHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_delete_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hldf"))
			{
				ReportListDeleteFilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_delete_files_in_directory") || (ConvertStringToLowerCase(vArgs[1]) == "-hldfid"))
			{
				ReportListDeleteFilesInDirectoryHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_transform_rename_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hltrf"))
			{
				ReportListTransformRenameFilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_match_replace_rename_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlmrrf"))
			{
				ReportListMatchReplaceRenameFilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_confirm_output_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlcof"))
			{
				ReportListConfirmOutputFilesHelp();

				return 0;
			}
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-help_list_compare_differential_files") || (ConvertStringToLowerCase(vArgs[1]) == "-hlcdf"))
			{
				ReportListCompareDifferentialFilesHelp();

				return 0;
			}

			//  Update console; start application;
			ReportTimeStamp(vArgs[0], "Base123 Start: ");

			//  Report parameters
			strReport = "[" + ConvertIntToString(nArgumentCount) + "] ";
			for (int nCount = 0; nCount < nArgumentCount; nCount++)
			{
				strReport += vArgs[nCount];
				strReport += "; ";
			}
			strReport += "\n";

			//  Report to console
			ReportTimeStamp("Parameters:  ", strReport);

			//  Test
			if ((ConvertStringToLowerCase(vArgs[1]) == "-test") || (ConvertStringToLowerCase(vArgs[1]) == "-t"))
			{
			}
			//  List parse fna to fa
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_parse_fna_to_fa") || (ConvertStringToLowerCase(vArgs[1]) == "-lpftf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7>
				//    -list_parse_fna_to_fa [-lpftf]
				//         <input_file_path_name_list>
				//         <output_file_path_name_transform>
				//         <sub_folder_list>
				//         <fna_output_list_file_path_name>
				//         <fa_output_list_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>;\n";

				if (nArgumentCount == 9)
				{
					string strInputFilePathNameList = "";
					string strOutputFilePathNameTransform = "";
					string strSubFolderList = "";
					string strFNAOutputListFilePathName = "";
					string strFAOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					//  Sub-lfofders vector<string>
					vector<string> vSubFolders;

					strInputFilePathNameList = vArgs[2];
					strOutputFilePathNameTransform = vArgs[3];
					strSubFolderList = vArgs[4];
					strFNAOutputListFilePathName = vArgs[5];
					strFAOutputListFilePathName = vArgs[6];
					strErrorFilePathName = vArgs[7];
					stringstream(vArgs[8]) >> nMaxProcs;

					if (!ListProcessFNAtoFA(strInputFilePathNameList, strOutputFilePathNameTransform, vSubFolders, strFNAOutputListFilePathName, strFAOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Parse .fna/.fa to .fa File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Parse .fna/.fa to .fa File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  List parse fa to porf
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_parse_fa_to_porf") || (ConvertStringToLowerCase(vArgs[1]) == "-lpftp"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7>
				//    -list_parse_fa_to_porf [-lpftp]...\n";
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         <min_orf_length>
				//         <max_orf_length>
				//         <output_list_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 9)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					int nMinORFLength = 0;
					int nMaxORFLength = 0;
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					stringstream(vArgs[4]) >> nMinORFLength;
					stringstream(vArgs[5]) >> nMaxORFLength;
					strOutputListFilePathName = vArgs[6];
					strErrorFilePathName = vArgs[7];
					stringstream(vArgs[8]) >> nMaxProcs;

					if (!ListParseFAtoPORF(strInputFilePathNameList, strInputFilePathNameTransform, nMinORFLength, nMaxORFLength, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Parse .fa to .pORF File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Parse .fa to .pORF File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  List parse porf to orf
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_parse_porf_to_orf") || (ConvertStringToLowerCase(vArgs[1]) == "-lppto"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8>
				//    -list_parse_porf_to_orf [-lppto]
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         <orf_folder_name>
				//         <min_orf_length>
				//         <max_orf_length>
				//         <output_list_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 10)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strORFFolderName = "";
					string strORFFileNameExtension = "";
					int nMinORFLength = 0;
					int nMaxORFLength = 0;
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strORFFolderName = vArgs[4];
					stringstream(vArgs[5]) >> nMinORFLength;
					stringstream(vArgs[6]) >> nMaxORFLength;
					strOutputListFilePathName = vArgs[7];
					strErrorFilePathName = vArgs[8];
					stringstream(vArgs[9]) >> nMaxProcs;

					if (!ListParsePORFtoORF(strInputFilePathNameList, strInputFilePathNameTransform, strORFFolderName, nMinORFLength, nMaxORFLength, 
						strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Parse .pORF to .ORF Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Parse .pORF to .ORF File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  List parse .gbk container file
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_parse_gbk_container") || (ConvertStringToLowerCase(vArgs[1]) == "-lpgc"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>
				//    -list_parse_gbk_container [-lpgc]
				//         <input_file_path_name_list>
				//         <output_file_path_name_transform>
				//         <output_list_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 7)
				{
					string strInputFilePathNameList = "";
					string strOutputFilePathNameTransform = "";
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strOutputFilePathNameTransform = vArgs[3];
					strInputFilePathNameList = vArgs[4];
					strErrorFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> nMaxProcs;

					if (!ListParseGBKContainerFiles(strInputFilePathNameList, strOutputFilePathNameTransform, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Parse .gbk Container File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Parse .gbk Container File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Create .dat/_na.dat catalog
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-create_dat_catalog") || (ConvertStringToLowerCase(vArgs[1]) == "-cdc"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>
				//    -create_dat_catalog [-cdc]
				//         <dat_input_file_path_name>
				//         <na_dat_input_file_path_name>
				//         <output_catalog_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>
				//         <max_catalog_size>

				if (nArgumentCount == 8)
				{
					string strDatInputFilePathName = "";
					string strNADatInputFilePathName = "";
					string strOutputCatalogFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 1;
					long lMaxCatalogSize = 0;

					strDatInputFilePathName = vArgs[2];
					strNADatInputFilePathName = vArgs[3];
					strOutputCatalogFilePathName = vArgs[4];
					strErrorFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> nMaxProcs;
					stringstream(vArgs[7]) >> lMaxCatalogSize;

					CBase123_Catalog b123Catalog(lMaxCatalogSize);
					if (!b123Catalog.CreateDatCatalog(strDatInputFilePathName, strNADatInputFilePathName, strOutputCatalogFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  Create .dat Catalog Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Create .dat Catalog:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Create .gbk catalog
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-create_gbk_catalog") || (ConvertStringToLowerCase(vArgs[1]) == "-cgc"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>
				//    -create_gbk_catalog [-cgc]
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         <output_catalog_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>
				//         <max_catalog_size>

				if (nArgumentCount == 8)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputCatalogFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 1;
					long lMaxCatalogSize = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputCatalogFilePathName = vArgs[4];
					strErrorFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> nMaxProcs;
					stringstream(vArgs[7]) >> lMaxCatalogSize;

					CBase123_Catalog b123Catalog(lMaxCatalogSize);
					if (!b123Catalog.CreateGBKCatalog(strInputFilePathNameList, strInputFilePathNameTransform, strOutputCatalogFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  Create .gbk Catalog Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Create .gbk Catalog:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  FRESH shuffles
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_shuffle_fa_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lsff"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8>
				//    -list_shuffle_fa_files [-lsff]
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         <catalog_file_path_name>
				//         <max_catalog_size>
				//         <output_count>
				//         <output_list_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 10)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strCatalogFilePathName = "";
					int nMaxCatalogSize = 0;
					int nOutputCount = 0;
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strCatalogFilePathName = vArgs[4];
					stringstream(vArgs[5]) >> nMaxCatalogSize;
					stringstream(vArgs[6]) >> nOutputCount;
					strOutputListFilePathName = vArgs[7];
					strErrorFilePathName = vArgs[8];
					stringstream(vArgs[9]) >> nMaxProcs;

					if (!ListshuffleFAFiles(strInputFilePathNameList, strInputFilePathNameTransform, strCatalogFilePathName, nMaxCatalogSize, nOutputCount, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List shuffle .fa File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List shuffle .fa File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Filter f-distance list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_filter_for_fdistance") || (ConvertStringToLowerCase(vArgs[1]) == "-lfff"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg5> <arg6> <arg7>
				//    -list_filter_for_fdistance [-lfff]
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         -use_strict_filter [-usf]
				//              ...OR
				//                   -use_lax_filter [-ulf]
				//         <max_poly_unknowns>
				//         <accept_output_list_file_path_name>
				//         <reject_output_list_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 9)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					bool bUseStrictFilter = false;
					int nMaxPolyLimit = 0;
					string strAcceptOutputListFilePathName = "";
					string strRejectOutputListFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					if ((ConvertStringToLowerCase(vArgs[4]) == "-use_strict_filter") || (ConvertStringToLowerCase(vArgs[4]) == "-usf"))
						bUseStrictFilter = true;
					stringstream(vArgs[5]) >> nMaxPolyLimit;
					strAcceptOutputListFilePathName = vArgs[6];
					strRejectOutputListFilePathName = vArgs[7];
					stringstream(vArgs[8]) >> nMaxProcs;

					if (!ListFilterForFDistance(strInputFilePathNameList, strInputFilePathNameTransform, bUseStrictFilter, nMaxPolyLimit, strAcceptOutputListFilePathName, strRejectOutputListFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  Filter F-Distance List Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Filter F-Distance List:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Contabulate F-Distance output
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_contabulate_fdistance_output") || (ConvertStringToLowerCase(vArgs[1]) == "-lcfo"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8> <arg9>
				//    -list_contabulate_fdistance_output [-lcfo]
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         <output_tablefile_path_name>
				//         <catalog_file_path_name>
				//         <max_catalog_size>
				//         <output_count>
				//         <output_file_name_suffix>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 11)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputTableFilePathName = "";
					string strCatalogFilePathName = "";
					long lMaxCatalogSize = 0;
					int nOutputCount = 0;
					string strOutputFileNameSuffix = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputTableFilePathName = vArgs[4];
					strCatalogFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> lMaxCatalogSize;
					stringstream(vArgs[7]) >> nOutputCount;
					strOutputFileNameSuffix = vArgs[8];
					strErrorFilePathName = vArgs[9];
					stringstream(vArgs[10]) >> nMaxProcs;

					if (ListContabulateFDistanceOutput(strInputFilePathNameList, strInputFilePathNameTransform, strOutputTableFilePathName, strCatalogFilePathName, lMaxCatalogSize, nOutputCount, strOutputFileNameSuffix, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  Contabulate F-Distance Output Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Contabulate F-Distance Output:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Clear F-Distance output
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_clear_fdistance_output") || (ConvertStringToLowerCase(vArgs[1]) == "-lclfo"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>
				//    -list_clear_fdistance_output [-lclfo]
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         <output_count>
				//         <output_file_name_suffix>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 8)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					int nOutputCount = 0;
					string strOutputFileNameSuffix = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					stringstream(vArgs[4]) >> nOutputCount;
					strOutputFileNameSuffix = vArgs[5];
					strErrorFilePathName = vArgs[6];
					stringstream(vArgs[7]) >> nMaxProcs;

					if (!ListClearFDistanceOutput(strInputFilePathNameList, strInputFilePathNameTransform, nOutputCount, strOutputFileNameSuffix, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  Clear F-Distance Output Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Clear F-Distance Output:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Perform F-Distance analysis
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-perform_fdistance_analysis") || (ConvertStringToLowerCase(vArgs[1]) == "-pfda"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8> <arg9> <arg10> <arg11> <arg12> <arg13> <arg14> <arg15> <arg16> <arg17> <arg18>
				//    -perform_fdistance_analysis [-pfda]
				//         <output_table_file_path_name>
				//         <background_input_file_path_name_list>
				//         <background_input_file_path_name_transform>
				//         <background_catalog_file_path_name>
				//         <maximum_background_catalog_size>
				//         -background_unidirect [-bu]
				//              ...OR
				//                   -background_bidirect [-bb]
				//         -background_allow_unknowns [-bau]
				//              ...OR
				//                   -background_disallow_unknowns [-bdu]
				//         <background_error_file_path_name>
				//         <foreground_input_file_path_name_list>
				//         <foreground_input_file_path_name_transform>
				//         <foreground_catalog_file_path_name>
				//         <maximum_background_catalog_size>
				//         -foreground_unidirect [-fu]
				//              ...OR
				//                   -foreground_bidirect [-fb]
				//         <output_file_name_suffix>
				//         <foreground_error_file_path_name>
				//         <nmer_length>
				//         <max_processors>

				if (nArgumentCount == 20)
				{
					bool bResult = false;
					string strOutputTableFilePathName = "";
					string strBackgroundFilePathNameList = "";
					string strBackgroundInputFilePathNameTransform = "";
					string strBackgroundCatalogFilePathName = "";
					long lMaxBackgroundCatalogSize = 0;
					bool bBackgroundBidirect = false;
					bool bBackgroundAllowUnknowns = false;
					string strBackgroundErrorFilePathName = "";
					string strForegroundFilePathNameList = "";
					string strForegroundInputFilePathNameTransform = "";
					string strForegroundCatalogFilePathName = "";
					long lMaxForegroundCatalogSize = 0;
					bool bForegroundBidirect = false;
					bool bForegroundAllowUnknowns = false;
					string strForegroundErrorFilePathName = "";
					string strOutputFileNameSuffix = "";
					int nNMerLength = 0;
					int nMaxProcs = 0;

					strOutputTableFilePathName = vArgs[2];
					strBackgroundFilePathNameList = vArgs[3];
					strBackgroundInputFilePathNameTransform = vArgs[4];
					strBackgroundCatalogFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> lMaxBackgroundCatalogSize;
					if ((ConvertStringToLowerCase(vArgs[7]) == "-background_bidirect") || (ConvertStringToLowerCase(vArgs[7]) == "-bb"))
						bBackgroundBidirect = true;
					if ((ConvertStringToLowerCase(vArgs[8]) == "-background_allow_unknowns") || (ConvertStringToLowerCase(vArgs[8]) == "-bau"))
						bBackgroundAllowUnknowns = true;
					strBackgroundErrorFilePathName = vArgs[9];
					strForegroundFilePathNameList = vArgs[10];
					strForegroundInputFilePathNameTransform = vArgs[11];
					strForegroundCatalogFilePathName = vArgs[12];
					stringstream(vArgs[13]) >> lMaxForegroundCatalogSize;
					if ((ConvertStringToLowerCase(vArgs[14]) == "-foreground_bidirect") || (ConvertStringToLowerCase(vArgs[14]) == "-fb"))
						bForegroundBidirect = true;
					if ((ConvertStringToLowerCase(vArgs[15]) == "-foreground_allow_unknowns") || (ConvertStringToLowerCase(vArgs[15]) == "-fau"))
						bForegroundAllowUnknowns = true;
					strOutputFileNameSuffix = vArgs[16];
					strForegroundErrorFilePathName = vArgs[17];
					stringstream(vArgs[18]) >> nNMerLength;
					stringstream(vArgs[19]) >> nMaxProcs;

					if ((nNMerLength == 8) || (nNMerLength == 16))
					{
						if (PerformFDistanceAnalysis(strOutputTableFilePathName, strBackgroundFilePathNameList, strBackgroundInputFilePathNameTransform, 
								strBackgroundCatalogFilePathName, lMaxBackgroundCatalogSize, bBackgroundBidirect, bBackgroundAllowUnknowns, strBackgroundErrorFilePathName, 
								strForegroundFilePathNameList, strForegroundInputFilePathNameTransform, strForegroundCatalogFilePathName, lMaxForegroundCatalogSize,
								bForegroundBidirect, bForegroundAllowUnknowns, strOutputFileNameSuffix, strForegroundErrorFilePathName, nNMerLength, nMaxProcs))
						{
							ReportTimeStamp(vArgs[0], "ERROR:  F-Distance Analysis Failed");

							return -1;
						}
					}
					else
					{
						ReportTimeStamp(vArgs[0], "ERROR:  F-Distance nMer Length Must be [8, 16]:  Use -help [-h] Switch for Assistance");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Perform F-Distance Analysis:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Fold files list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_fold_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lff"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8> <arg9> <arg10> <arg11> <arg12> <arg13> <arg14> <arg15> <arg16> <arg17>
				//       <arg18> <arg19>
				//    -list_fold_files [-lfpf]
				//       <input_file_path_name_list>
				//       -porf_file_list [-pfl]...\n";
				//            ...OR...\n";
				//                 -orf_file_list [-ofl]...\n";
				//       <input_file_path_name_transform>
				//       -no_overwrite_files [-nof]...\n";
				//            ...OR...\n";
				//                 -overwrite_files [-of]...\n";
				//       -thread_mode_process [-tmp]...\n";
				//            ...OR...\n";
				//                 -thread_mode_system [-tms]...\n";
				//            ...OR...\n";
				//                 -thread_mode_popen [-tmpn]...\n";
				//       <working_directory>
				//       <application_file_path_name>
				//       <application_parameters>
				//       <output_file_path_name_transform>
				//       <overwrite_file_path_name_transform>
				//       <after_file_path_name_transforms>
				//       <length_multiplier_factor>
				//       <orf_folder_name>
				//       <min_orf_length>
				//       <max_orf_length>
				//       <porf_output_list_file_path_name>
				//       <porf_error_file_path_name>
				//       <orf_output_list_file_name_suffix>
				//       <orf_error_file_path_name>
				//       <max_processors>
				
				if (nArgumentCount == 21)
				{
					string strInputFilePathNameList = "";
					bool bPORFFiles = true;
					string strInputFilePathNameTransform = "";
					bool bOverwriteFiles = false;
					string strThreadMode = "";
					string strWorkingDirectory = "";
					string strApplicationFilePathName = "";
					string strApplicationParameters = "";
					string strOutputFilePathNameTransform = "";
					string strOverwriteFilePathNameTransform = "";
					string strAfterFilePathNameTransforms = "";
					int nLengthMultiplierFactor = 0;
					string strORFFolderName = "";
					int nMinORFLength = 0;
					int nMaxORFLength = 0;
					string strORFOutputListFileNameSuffix = "";
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					if ((ConvertStringToLowerCase(vArgs[4]) == "-orf_file_list") || (ConvertStringToLowerCase(vArgs[4]) == "-ofl"))
						bPORFFiles = false;
					if ((ConvertStringToLowerCase(vArgs[5]) == "-overwrite_files") || (ConvertStringToLowerCase(vArgs[5]) == "-of"))
						bOverwriteFiles = true;
					if ((ConvertStringToLowerCase(vArgs[6]) == "-thread_mode_process") || (ConvertStringToLowerCase(vArgs[6]) == "-tmp"))
						strThreadMode = "-thread_mode_process";
					else if ((ConvertStringToLowerCase(vArgs[6]) == "-thread_mode_system") || (ConvertStringToLowerCase(vArgs[6]) == "-tms"))
						strThreadMode = "-thread_mode_system";
					else if ((ConvertStringToLowerCase(vArgs[6]) == "-thread_mode_popen") || (ConvertStringToLowerCase(vArgs[6]) == "-tmpn"))
						strThreadMode = "-thread_mode_popen";
					strWorkingDirectory = vArgs[7];
					strApplicationFilePathName = vArgs[8];
					strApplicationParameters = vArgs[9];
					strOutputFilePathNameTransform = vArgs[10];
					strOverwriteFilePathNameTransform = vArgs[11];
					strAfterFilePathNameTransforms = vArgs[12];
					stringstream(vArgs[13]) >> nLengthMultiplierFactor;
					strORFFolderName = vArgs[14];
					stringstream(vArgs[15]) >> nMinORFLength;
					stringstream(vArgs[16]) >> nMaxORFLength;
					strORFOutputListFileNameSuffix = vArgs[17];
					strOutputListFilePathName = vArgs[18];
					strErrorFilePathName = vArgs[19];
					stringstream(vArgs[20]) >> nMaxProcs;

					if (!ListFoldFiles(strInputFilePathNameList, bPORFFiles, strInputFilePathNameTransform, bOverwriteFiles, strThreadMode, strWorkingDirectory, strApplicationFilePathName, 
						strApplicationParameters, strOutputFilePathNameTransform, strOverwriteFilePathNameTransform, strAfterFilePathNameTransforms, nLengthMultiplierFactor, strORFFolderName,
						nMinORFLength, nMaxORFLength, strORFOutputListFileNameSuffix, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Fold File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted for List Fold File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Convert file list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_confirm_fold_output_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lcfof"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8> <arg9> <arg10>
				//  -list_confirm_fold_output_files [-lcfof]
				//       <input_file_path_name_list>
				//       <input_file_path_name_transform>
				//       <output_file_path_name_transform>
				//       <orf_folder_name>
				//       <min_orf_length>
				//       <missing_porf_list_file_path_name>
				//       <missing_orf_list_file_path_name>
				//       <analytical_output_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 12)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputFilePathNameTransform = "";
					string strORFFolderName = "";
					int nMinORFLength = 0;
					int nMaxORFLength = 0;
					string strMissingPORFListFilePathName = "";
					string strMissingORFListFilePathName = "";
					string strAnalyticalOutputFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputFilePathNameTransform = vArgs[4];
					strORFFolderName = vArgs[5];
					stringstream(vArgs[6]) >> nMinORFLength;
					stringstream(vArgs[7]) >> nMaxORFLength;
					strMissingPORFListFilePathName = vArgs[8];
					strMissingORFListFilePathName = vArgs[9];
					strAnalyticalOutputFilePathName = vArgs[10];
					stringstream(vArgs[11]) >> nMaxProcs;

					if (!ListConfirmFoldOutputFiles(strInputFilePathNameList, strInputFilePathNameTransform, strOutputFilePathNameTransform, strORFFolderName, nMinORFLength,
						nMaxORFLength, strMissingPORFListFilePathName, strMissingORFListFilePathName, strAnalyticalOutputFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Confirm Fold Output Files Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Confirm Fold Output Files:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Extract .PDB files from Rosetta silent (*.out) file format
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_extract_pdb_from_silent_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lepfsf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8> <arg9> <arg10> <arg11> <arg12>
				//  -list_extract_pdb_from_silent_files [-lepfsf]...\n";
				//       <input_file_path_name_list>...\n";
				//       <input_file_path_name_transform>...\n";
				//       -no_overwrite_files [-nof]...\n";
				//            ...OR...\n";
				//                 -overwrite_files [-of]...\n";
				//       -thread_mode_process [-tmp]...\n";
				//            ...OR...\n";
				//                 -thread_mode_system [-tms]...\n";
				//            ...OR...\n";
				//                 -thread_mode_popen [-tmpn]...\n";
				//       <working_directory>...\n";
				//       <application_file_path_name>...\n";
				//       <application_parameters>...\n";
				//       <overwrite_file_path_name_transform>...\n";
				//       <after_file_path_name_transforms>...\n";
				//       <output_list_file_path_name>...\n";
				//       <error_file_path_name>...\n";
				//       <max_processors>;\n";

				if (nArgumentCount == 14)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					bool bOverwriteFiles = false;
					string strThreadMode = "";
					string strWorkingDirectory = "";
					string strApplicationFilePathName = "";
					string strApplicationParameters = "";
					string strOverwriteFilePathNameTransform = "";
					string strAfterFilePathNameTransforms = "";
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					if ((ConvertStringToLowerCase(vArgs[4]) == "-overwrite_files") || (ConvertStringToLowerCase(vArgs[4]) == "-of"))
						bOverwriteFiles = true;
					if ((ConvertStringToLowerCase(vArgs[5]) == "-thread_mode_process") || (ConvertStringToLowerCase(vArgs[5]) == "-tmp"))
						strThreadMode = "-thread_mode_process";
					else if ((ConvertStringToLowerCase(vArgs[5]) == "-thread_mode_system") || (ConvertStringToLowerCase(vArgs[5]) == "-tms"))
						strThreadMode = "-thread_mode_system";
					else if ((ConvertStringToLowerCase(vArgs[5]) == "-thread_mode_popen") || (ConvertStringToLowerCase(vArgs[5]) == "-tmpn"))
						strThreadMode = "-thread_mode_popen";
					strWorkingDirectory = vArgs[6];
					strApplicationFilePathName = vArgs[7];
					strApplicationParameters = vArgs[8];
					strOverwriteFilePathNameTransform = vArgs[9];
					strAfterFilePathNameTransforms = vArgs[10];
					strOutputListFilePathName = vArgs[11];
					strErrorFilePathName = vArgs[12];
					stringstream(vArgs[13]) >> nMaxProcs;

					if (!ListExtractPDBFromSilentFiles(strInputFilePathNameList, strInputFilePathNameTransform, bOverwriteFiles, strThreadMode, strWorkingDirectory, strApplicationFilePathName,
						strApplicationParameters, strOverwriteFilePathNameTransform, strAfterFilePathNameTransforms, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Extract .PDB from Rosetta Silent (*.out) File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted for List Extract .PDB from Rosetta Silent (*.out) File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Convert .PDB files to dot-bracket file format
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_convert_pdb_to_db_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lcptdf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>
				//    -list_convert_pdb_to_db_files [-lcptdf]
				//       <input_file_path_name_list>
				//       <input_file_path_name_transform>
				//       <output_file_path_name_transform>
				//       <output_list_file_path_name>
				//       <error_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 8)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputFilePathNameTransform = "";
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputFilePathNameTransform = vArgs[4];
					strOutputListFilePathName = vArgs[5];
					strErrorFilePathName = vArgs[6];
					stringstream(vArgs[7]) >> nMaxProcs;

					if (!ListConvertPDBtoB123Files(strInputFilePathNameList, strInputFilePathNameTransform, strOutputFilePathNameTransform, strOutputListFilePathName,
						strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Convert .PDB to Dot-Bracket (*.fold) File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted for List Convert .PDB to Dot-Bracket (*.fold) File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Convert Rosetta PDB fold output files to Base123 format
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_convert_pdb_to_base123_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lcptbf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>
				//    -list_convert_pdb_to_base123_files [-lcptbf]
				//       <input_file_path_name_list>
				//       <input_file_path_name_transform>
				//       <output_file_path_name_transform>
				//       <output_list_file_path_name>
				//       <error_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 8)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputFilePathNameTransform = "";
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputFilePathNameTransform = vArgs[4];
					strOutputListFilePathName = vArgs[5];
					strErrorFilePathName = vArgs[6];
					stringstream(vArgs[7]) >> nMaxProcs;

					if (!ListConvertPDBtoB123Files(strInputFilePathNameList, strInputFilePathNameTransform, strOutputFilePathNameTransform, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Convert Rosetta PDB Fold Output (*.PDB) File to Base123 (*.b123) File Format Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted for List Convert Rosetta PDB Fold Output (*.pdb) to Base123 (*.b123) File Format:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Convert ViennaRNA (.fold) fold output files to Base123 format
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_convert_db_to_base123_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lcdtbf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>
				//    -list_convert_db_to_base123_files [-lcdtbf]
				//       <input_file_path_name_list>
				//       <input_file_path_name_transform>
				//       <output_file_path_name_transform>
				//       <output_list_file_path_name>
				//       <error_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 8)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputFilePathNameTransform = "";
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputFilePathNameTransform = vArgs[4];
					strOutputListFilePathName = vArgs[5];
					strErrorFilePathName = vArgs[6];
					stringstream(vArgs[7]) >> nMaxProcs;

					if (!ListConvertDBtoB123Files(strInputFilePathNameList, strInputFilePathNameTransform, strOutputFilePathNameTransform, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Convert ViennaRNA Fold Output (*.fold) File to Base123 File Format Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted for List Convert ViennaRNA Fold Output (*.fold) to Base123 (*.b123) File Format:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Tabulate Base123 files list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_tabulate_base123_files") || (ConvertStringToLowerCase(vArgs[1]) == "-ltbf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>
				//    -list_tabulate_base123_files [-ltbf]
				//       <input_file_path_name_list>
				//       <input_file_path_name_transform>
				//       <output_list_file_path_name>
				//       <error_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 7)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputListFilePathName = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputListFilePathName = vArgs[4];
					strErrorFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> nMaxProcs;

					if (!ListTabulateB123Files(strInputFilePathNameList, strInputFilePathNameTransform, strOutputListFilePathName, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Tabulate Base123 (*.b123) File(s) Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted for List Tabulate Base123 (*.b123) File(s):  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Create HPC Distributed Batch Job From a File List
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-create_distributed_batch_job") || (ConvertStringToLowerCase(vArgs[1]) == "-cdbj"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> <arg8> <arg9> <arg10> <arg11> <arg12> <arg13>
				//  -create_distributed_batch_job [-cdbj]
				//       <input_file_path_name_list>
				//       <output_list_file_path_name_transform>
				//       <queue_name>
				//       <wall_time>
				//       <job_name>
				//       <account_id>
				//       <application_name>
				//       <application_parameters>
				//       <project_path_name>
				//       <max_batches>
				//       -aprun_batch [-ab]
				//            ...OR...\n";
				//                 -qsub_batch [-qb]
				//       -make_list [-ml]
				//            ...OR...\n";
				//                 -skip_list [-sl]
				//       <max_processors>

				if (nArgumentCount == 15)
				{
					string strInputFilePathNameList = "";
					string strOutputListFilePathNameTransform = "";
					string strQueueName = "";
					string strWallTime = "";
					string strJobName = "";
					string strAccountID = "";
					string strApplicationName = "";
					string strApplicationParameters = "";
					string strProjectPathName = "";
					int nMaxBatches = 0;
					bool bUseAprun = false;
					bool bMakeList = true;
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strOutputListFilePathNameTransform = vArgs[3];
					strQueueName = vArgs[4];
					strWallTime = vArgs[5];
					strJobName = vArgs[6];
					strAccountID = vArgs[7];
					strApplicationName = vArgs[8];
					strApplicationParameters = vArgs[9];
					strProjectPathName = vArgs[10];
					stringstream(vArgs[11]) >> nMaxBatches;
					if ((ConvertStringToLowerCase(vArgs[12]) == "-aprun_batch") || (ConvertStringToLowerCase(vArgs[12]) == "-ab"))
						bUseAprun = true;
					if ((ConvertStringToLowerCase(vArgs[13]) == "-skip_list") || (ConvertStringToLowerCase(vArgs[13]) == "-sl"))
						bMakeList = false;
					stringstream(vArgs[14]) >> nMaxProcs;

					if (!CreateDistributedBatchJob(strInputFilePathNameList, strOutputListFilePathNameTransform, strQueueName, strWallTime, strJobName, strAccountID, strApplicationName, 
						strApplicationParameters, strProjectPathName, nMaxBatches, bUseAprun, bMakeList, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  Create HPC Distributed Batch Job Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Create HPC Distributed Batch Job:  Use -help [-h] Switch for Assistance");

					string strMsg = "\n";

					if (nArgumentCount >= 2)
						strMsg += "-create_distributed_batch_job [-cdbj] = " + vArgs[1] + "\n";
					if (nArgumentCount >= 3)
						strMsg += "input_file_path_name_list = " + vArgs[2] + "\n";
					if (nArgumentCount >= 4)
						strMsg += "output_list_file_path_name_transform = " + vArgs[3] + "\n";
					if (nArgumentCount >= 5)
						strMsg += "queue_name = " + vArgs[4] + "\n";
					if (nArgumentCount >= 6)
						strMsg += "wall_time = " + vArgs[5] + "\n";
					if (nArgumentCount >= 7)
						strMsg += "job_name = " + vArgs[6] + "\n";
					if (nArgumentCount >= 8)
						strMsg += "account_id = " + vArgs[7] + "\n";
					if (nArgumentCount >= 9)
						strMsg += "application_name = " + vArgs[8] + "\n";
					if (nArgumentCount >= 10)
						strMsg += "<application_parameters = " + vArgs[9] + "\n";
					if (nArgumentCount >= 11)
						strMsg += "project_path_name = " + vArgs[10] + "\n";
					if (nArgumentCount >= 12)
						strMsg += "max_batches = " + vArgs[11] + "\n";
					if (nArgumentCount >= 13)
						strMsg += "-aprun_batch [-ab] = " + vArgs[12] + "\n";
					if (nArgumentCount >= 14)
						strMsg += "max_processors = " + vArgs[13] + "\n";

					ReportTimeStamp(vArgs[0], strMsg);

					return -1;
				}
			}
			//  Convert file list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_convert_path") || (ConvertStringToLowerCase(vArgs[1]) == "-lcp"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4>
				//    -list_convert_path [-lcp]
				//         <input_file_path_name_list>
				//         <output_file_path_name_transform>
				//         <output_list_file_path_name>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 6)
				{
					string strInputFilePathNameList = "";
					string strOutputFilePathNameTransform = "";
					string strOutputListFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strOutputFilePathNameTransform = vArgs[3];
					strOutputListFilePathName = vArgs[4];
					stringstream(vArgs[5]) >> nMaxProcs;

					if (!ListConvertPath(strInputFilePathNameList, strOutputFilePathNameTransform, strOutputListFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  Convert File List Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to Convert File List:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  File find and replace
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-file_find_replace") || (ConvertStringToLowerCase(vArgs[1]) == "-ffr"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>
				//    -file_find_replace [-ffr]
				//         <input_file_path_name>
				//         <output_file_path_name>
				//         <text_to_extract>
				//         <text_to_insert>
				//         -is_case_sensitive [-ics]
				//              ...OR...\n";
				//                   -not_case_sensitive [-ncs]

				if (nArgumentCount == 7)
				{
					string strInputFilePathName = "";
					string strOutputFilePathName = "";
					string strExtract = "";
					string strInsert = "";
					bool bIsCaseSensitive = false;

					strInputFilePathName = vArgs[2];
					strOutputFilePathName = vArgs[3];
					strExtract = vArgs[4];
					strInsert = vArgs[5];
					if ((ConvertStringToLowerCase(vArgs[6]) == "-is_case_sensitive") || (ConvertStringToLowerCase(vArgs[6]) == "-ics"))
						bIsCaseSensitive = true;

					if (!FileTextReplace(strInputFilePathName, strOutputFilePathName, strExtract, strInsert, bIsCaseSensitive))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  File Find and Replace Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted for File Find and Replace:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Delete all files in list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_delete_files") || (ConvertStringToLowerCase(vArgs[1]) == "-ldf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4>
				//    -list_delete_files [-ldf]
				//         <input_file_path_name_list>
				//         <input_file_path_name_transform>
				//         <error_file_path_name>
				//         <max_processors>

				if (nArgumentCount == 6)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strErrorFilePathName = vArgs[4];
					stringstream(vArgs[5]) >> nMaxProcs;

					if (!ListDeleteFiles(strInputFilePathNameList, strInputFilePathNameTransform, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Delete Files Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Delete Files:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Delete all files in list using transform
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_delete_files_in_directory") || (ConvertStringToLowerCase(vArgs[1]) == "-ldfid"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4>
				//  -list_delete_files_in_directory [-ldfid]
				//       <input_file_path_name>
				//       <delete_path_name_transform>
				//       <error_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 6)
				{
					string strInputFilePathNameList = "";
					string strDeletePathNameTransform = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strDeletePathNameTransform = vArgs[3];
					strErrorFilePathName = vArgs[4];
					stringstream(vArgs[5]) >> nMaxProcs;

					if (!ListDeleteFilesInDirectory(strInputFilePathNameList, strDeletePathNameTransform, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Delete Files in Directory Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Delete Files in Directory:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Renames all files in a list via transforms
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_transform_rename_files") || (ConvertStringToLowerCase(vArgs[1]) == "-ltrf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>
				//  -list_rename_files [-lrf]
				//       <input_file_path_name>
				//       <input_file_path_name_transform>
				//       <file_path_name_transforms>
				//       <error_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 7)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strFilePathNameTransforms = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strFilePathNameTransforms = vArgs[4];
					strErrorFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> nMaxProcs;

					if (!ListTransformRenameFiles(strInputFilePathNameList, strInputFilePathNameTransform, strFilePathNameTransforms, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Transform Rename Files Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Transform Rename Files:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Renames all files in a list via match-and-replace
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_match_replace_rename_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lmrrf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>>
				//  -list_rename_files [-lrf]
				//       <input_file_path_name>
				//       <input_file_path_name_transform>
				//       <match_and_replace>
				//       <error_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 7)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strMatchAndReplace = "";
					string strErrorFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strMatchAndReplace = vArgs[4];
					strErrorFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> nMaxProcs;

					if (!ListMatchReplaceRenameFiles(strInputFilePathNameList, strInputFilePathNameTransform, strMatchAndReplace, strErrorFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Match-and-Replace Rename Files Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Match-and-Replace Rename Files:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Confirm output of all files in a list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_confirm_output_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lcof"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5>
				//  -list_confirm_output_files [-lcof]
				//       <input_file_path_name>
				//       <input_file_path_name_transform>
				//       <output_file_path_name_transform>
				//       <missing_list_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 7)
				{
					string strInputFilePathNameList = "";
					string strInputFilePathNameTransform = "";
					string strOutputFilePathNameTransform = "";
					string strMissingListFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameList = vArgs[2];
					strInputFilePathNameTransform = vArgs[3];
					strOutputFilePathNameTransform = vArgs[4];
					strMissingListFilePathName = vArgs[5];
					stringstream(vArgs[6]) >> nMaxProcs;

					if (!ListConfirmOutputFiles(strInputFilePathNameList, strInputFilePathNameTransform, strOutputFilePathNameTransform, strMissingListFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Confirm Output Files Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Confirm Output Files:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			//  Compares from-list to to-list and outputs differential list
			else if ((ConvertStringToLowerCase(vArgs[1]) == "-list_compare_differential_files") || (ConvertStringToLowerCase(vArgs[1]) == "-lcdf"))
			{
				//  Usage is Base123 <switch> <arg1> <arg2> <arg3> <arg4> <arg5> <arg6>
				//  -list_compare_differential_files [-lcdf]
				//       <input_file_path_name_list_from>
				//       <input_file_path_name_list_to>
				//       <file_path_name_transform>
				//       -multiset_diff [-msd]
				//            ...OR...
				//                 -set_diff [-sd]
				//            ...OR...
				//                 -vector_diff [-vd]
				//       <output_list_file_path_name>
				//       <max_processors>

				if (nArgumentCount == 8)
				{
					string strInputFilePathNameListFrom = "";
					string strInputFilePathNameListTo = "";
					string strFilePathNameTransform = "";
					string strDiffMethod = "";
					string strOutputListFilePathName = "";
					int nMaxProcs = 0;

					strInputFilePathNameListFrom = vArgs[2];
					strInputFilePathNameListTo = vArgs[3];
					strFilePathNameTransform = vArgs[4];
					strDiffMethod = vArgs[5];
					strOutputListFilePathName = vArgs[6];
					stringstream(vArgs[7]) >> nMaxProcs;

					if (!ListCompareDifferentialFiles(strInputFilePathNameListFrom, strInputFilePathNameListTo, strFilePathNameTransform, strDiffMethod, strOutputListFilePathName, nMaxProcs))
					{
						ReportTimeStamp(vArgs[0], "ERROR:  List Compare Differential Files Failed");

						return -1;
					}
				}
				else
				{
					ReportTimeStamp(vArgs[0], "ERROR:  Command Line is Not Properly Formatted to List Compare Differential Files:  Use -help [-h] Switch for Assistance");

					return -1;
				}
			}
			else
			{
				//  Report unrecognized switch set
				string strMsg("ERROR:  Invalid Command Switch [^ARG^]");
				strMsg.replace(strMsg.find("^ARG^"), 5, vArgs[1]);
				ReportTimeStamp(vArgs[0], (char*)strMsg.c_str());

				return -1;
			}

			// Update console; end application;
			ReportTimeStamp(vArgs[0], "Base123 Finish");
		}
	}
	catch (exception ex)
	{
		cout << "ERROR [Base123] Exception Code (Check Parameter Arguments/Counts - Index Overflow?):  " << ex.what() << "\n";

		return -1;
	}

	return 0;
}
